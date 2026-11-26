//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <algorithm>
#include <charconv>
#include <cstdlib>
#include <ostream>

#include <binance/common/config.hpp>
#include <binance/common/errors.hpp>
#include <binance/common/logger.hpp>

namespace binance::common {

namespace {

constexpr const char* kRedacted = "[REDACTED]";

template <class T> void print_secret(std::ostream& os, const std::optional<T>& v) {
    os << (v ? kRedacted : "None");
}

void print_opt(std::ostream& os, const std::optional<std::string>& v) {
    if (v) {
        os << '"' << *v << '"';
    } else {
        os << "None";
    }
}

void print_proxy(std::ostream& os, const std::optional<ProxyConfig>& proxy) {
    if (!proxy) {
        os << "None";
        return;
    }
    os << "{ host: \"" << proxy->host << "\", port: " << proxy->port << ", protocol: \""
       << to_string(proxy->protocol) << "\", auth: ";
    if (proxy->auth) {
        os << "{ username: \"" << proxy->auth->username << "\", password: " << kRedacted << " }";
    } else {
        os << "None";
    }
    os << " }";
}

void print_time_unit(std::ostream& os, const std::optional<TimeUnit>& unit) {
    if (unit) {
        os << to_lower_string(*unit);
    } else {
        os << "None";
    }
}

void print_mode(std::ostream& os, const WebsocketMode& mode) {
    if (mode.is_pool()) {
        os << "Pool(" << mode.pool_size() << ")";
    } else {
        os << "Single";
    }
}

const char* env(const char* name) {
    const char* value = std::getenv(name); // NOLINT(concurrency-mt-unsafe)
    return value != nullptr && *value != '\0' ? value : nullptr;
}

// ASCII only: `std::tolower` and `std::isspace` depend on the C locale.
std::string lower(std::string_view s) {
    std::string out(s);
    std::transform(out.begin(), out.end(), out.begin(), [](char c) {
        return c >= 'A' && c <= 'Z' ? static_cast<char>(c - 'A' + 'a') : c;
    });
    return out;
}

bool is_space(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v';
}

std::string_view trim(std::string_view s) {
    while (!s.empty() && is_space(s.front())) {
        s.remove_prefix(1);
    }
    while (!s.empty() && is_space(s.back())) {
        s.remove_suffix(1);
    }
    return s;
}

std::string percent_decode(std::string_view in) {
    std::string out;
    out.reserve(in.size());
    for (std::size_t i = 0; i < in.size(); ++i) {
        unsigned value = 0;
        if (in[i] == '%' && i + 2 < in.size() &&
            std::from_chars(in.data() + i + 1, in.data() + i + 3, value, 16).ptr ==
                in.data() + i + 3) {
            out += static_cast<char>(value);
            i += 2;
        } else {
            out += in[i];
        }
    }
    return out;
}

/// Splits `host[:port]` / `[v6][:port]`. A bare IPv6 address (more than one `:`) has no port.
/// Returns false when the port is not a number.
bool split_host_port(std::string_view authority, std::string& host,
                     std::optional<std::uint16_t>& port) {
    std::string_view port_text;
    if (authority.starts_with('[')) {
        const auto close = authority.find(']');
        if (close == std::string_view::npos) {
            return false;
        }
        host = std::string(authority.substr(1, close - 1));
        const auto after = authority.substr(close + 1);
        if (after.starts_with(':')) {
            port_text = after.substr(1);
        } else if (!after.empty()) {
            return false;
        }
    } else if (authority.find(':') != authority.rfind(':')) {
        host = std::string(authority);
    } else {
        const auto colon = authority.rfind(':');
        host = std::string(authority.substr(0, colon));
        if (colon != std::string_view::npos) {
            port_text = authority.substr(colon + 1);
        }
    }
    if (!port_text.empty()) {
        std::uint16_t value = 0;
        const auto [ptr, ec] =
            std::from_chars(port_text.data(), port_text.data() + port_text.size(), value);
        if (ec != std::errc{} || ptr != port_text.data() + port_text.size() || value == 0) {
            return false;
        }
        port = value;
    }
    return !host.empty();
}

bool no_proxy_matches(std::string_view list, std::string_view host, std::uint16_t port) {
    const auto target = lower(host);
    while (!list.empty()) {
        const auto comma = list.find(',');
        auto entry = trim(list.substr(0, comma));
        list = comma == std::string_view::npos ? std::string_view{} : list.substr(comma + 1);
        if (entry.empty()) {
            continue;
        }
        if (entry == "*") {
            return true;
        }
        std::string name;
        std::optional<std::uint16_t> entry_port;
        if (!split_host_port(entry, name, entry_port)) {
            name = std::string(entry);
        }
        if (entry_port && *entry_port != port) {
            continue;
        }
        auto pattern = lower(name);
        if (pattern.starts_with("*.")) {
            pattern.erase(0, 1);
        }
        if (pattern.starts_with('.')) {
            pattern.erase(0, 1);
        }
        if (target == pattern || (target.size() > pattern.size() && target.ends_with(pattern) &&
                                  target[target.size() - pattern.size() - 1] == '.')) {
            return true;
        }
    }
    return false;
}

} // namespace

std::string_view to_string(ProxyProtocol protocol) noexcept {
    switch (protocol) {
    case ProxyProtocol::Http:
        return "http";
    case ProxyProtocol::Https:
        return "https";
    case ProxyProtocol::Socks5:
        return "socks5";
    case ProxyProtocol::Socks5h:
        return "socks5h";
    }
    return "";
}

std::optional<ProxyConfig> proxy_from_environment(bool tls, std::string_view host,
                                                  std::uint16_t port) {
    if (const char* no_proxy = env("no_proxy") != nullptr ? env("no_proxy") : env("NO_PROXY");
        no_proxy != nullptr && no_proxy_matches(no_proxy, host, port)) {
        return std::nullopt;
    }
    const char* value = nullptr;
    if (tls) {
        value = env("https_proxy") != nullptr ? env("https_proxy") : env("HTTPS_PROXY");
    } else if (env("REQUEST_METHOD") == nullptr) {
        value = env("http_proxy") != nullptr ? env("http_proxy") : env("HTTP_PROXY");
    } else {
#ifndef _WIN32
        value = env("http_proxy");
#endif
    }
    if (value == nullptr) {
        value = env("all_proxy") != nullptr ? env("all_proxy") : env("ALL_PROXY");
    }
    if (value == nullptr) {
        return std::nullopt;
    }

    const auto invalid = [] {
        // The value may hold credentials, so it is not echoed.
        return ConfigError("Invalid proxy URL in the environment");
    };
    std::string_view url = trim(value);
    ProxyConfig out;
    if (const auto scheme = url.find("://"); scheme != std::string_view::npos) {
        const auto protocol = lower(url.substr(0, scheme));
        if (protocol == "http") {
            out.protocol = ProxyProtocol::Http;
        } else if (protocol == "https") {
            out.protocol = ProxyProtocol::Https;
        } else if (protocol == "socks5") {
            out.protocol = ProxyProtocol::Socks5;
        } else if (protocol == "socks5h") {
            out.protocol = ProxyProtocol::Socks5h;
        } else {
            Logger::warn("Ignoring the proxy from the environment: unsupported protocol '" +
                         protocol + "' (expected 'http', 'https', 'socks5' or 'socks5h')");
            return std::nullopt;
        }
        url.remove_prefix(scheme + 3);
    }
    url = url.substr(0, url.find_first_of("/?#"));
    if (const auto at = url.rfind('@'); at != std::string_view::npos) {
        const auto userinfo = url.substr(0, at);
        const auto colon = userinfo.find(':');
        out.auth =
            ProxyAuth{percent_decode(userinfo.substr(0, colon)),
                      colon == std::string_view::npos ? std::string()
                                                      : percent_decode(userinfo.substr(colon + 1))};
        url.remove_prefix(at + 1);
    }
    std::optional<std::uint16_t> proxy_port;
    if (!split_host_port(url, out.host, proxy_port)) {
        throw invalid();
    }
    const bool socks =
        out.protocol == ProxyProtocol::Socks5 || out.protocol == ProxyProtocol::Socks5h;
    std::uint16_t default_port = 80;
    if (socks) {
        default_port = 1080;
    } else if (out.protocol == ProxyProtocol::Https) {
        default_port = 443;
    }
    out.port = proxy_port.value_or(default_port);
    return out;
}

std::ostream& operator<<(std::ostream& os, const RestApiConfig& cfg) {
    os << "RestApiConfig { api_key: ";
    print_secret(os, cfg.api_key);
    os << ", api_secret: ";
    print_secret(os, cfg.api_secret);
    os << ", base_path: ";
    print_opt(os, cfg.base_path);
    os << ", timeout: " << cfg.timeout.count() << "ms, keep_alive: " << std::boolalpha
       << cfg.keep_alive << ", compression: " << cfg.compression
       << ", max_response_size: " << cfg.max_response_size << ", retries: " << cfg.retries
       << ", backoff: " << cfg.backoff.count() << "ms, proxy: ";
    print_proxy(os, cfg.proxy);
    os << ", proxy_from_env: " << cfg.proxy_from_env << ", custom_headers: {";
    bool first = true;
    for (const auto& header : cfg.custom_headers) {
        // Values can carry credentials (authorization, tokens), so only names are printed.
        os << (first ? " " : ", ") << '"' << header.first << "\": " << kRedacted;
        first = false;
    }
    os << (first ? "}" : " }") << ", agent: " << (cfg.agent ? "<tls context hook>" : "None")
       << ", private_key: ";
    print_secret(os, cfg.private_key);
    os << ", private_key_passphrase: ";
    print_secret(os, cfg.private_key_passphrase);
    os << ", time_unit: ";
    print_time_unit(os, cfg.time_unit);
    os << ", timestamp_provider: " << (cfg.timestamp_provider ? "<custom timestamp fn>" : "None");
    os << ", executor: " << (cfg.executor != nullptr ? "<shared>" : "<dedicated thread>") << " }";
    return os;
}

std::ostream& operator<<(std::ostream& os, const WebsocketApiConfig& cfg) {
    os << "WebsocketApiConfig { api_key: ";
    print_secret(os, cfg.api_key);
    os << ", api_secret: ";
    print_secret(os, cfg.api_secret);
    os << ", url: ";
    print_opt(os, cfg.url);
    os << ", timeout: " << cfg.timeout.count()
       << "ms, reconnect_delay: " << cfg.reconnect_delay.count()
       << "ms, connect_timeout: " << cfg.connect_timeout.count() << "ms, mode: ";
    print_mode(os, cfg.mode);
    os << ", compression: " << std::boolalpha << cfg.compression
       << ", max_message_size: " << cfg.max_message_size << ", proxy: ";
    print_proxy(os, cfg.proxy);
    os << ", proxy_from_env: " << cfg.proxy_from_env
       << ", agent: " << (cfg.agent ? "<tls context hook>" : "None") << ", private_key: ";
    print_secret(os, cfg.private_key);
    os << ", private_key_passphrase: ";
    print_secret(os, cfg.private_key_passphrase);
    os << ", time_unit: ";
    print_time_unit(os, cfg.time_unit);
    os << ", timestamp_provider: " << (cfg.timestamp_provider ? "<custom timestamp fn>" : "None");
    os << ", auto_session_relogon: " << cfg.auto_session_relogon
       << ", executor: " << (cfg.executor != nullptr ? "<shared>" : "<dedicated thread>") << " }";
    return os;
}

std::ostream& operator<<(std::ostream& os, const WebsocketStreamsConfig& cfg) {
    os << "WebsocketStreamsConfig { url: ";
    print_opt(os, cfg.url);
    os << ", reconnect_delay: " << cfg.reconnect_delay.count()
       << "ms, connect_timeout: " << cfg.connect_timeout.count() << "ms, mode: ";
    print_mode(os, cfg.mode);
    os << ", compression: " << std::boolalpha << cfg.compression
       << ", max_message_size: " << cfg.max_message_size << ", proxy: ";
    print_proxy(os, cfg.proxy);
    os << ", proxy_from_env: " << cfg.proxy_from_env
       << ", agent: " << (cfg.agent ? "<tls context hook>" : "None") << ", time_unit: ";
    print_time_unit(os, cfg.time_unit);
    os << ", timestamp_provider: " << (cfg.timestamp_provider ? "<custom timestamp fn>" : "None");
    os << ", api_key: ";
    print_secret(os, cfg.api_key);
    os << ", api_secret: ";
    print_secret(os, cfg.api_secret);
    os << ", private_key: ";
    print_secret(os, cfg.private_key);
    os << ", private_key_passphrase: ";
    print_secret(os, cfg.private_key_passphrase);
    os << ", executor: " << (cfg.executor != nullptr ? "<shared>" : "<dedicated thread>") << " }";
    return os;
}

} // namespace binance::common
