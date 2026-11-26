//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <algorithm>
#include <charconv>
#include <cmath>
#include <stdexcept>
#include <string_view>
#include <system_error>
#include <utility>

#include <boost/json/parse.hpp>
#include <boost/json/serialize.hpp>
#include <boost/json/value.hpp>

#include <binance/common/decimal.hpp>
#include <binance/common/detail/utils.hpp>

#include "utils.hpp"

namespace binance::common {

namespace {

constexpr long kMaxExponent = 1000;

[[noreturn]] void invalid(std::string_view text) {
    throw std::invalid_argument("Invalid decimal: '" + std::string(text) + "'");
}

bool is_digit(char c) {
    return c >= '0' && c <= '9';
}

std::string canonicalize(std::string_view text) {
    std::size_t i = 0;
    bool negative = false;
    if (i < text.size() && (text[i] == '-' || text[i] == '+')) {
        negative = text[i] == '-';
        ++i;
    }

    std::string digits;
    long point = 0; // position of the decimal point inside `digits`
    bool any_digit = false;
    while (i < text.size() && is_digit(text[i])) {
        digits += text[i++];
        any_digit = true;
    }
    point = static_cast<long>(digits.size());
    if (i < text.size() && text[i] == '.') {
        ++i;
        while (i < text.size() && is_digit(text[i])) {
            digits += text[i++];
            any_digit = true;
        }
    }
    if (!any_digit) {
        invalid(text);
    }
    if (i < text.size() && (text[i] == 'e' || text[i] == 'E')) {
        ++i;
        long exponent = 0;
        const auto* first = text.data() + i;
        const auto* last = text.data() + text.size();
        if (first != last && (*first == '+' || *first == '-') && first + 1 != last &&
            !is_digit(first[1])) {
            invalid(text); // "1e+-5", "1e--5"
        }
        if (first != last && *first == '+') {
            ++first;
        }
        auto [ptr, ec] = std::from_chars(first, last, exponent);
        if (ec != std::errc{} || ptr != last || exponent > kMaxExponent ||
            exponent < -kMaxExponent) {
            invalid(text);
        }
        point += exponent;
        i = text.size();
    }
    if (i != text.size()) {
        invalid(text);
    }

    std::size_t lead = 0;
    while (lead < digits.size() && digits[lead] == '0') {
        ++lead;
    }
    digits.erase(0, lead);
    point -= static_cast<long>(lead);
    while (!digits.empty() && digits.back() == '0') {
        digits.pop_back();
    }
    if (digits.empty()) {
        return "0";
    }

    std::string out = negative ? "-" : "";
    const auto len = static_cast<long>(digits.size());
    if (point <= 0) {
        out += "0.";
        out.append(static_cast<std::size_t>(-point), '0');
        out += digits;
    } else if (point >= len) {
        out += digits;
        out.append(static_cast<std::size_t>(point - len), '0');
    } else {
        out.append(digits, 0, static_cast<std::size_t>(point));
        out += '.';
        out.append(digits, static_cast<std::size_t>(point));
    }
    return out;
}

} // namespace

Decimal::Decimal(std::string_view text) : repr_(canonicalize(text)) {}

Decimal::Decimal(const char* text) {
    if (text == nullptr) {
        throw std::invalid_argument("Invalid decimal: null pointer");
    }
    repr_ = canonicalize(text);
}

Decimal::Decimal(double value) {
    if (!std::isfinite(value)) {
        throw std::invalid_argument("Invalid decimal: non-finite double");
    }
    // Boost.JSON writes the shortest round-trip digits in exponent form (`1.5E-7`), independently
    // of the locale and of the platform's floating-point charconv support.
    const auto scientific = boost::json::serialize(boost::json::value(value));
    constexpr double kTwoPow53 = 9007199254740992.0;
    if (std::fabs(value) >= kTwoPow53) {
        // An integer this large keeps all its exact digits when they are no longer than the
        // exponent form (`-1.2345e+17`): the shortest text, ties going to plain digits.
        const auto mantissa = scientific.substr(0, scientific.find('E'));
        const auto exponent = std::string_view(scientific).substr(mantissa.size() + 1);
        const bool negative_exponent = exponent.starts_with('-');
        const auto exponent_digits = exponent.size() - (negative_exponent ? 1 : 0);
        const auto scientific_size =
            mantissa.size() + 2 + std::max<std::size_t>(exponent_digits, 2);
        auto exact = detail::format_double(value);
        if (exact.size() <= scientific_size) {
            repr_ = std::move(exact);
            return;
        }
    }
    repr_ = canonicalize(scientific);
}

std::strong_ordering operator<=>(const Decimal& a, const Decimal& b) noexcept {
    const std::string_view x = a.str();
    const std::string_view y = b.str();
    const bool x_negative = x.starts_with('-');
    const bool y_negative = y.starts_with('-');
    if (x_negative != y_negative) {
        return x_negative ? std::strong_ordering::less : std::strong_ordering::greater;
    }
    // Compare magnitudes: integer part by length then digits, then the fraction digit by digit.
    const auto magnitude = [](std::string_view s, bool negative) {
        if (negative) {
            s.remove_prefix(1);
        }
        const auto point = s.find('.');
        return std::pair{s.substr(0, point), point == std::string_view::npos ? std::string_view()
                                                                             : s.substr(point + 1)};
    };
    const auto [xi, xf] = magnitude(x, x_negative);
    const auto [yi, yf] = magnitude(y, y_negative);
    auto order = xi.size() <=> yi.size();
    if (order == 0) {
        order = xi.compare(yi) <=> 0;
    }
    if (order == 0) {
        // Canonical fractions have no trailing zeros, so a plain comparison is numeric.
        order = xf.compare(yf) <=> 0;
    }
    return x_negative ? 0 <=> order : order;
}

double Decimal::to_double() const {
    // The canonical form is a valid JSON number. Precise parsing rounds correctly, independently
    // of the locale and of the platform's floating-point charconv support.
    boost::json::parse_options opts;
    opts.numbers = boost::json::number_precision::precise;
    boost::system::error_code ec;
    const auto jv = boost::json::parse(repr_, ec, {}, opts);
    if (ec) {
        throw std::invalid_argument("Invalid decimal: cannot convert '" + repr_ +
                                    "' to double: " + ec.message());
    }
    if (jv.is_int64()) {
        return static_cast<double>(jv.get_int64());
    }
    if (jv.is_uint64()) {
        return static_cast<double>(jv.get_uint64());
    }
    // Values beyond the range of a double come back as infinity, or as zero, which keeps the sign.
    const double out = jv.get_double();
    return out == 0.0 && repr_.front() == '-' ? -0.0 : out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv, const Decimal& d) {
    jv = d.str();
}

Decimal tag_invoke(boost::json::value_to_tag<Decimal> /*tag*/, const boost::json::value& jv) {
    switch (jv.kind()) {
    case boost::json::kind::string:
        return Decimal(std::string_view(jv.get_string()));
    case boost::json::kind::int64:
        return Decimal(jv.get_int64());
    case boost::json::kind::uint64:
        return Decimal(jv.get_uint64());
    case boost::json::kind::double_:
        return Decimal(jv.get_double());
    default:
        throw std::invalid_argument("Invalid decimal: expected a JSON string or number");
    }
}

} // namespace binance::common
