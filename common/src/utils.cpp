//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include "utils.hpp"

#include <algorithm>
#include <array>
#include <charconv>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <iterator>
#include <limits>
#include <regex>
#include <system_error>
#include <variant>
#include <vector>

#include <boost/json/object.hpp>
#include <boost/json/serialize.hpp>
#include <boost/json/string.hpp>
#include <openssl/rand.h>

#include <binance/common/decimal.hpp>
#include <binance/common/detail/utils.hpp>
#include <binance/common/errors.hpp>
#include <binance/common/version.hpp>

namespace binance::common {

namespace {

constexpr std::string_view kHexLower = "0123456789abcdef";
constexpr std::string_view kHexUpper = "0123456789ABCDEF";

void random_bytes(unsigned char* out, int len) {
    if (RAND_bytes(out, len) != 1) {
        throw ConnectorClientError("Failed to obtain random bytes");
    }
}

/// `|d|` as an integer, digit by digit. `d` must be finite and integral.
std::string exact_integer(double d) {
    int exponent = 0;
    const double fraction = std::frexp(std::fabs(d), &exponent); // |d| = fraction * 2^exponent
    constexpr int kMantissaBits = std::numeric_limits<double>::digits;
    auto mantissa = static_cast<std::uint64_t>(std::ldexp(fraction, kMantissaBits));
    int shift = exponent - kMantissaBits;
    // Little-endian base-10^9 limbs.
    constexpr std::uint32_t kBase = 1'000'000'000;
    std::vector<std::uint32_t> limbs;
    while (mantissa != 0) {
        limbs.push_back(static_cast<std::uint32_t>(mantissa % kBase));
        mantissa /= kBase;
    }
    for (; shift > 0; --shift) {
        std::uint32_t carry = 0;
        for (auto& limb : limbs) {
            const auto v = (std::uint64_t{limb} << 1U) + carry;
            limb = static_cast<std::uint32_t>(v % kBase);
            carry = static_cast<std::uint32_t>(v / kBase);
        }
        if (carry != 0) {
            limbs.push_back(carry);
        }
    }
    if (limbs.empty()) {
        return "0";
    }
    std::string out = std::to_string(limbs.back());
    for (auto it = std::next(limbs.rbegin()); it != limbs.rend(); ++it) {
        const auto chunk = std::to_string(*it);
        out.append(9 - chunk.size(), '0');
        out += chunk;
    }
    return out;
}

} // namespace

namespace detail {

std::string format_double(double d) {
    if (!std::isfinite(d)) {
        return "null";
    }
    if (d == 0.0) {
        return std::signbit(d) ? "-0" : "0";
    }
    constexpr double kTwoPow53 = 9007199254740992.0;
    if (std::fabs(d) >= kTwoPow53) {
        // Appended rather than `"-" + exact_integer(d)`, which GCC 12 misreports as an overlapping
        // copy (-Wrestrict, GCC bug 105329).
        std::string out = d < 0 ? "-" : "";
        out += exact_integer(d);
        return out;
    }
    return Decimal(d).str();
}

} // namespace detail

namespace {

void append_json(std::string& out, const boost::json::value& value) {
    switch (value.kind()) {
    case boost::json::kind::null:
        out += "null";
        break;
    case boost::json::kind::bool_:
        out += value.get_bool() ? "true" : "false";
        break;
    case boost::json::kind::int64:
        out += std::to_string(value.get_int64());
        break;
    case boost::json::kind::uint64:
        out += std::to_string(value.get_uint64());
        break;
    case boost::json::kind::double_:
        out += detail::format_double(value.get_double());
        break;
    case boost::json::kind::string:
        out += boost::json::serialize(value.get_string());
        break;
    case boost::json::kind::array: {
        out += '[';
        bool first = true;
        for (const auto& item : value.get_array()) {
            if (!first) {
                out += ',';
            }
            first = false;
            append_json(out, item);
        }
        out += ']';
        break;
    }
    case boost::json::kind::object: {
        out += '{';
        bool first = true;
        for (const auto& [key, item] : value.get_object()) {
            if (!first) {
                out += ',';
            }
            first = false;
            out += boost::json::serialize(boost::json::string(key));
            out += ':';
            append_json(out, item);
        }
        out += '}';
        break;
    }
    }
}

void ensure_safe_plain_component(std::string_view text, const std::string& context) {
    // NOLINTNEXTLINE(readability-qualified-auto): a pointer on some standard libraries only
    const auto bad = std::find_if(text.begin(), text.end(), [](char c) {
        const auto u = static_cast<unsigned char>(c);
        return c == '&' || c == '=' || u < 0x20 || u == 0x7f;
    });
    if (bad != text.end()) {
        throw ConnectorClientError(
            context +
            ": value contains disallowed character; '&', '=', and control characters are not "
            "permitted in WebSocket API signed parameters");
    }
}

// ASCII-only character classes: the `<cctype>` ones depend on the C locale.
constexpr bool is_ascii_alnum(char c) noexcept {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9');
}

constexpr bool is_ascii_space(char c) noexcept {
    return c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r';
}

constexpr char ascii_lower(char c) noexcept {
    return c >= 'A' && c <= 'Z' ? static_cast<char>(c - 'A' + 'a') : c;
}

constexpr char ascii_upper(char c) noexcept {
    return c >= 'a' && c <= 'z' ? static_cast<char>(c - 'a' + 'A') : c;
}

std::string to_lower(std::string_view text) {
    std::string out(text);
    std::transform(out.begin(), out.end(), out.begin(), ascii_lower);
    return out;
}

std::uint32_t parse_u32_or(std::string_view text, std::uint32_t fallback) {
    std::uint32_t out = 0;
    auto [ptr, ec] = std::from_chars(text.data(), text.data() + text.size(), out);
    return (ec == std::errc{} && ptr == text.data() + text.size()) ? out : fallback;
}

std::string compiler_id() {
#if defined(__clang__) && defined(__apple_build_version__)
    return "appleclang " + std::to_string(__clang_major__) + "." + std::to_string(__clang_minor__) +
           "." + std::to_string(__clang_patchlevel__);
#elif defined(__clang__)
    return "clang " + std::to_string(__clang_major__) + "." + std::to_string(__clang_minor__) +
           "." + std::to_string(__clang_patchlevel__);
#elif defined(__GNUC__)
    return "gcc " + std::to_string(__GNUC__) + "." + std::to_string(__GNUC_MINOR__) + "." +
           std::to_string(__GNUC_PATCHLEVEL__);
#elif defined(_MSC_VER)
    return "msvc " + std::to_string(_MSC_VER / 100) + "." + std::to_string(_MSC_VER % 100);
#else
    return "unknown";
#endif
}

constexpr std::string_view os_id() {
#if defined(_WIN32)
    return "windows";
#elif defined(__APPLE__)
    return "macos";
#elif defined(__linux__)
    return "linux";
#elif defined(__FreeBSD__)
    return "freebsd";
#else
    return "unknown";
#endif
}

constexpr std::string_view arch_id() {
#if defined(__x86_64__) || defined(_M_X64)
    return "x86_64";
#elif defined(__aarch64__) || defined(_M_ARM64)
    return "aarch64";
#elif defined(__i386__) || defined(_M_IX86)
    return "x86";
#elif defined(__arm__) || defined(_M_ARM)
    return "arm";
#else
    return "unknown";
#endif
}

std::string_view trim(std::string_view text) {
    while (!text.empty() && is_ascii_space(text.front())) {
        text.remove_prefix(1);
    }
    while (!text.empty() && is_ascii_space(text.back())) {
        text.remove_suffix(1);
    }
    return text;
}

} // namespace

namespace detail {

std::string form_urlencode(std::string_view text) {
    std::string out;
    out.reserve(text.size());
    for (const char c : text) {
        const auto u = static_cast<unsigned char>(c);
        if (is_ascii_alnum(c) || c == '*' || c == '-' || c == '.' || c == '_') {
            out += c;
        } else if (c == ' ') {
            out += '+';
        } else {
            out += '%';
            out += kHexUpper[u >> 4U];
            out += kHexUpper[u & 0x0FU];
        }
    }
    return out;
}

std::string to_json_string(const boost::json::value& value) {
    std::string out;
    append_json(out, value);
    return out;
}

namespace {

void doubles_to_text(boost::json::value& value) {
    if (const auto* d = value.if_double()) {
        value = std::isfinite(*d) ? boost::json::value(boost::json::string(format_double(*d)))
                                  : boost::json::value(nullptr);
    } else if (auto* array = value.if_array()) {
        for (auto& item : *array) {
            doubles_to_text(item);
        }
    } else if (auto* object = value.if_object()) {
        for (auto& [key, item] : *object) {
            doubles_to_text(item);
        }
    }
}

/// Puts the members of every nested object in alphabetical order. Binance rebuilds a nested
/// parameter such as `filter` with sorted keys before checking the signature, so the signed
/// text and the JSON on the wire must both be sorted.
void sort_object_keys(boost::json::value& value) {
    if (auto* array = value.if_array()) {
        for (auto& item : *array) {
            sort_object_keys(item);
        }
    } else if (auto* object = value.if_object()) {
        std::vector<std::pair<std::string, boost::json::value>> members;
        members.reserve(object->size());
        for (auto& [key, item] : *object) {
            sort_object_keys(item);
            members.emplace_back(std::string(key), std::move(item));
        }
        std::sort(members.begin(), members.end(),
                  [](const auto& lhs, const auto& rhs) { return lhs.first < rhs.first; });
        object->clear();
        for (auto& [key, item] : members) {
            object->emplace(key, std::move(item));
        }
    }
}

} // namespace

std::string param_to_string(const boost::json::value& value) {
    if (value.is_string()) {
        return std::string(value.get_string());
    }
    return to_json_string(value);
}

std::string build_query_string(const Params& params) {
    std::string out;
    for (const auto& [key, value] : params) {
        if (value.is_null()) {
            continue;
        }
        if (!out.empty()) {
            out += '&';
        }
        out += form_urlencode(key);
        out += '=';
        out += form_urlencode(param_to_string(value));
    }
    return out;
}

std::string build_plain_query_string(const Params& params) {
    std::string out;
    for (const auto& [key, value] : params) {
        if (value.is_null()) {
            continue;
        }
        auto text = param_to_string(value);
        ensure_safe_plain_component(key, "unsafe character in parameter name `" + key + "`");
        ensure_safe_plain_component(text, "unsafe character in value of parameter `" + key + "`");
        if (!out.empty()) {
            out += '&';
        }
        out += key;
        out += '=';
        out += text;
    }
    return out;
}

bool should_retry_request(std::string_view method, std::optional<std::uint16_t> status,
                          std::int64_t retries_left) {
    const auto upper = [&] {
        std::string m(method);
        std::transform(m.begin(), m.end(), m.begin(), ascii_upper);
        return m;
    }();
    const bool retriable_method = upper == "GET" || upper == "DELETE";
    const bool retriable_status =
        !status || *status == 500 || *status == 502 || *status == 503 || *status == 504;
    return retries_left > 0 && retriable_method && retriable_status;
}

std::vector<RestApiRateLimit> parse_rate_limit_headers(const Headers& headers) {
    std::vector<RestApiRateLimit> out;
    std::optional<std::uint32_t> retry_after;

    for (const auto& [raw_name, value] : headers) {
        if (to_lower(raw_name) == "retry-after") {
            const auto parsed = parse_u32_or(trim(value), UINT32_MAX);
            if (parsed != UINT32_MAX) {
                retry_after = parsed;
            }
        }
    }

    for (const auto& [raw_name, value] : headers) {
        const auto name = to_lower(raw_name);
        constexpr std::string_view kWeight = "x-mbx-used-weight-";
        constexpr std::string_view kOrders = "x-mbx-order-count-";
        RateLimitType type{};
        std::string_view rest;
        if (name.starts_with(kWeight)) {
            type = RateLimitType::RequestWeight;
            rest = std::string_view(name).substr(kWeight.size());
        } else if (name.starts_with(kOrders)) {
            type = RateLimitType::Orders;
            rest = std::string_view(name).substr(kOrders.size());
        } else {
            continue;
        }
        if (rest.size() < 2) {
            continue;
        }
        const auto digits = rest.substr(0, rest.size() - 1);
        if (!std::all_of(digits.begin(), digits.end(),
                         [](char c) { return c >= '0' && c <= '9'; })) {
            continue;
        }
        Interval interval{};
        switch (rest.back()) {
        case 's':
            interval = Interval::Second;
            break;
        case 'm':
            interval = Interval::Minute;
            break;
        case 'h':
            interval = Interval::Hour;
            break;
        case 'd':
            interval = Interval::Day;
            break;
        default:
            continue;
        }
        out.push_back(RestApiRateLimit{
            .rate_limit_type = type,
            .interval = interval,
            .interval_num = parse_u32_or(digits, 0),
            .count = parse_u32_or(trim(value), 0),
            .retry_after = retry_after,
        });
    }
    return out;
}

std::string user_agent_or_default(std::string user_agent) {
    return user_agent.empty() ? build_user_agent("common") : std::move(user_agent);
}

std::string build_user_agent(std::string_view product) {
    // NOLINTNEXTLINE(concurrency-mt-unsafe): read-only access during client construction.
    if (const char* override_ua = std::getenv("BINANCE_CONNECTOR_CPP_USER_AGENT")) {
        static const std::regex cli_skill_ua(
            R"(^binance-(?:cli|skill)(?:/[A-Za-z0-9._-]+){0,2} \([^;()]+; [^;()]+; [^;()]+\)$)");
        const std::string trimmed(trim(override_ua));
        if (std::regex_match(trimmed, cli_skill_ua)) {
            return trimmed;
        }
    }
    std::string ua = "binance-connector-cpp/";
    ua += product;
    ua += '/';
    ua += kVersion;
    ua += " (C++/" + compiler_id() + "; ";
    ua += os_id();
    ua += "; ";
    ua += arch_id();
    ua += ')';
    return ua;
}

std::optional<TimeUnit> validate_time_unit(std::string_view value) {
    if (value.empty()) {
        return std::nullopt;
    }
    if (value == "MILLISECOND" || value == "millisecond") {
        return TimeUnit::Millisecond;
    }
    if (value == "MICROSECOND" || value == "microsecond") {
        return TimeUnit::Microsecond;
    }
    throw ConfigError("time_unit must be either 'MILLISECOND' or 'MICROSECOND'");
}

std::int64_t timestamp_ms() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
               std::chrono::system_clock::now().time_since_epoch())
        .count();
}

std::int64_t timestamp_ms(const TimestampProvider& provider) {
    return provider ? provider() : timestamp_ms();
}

std::string random_string() {
    std::array<unsigned char, 16> bytes{};
    random_bytes(bytes.data(), static_cast<int>(bytes.size()));
    std::string out;
    out.reserve(32);
    for (const auto b : bytes) {
        out += kHexLower[b >> 4U];
        out += kHexLower[b & 0x0FU];
    }
    return out;
}

std::uint32_t random_integer() {
    std::array<unsigned char, 4> bytes{};
    random_bytes(bytes.data(), static_cast<int>(bytes.size()));
    return (std::uint32_t{bytes[0]} << 24U) | (std::uint32_t{bytes[1]} << 16U) |
           (std::uint32_t{bytes[2]} << 8U) | std::uint32_t{bytes[3]};
}

} // namespace detail

std::string_view to_string(RateLimitType type) noexcept {
    switch (type) {
    case RateLimitType::RequestWeight:
        return "REQUEST_WEIGHT";
    case RateLimitType::Orders:
        return "ORDERS";
    case RateLimitType::RawRequests:
        return "RAW_REQUESTS";
    }
    return "";
}

std::string_view to_string(Interval interval) noexcept {
    switch (interval) {
    case Interval::Second:
        return "SECOND";
    case Interval::Minute:
        return "MINUTE";
    case Interval::Hour:
        return "HOUR";
    case Interval::Day:
        return "DAY";
    }
    return "";
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const RestApiRateLimit& limit) {
    boost::json::object obj{{"rateLimitType", to_string(limit.rate_limit_type)},
                            {"interval", to_string(limit.interval)},
                            {"intervalNum", limit.interval_num},
                            {"count", limit.count}};
    if (limit.retry_after) {
        obj["retryAfter"] = *limit.retry_after;
    }
    jv = std::move(obj);
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const WebsocketApiRateLimit& limit) {
    jv = boost::json::object{{"rateLimitType", to_string(limit.rate_limit_type)},
                             {"interval", to_string(limit.interval)},
                             {"intervalNum", limit.interval_num},
                             {"limit", limit.limit},
                             {"count", limit.count}};
}

boost::json::value parse_json(std::string_view text) {
    boost::json::parse_options opts;
    opts.numbers = boost::json::number_precision::precise;
    boost::system::error_code ec;
    auto jv = boost::json::parse(text, ec, {}, opts);
    if (ec) {
        throw ConnectorClientError("Failed to parse JSON response: " + ec.message());
    }
    return jv;
}

namespace detail {

bool is_valid_request_id(std::string_view id) noexcept {
    return id.size() == 32 && std::all_of(id.begin(), id.end(), [](char c) {
               return kHexLower.find(c) != std::string_view::npos;
           });
}

boost::json::value normalize_stream_id(const std::optional<StreamId>& id, bool strictly_number) {
    const auto* number = id ? std::get_if<std::uint32_t>(&*id) : nullptr;
    if (strictly_number) {
        return number != nullptr ? *number : random_integer();
    }
    if (number != nullptr) {
        return *number;
    }
    if (const auto* text = id ? std::get_if<std::string>(&*id) : nullptr;
        text != nullptr && is_valid_request_id(*text)) {
        return boost::json::string(*text);
    }
    return boost::json::string(random_string());
}

Params remove_empty_value(Params params) {
    std::erase_if(params, [](const auto& entry) {
        const auto& value = entry.second;
        return value.is_null() || (value.is_string() && value.get_string().empty());
    });
    return params;
}

namespace {

std::string normalize_ws_streams_key(std::string_view key) {
    std::string out;
    for (const char c : key) {
        if (c != '_' && c != '-') {
            out += ascii_lower(c);
        }
    }
    return out;
}

} // namespace

std::string
replace_websocket_streams_placeholders(std::string_view input,
                                       const std::map<std::string, std::string>& variables,
                                       bool lowercase_head) {
    const bool leading_slash = input.starts_with('/');
    const auto body = leading_slash ? input.substr(1) : input;

    std::map<std::string, std::string> normalized;
    for (const auto& [key, value] : variables) {
        normalized[normalize_ws_streams_key(key)] = value;
    }
    const auto lookup = [&](std::string_view key) {
        const auto it = normalized.find(normalize_ws_streams_key(key));
        return it == normalized.end() ? std::string() : it->second;
    };

    // `(@)?<([^>]+)>`: the `@` before a placeholder is kept.
    std::string out;
    std::optional<std::string> head; // value of a placeholder at position 0
    std::size_t i = 0;
    while (i < body.size()) {
        const auto open = body.find('<', i);
        if (open == std::string_view::npos) {
            out.append(body.substr(i));
            break;
        }
        const auto close = body.find('>', open + 1);
        if (close == std::string_view::npos || close == open + 1) {
            out.append(body.substr(i, open + 1 - i));
            i = open + 1;
            continue;
        }
        out.append(body.substr(i, open - i));
        const auto name = body.substr(open + 1, close - open - 1);
        auto value = lookup(name);
        if (open == 0 && normalize_ws_streams_key(name) != "listenkey") {
            head = value;
        }
        out += value;
        i = close + 1;
    }
    while (out.ends_with('@')) {
        out.pop_back();
    }
    if (lowercase_head && leading_slash && head && out.starts_with(*head)) {
        for (std::size_t k = 0; k < head->size(); ++k) {
            out[k] = ascii_lower(out[k]);
        }
    }
    return out;
}

std::string replace_websocket_streams_placeholders_preserve_case(
    std::string_view input, const std::map<std::string, std::string>& variables) {
    return replace_websocket_streams_placeholders(input, variables, false);
}

std::pair<std::string, boost::json::object>
build_websocket_api_message(const WebsocketApiConfig& configuration,
                            const SignatureGenerator& signer, std::string_view method,
                            Params payload, const WebsocketMessageSendOptions& options,
                            bool skip_auth) {
    std::string id;
    if (const auto it = payload.find("id"); it != payload.end()) {
        if (it->second.is_string() && is_valid_request_id(it->second.get_string())) {
            id = std::string(it->second.get_string());
        }
        payload.erase(it);
    }
    if (id.empty()) {
        id = random_string();
    }

    // Doubles, nested ones included, are sent as their plain-notation text: the request JSON
    // would otherwise carry `1E-7` while the signature covers `0.0000001`. Non-finite doubles
    // become `null` (dropped at the top level).
    for (auto& [key, value] : payload) {
        doubles_to_text(value);
        sort_object_keys(value);
    }
    auto params = remove_empty_value(std::move(payload));
    if ((options.with_api_key || options.is_signed) && !skip_auth) {
        if (!configuration.api_key) {
            throw ConnectorClientError("api_key is required for " + std::string(method));
        }
        params["apiKey"] = boost::json::string(*configuration.api_key);
    }
    if (options.is_signed) {
        params["timestamp"] = timestamp_ms(configuration.timestamp_provider);
        if (!skip_auth) {
            const auto signature = signer.sign_unencoded(params);
            params["signature"] = boost::json::string(signature);
        }
    }

    boost::json::object request;
    request["id"] = id;
    request["method"] = method;
    boost::json::object out_params;
    for (auto& [key, value] : params) {
        out_params[key] = std::move(value);
    }
    request["params"] = std::move(out_params);
    return {std::move(id), std::move(request)};
}

} // namespace detail

} // namespace binance::common
