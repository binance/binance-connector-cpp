//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include "net.hpp"

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <string_view>

#include <boost/asio/read.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/asio/this_coro.hpp>
#include <boost/asio/write.hpp>
#include <openssl/evp.h>
#include <zlib.h>

#include <binance/common/errors.hpp>
#include <binance/common/logger.hpp>

#include "tls.hpp"

namespace binance::common::detail {

namespace asio = boost::asio;
namespace beast = boost::beast;
using tcp = asio::ip::tcp;

std::string Endpoint::authority() const {
    const bool v6 = host.find(':') != std::string::npos;
    std::string out = v6 ? "[" + host + "]" : host;
    if (port != (tls ? "443" : "80")) {
        out += ":" + port;
    }
    return out;
}

std::string Endpoint::host_port() const {
    return host.find(':') != std::string::npos ? "[" + host + "]:" + port : host + ":" + port;
}

Endpoint parse_url(std::string_view url, std::string_view plain_scheme, std::string_view tls_scheme,
                   std::string_view field) {
    const auto invalid = [&] {
        return ConfigError("Configuration missing or invalid `" + std::string(field) + "`: '" +
                           std::string(url) + "'");
    };
    Endpoint out;
    std::string_view rest;
    const auto scheme_end = url.find("://");
    if (scheme_end == std::string_view::npos) {
        throw invalid();
    }
    const auto scheme = lower(url.substr(0, scheme_end));
    if (scheme == tls_scheme) {
        out.tls = true;
    } else if (scheme != plain_scheme) {
        throw invalid();
    }
    rest = url.substr(scheme_end + 3);
    const auto slash = rest.find_first_of("/?#");
    const auto authority = rest.substr(0, slash);
    if (authority.find('@') != std::string_view::npos) {
        // Not echoed: the userinfo may be a password.
        throw ConfigError("Configuration missing or invalid `" + std::string(field) +
                          "`: credentials in the URL are not supported");
    }
    if (slash != std::string_view::npos) {
        auto tail = rest.substr(slash);
        tail = tail.substr(0, tail.find('#'));
        const auto q = tail.find('?');
        if (q != std::string_view::npos) {
            out.query = std::string(tail.substr(q + 1));
            tail = tail.substr(0, q);
        }
        while (tail.ends_with('/')) {
            tail.remove_suffix(1);
        }
        out.prefix = std::string(tail);
    }
    std::string_view port;
    if (authority.starts_with('[')) {
        const auto close = authority.find(']');
        if (close == std::string_view::npos) {
            throw invalid();
        }
        out.host = std::string(authority.substr(1, close - 1));
        const auto after = authority.substr(close + 1);
        if (!after.empty()) {
            if (after.front() != ':') {
                throw invalid();
            }
            port = after.substr(1);
        }
    } else {
        const auto colon = authority.rfind(':');
        out.host = std::string(authority.substr(0, colon));
        if (colon != std::string_view::npos) {
            port = authority.substr(colon + 1);
        }
    }
    if (out.host.empty() || port.size() > 5 ||
        !std::all_of(port.begin(), port.end(), [](char c) { return c >= '0' && c <= '9'; }) ||
        (!port.empty() &&
         (std::stoul(std::string(port)) == 0 || std::stoul(std::string(port)) > 65535))) {
        throw invalid();
    }
    if (port.empty()) {
        out.port = out.tls ? "443" : "80";
    } else {
        out.port = std::string(port);
    }
    return out;
}

ProxyRoute make_proxy_route(const std::optional<ProxyConfig>& configured, bool from_env,
                            const Endpoint& target) {
    ProxyRoute route;
    auto proxy_cfg = configured;
    if (!proxy_cfg && from_env) {
        proxy_cfg = proxy_from_environment(target.tls, target.host,
                                           static_cast<std::uint16_t>(std::stoul(target.port)));
        if (proxy_cfg) {
            Logger::debug("Using proxy " + std::string(to_string(proxy_cfg->protocol)) + "://" +
                          proxy_cfg->host + ":" + std::to_string(proxy_cfg->port) +
                          " from the environment");
        }
    }
    if (!proxy_cfg) {
        return route;
    }
    if (proxy_cfg->host.empty() || proxy_cfg->port == 0) {
        throw ConfigError("Configuration missing or invalid `proxy`");
    }
    if (proxy_cfg->protocol == ProxyProtocol::Socks5 ||
        proxy_cfg->protocol == ProxyProtocol::Socks5h) {
        if (proxy_cfg->auth &&
            (proxy_cfg->auth->username.size() > 255 || proxy_cfg->auth->password.size() > 255)) {
            throw ConfigError("Configuration invalid `proxy`: a SOCKS5 username and password "
                              "are at most 255 bytes each");
        }
        route.socks =
            SocksRoute{Endpoint{false, proxy_cfg->host, std::to_string(proxy_cfg->port), {}, {}},
                       proxy_cfg->protocol == ProxyProtocol::Socks5h, proxy_cfg->auth};
        return route;
    }
    route.proxy = Endpoint{proxy_cfg->protocol == ProxyProtocol::Https,
                           proxy_cfg->host,
                           std::to_string(proxy_cfg->port),
                           {},
                           {}};
    if (proxy_cfg->auth) {
        route.authorization =
            "Basic " + base64(proxy_cfg->auth->username + ":" + proxy_cfg->auth->password);
    }
    return route;
}

void init_tls_context(asio::ssl::context& ctx, const TlsContextHook& agent) {
    SSL_CTX_set_min_proto_version(ctx.native_handle(), TLS1_2_VERSION);
    ctx.set_verify_mode(asio::ssl::verify_peer);
    load_system_root_certificates(ctx.native_handle());
    if (agent) {
        agent(ctx);
    }
}

std::string lower(std::string_view s) {
    // ASCII only: `std::tolower` depends on the C locale.
    std::string out(s);
    std::transform(out.begin(), out.end(), out.begin(), [](char c) {
        return c >= 'A' && c <= 'Z' ? static_cast<char>(c - 'A' + 'a') : c;
    });
    return out;
}

std::string base64(std::string_view in) {
    std::string out(4 * ((in.size() + 2) / 3), '\0');
    const int n = EVP_EncodeBlock(reinterpret_cast<unsigned char*>(out.data()),
                                  reinterpret_cast<const unsigned char*>(in.data()),
                                  static_cast<int>(in.size()));
    out.resize(static_cast<std::size_t>(n));
    return out;
}

InflateStatus inflate(std::string_view in, std::size_t limit, std::string& out) {
    for (const int window_bits : {MAX_WBITS + 32, -MAX_WBITS}) {
        z_stream zs{};
        if (inflateInit2(&zs, window_bits) != Z_OK) {
            break;
        }
        zs.next_in = reinterpret_cast<Bytef*>(const_cast<char*>(in.data()));
        zs.avail_in = static_cast<uInt>(in.size());
        out.clear();
        std::array<char, std::size_t{64} * 1024> chunk{};
        int rc = Z_OK;
        do {
            zs.next_out = reinterpret_cast<Bytef*>(chunk.data());
            zs.avail_out = static_cast<uInt>(chunk.size());
            rc = ::inflate(&zs, Z_NO_FLUSH);
            out.append(chunk.data(), chunk.size() - zs.avail_out);
            if (out.size() > limit) {
                inflateEnd(&zs);
                out.clear();
                return InflateStatus::TooLarge;
            }
        } while (rc == Z_OK);
        inflateEnd(&zs);
        if (rc == Z_STREAM_END) {
            return InflateStatus::Ok;
        }
    }
    out.clear();
    return InflateStatus::Invalid;
}

void throw_network(const boost::system::error_code& ec, const char* what) {
    throw boost::system::system_error(ec, what);
}

std::string error_message(const boost::system::system_error& e) {
    std::string msg = e.what();
    if (const auto pos = msg.rfind(" [" + e.code().to_string()); pos != std::string::npos) {
        msg.erase(pos);
    }
    return msg;
}

namespace {

[[noreturn]] void socks_fail(boost::system::error_code ec, const std::string& what) {
    throw boost::system::system_error(ec, "SOCKS5 proxy: " + what);
}

/// The transport error and text for a failure reply (RFC 1928 section 6).
[[noreturn]] void socks_reply_failed(std::uint8_t code) {
    static constexpr std::string_view kHex = "0123456789abcdef";
    const std::string suffix =
        std::string(" (reply 0x") + kHex[code >> 4] + kHex[code & 0x0F] + ")";
    switch (code) {
    case 1:
        socks_fail(asio::error::connection_aborted, "general failure" + suffix);
    case 2:
        socks_fail(asio::error::no_permission, "connection not allowed by the ruleset" + suffix);
    case 3:
        socks_fail(asio::error::network_unreachable, "network unreachable" + suffix);
    case 4:
        socks_fail(asio::error::host_unreachable, "host unreachable" + suffix);
    case 5:
        socks_fail(asio::error::connection_refused, "the target refused the connection" + suffix);
    case 6:
        socks_fail(asio::error::timed_out, "TTL expired" + suffix);
    case 7:
        socks_fail(asio::error::operation_not_supported, "command not supported" + suffix);
    case 8:
        socks_fail(asio::error::address_family_not_supported,
                   "address type not supported" + suffix);
    default:
        socks_fail(make_error_code(boost::system::errc::protocol_error),
                   "unknown failure" + suffix);
    }
}

asio::awaitable<void> socks_write(beast::tcp_stream& stream, const std::string& data,
                                  const char* what) {
    boost::system::error_code ec;
    co_await asio::async_write(stream, asio::buffer(data),
                               asio::redirect_error(asio::use_awaitable, ec));
    if (ec) {
        socks_fail(ec, std::string("writing the ") + what);
    }
}

asio::awaitable<std::string> socks_read(beast::tcp_stream& stream, std::size_t size,
                                        const char* what) {
    std::string data(size, '\0');
    boost::system::error_code ec;
    co_await asio::async_read(stream, asio::buffer(data),
                              asio::redirect_error(asio::use_awaitable, ec));
    if (ec) {
        socks_fail(ec, std::string("reading the ") + what);
    }
    co_return data;
}

std::uint8_t byte(const std::string& data, std::size_t i) {
    return static_cast<std::uint8_t>(data[i]);
}

} // namespace

asio::awaitable<void> socks5_connect(beast::tcp_stream& stream, const Endpoint& target,
                                     const SocksRoute& socks,
                                     std::chrono::steady_clock::time_point deadline) {
    const auto protocol_error = [](const char* what) {
        socks_fail(make_error_code(boost::system::errc::protocol_error), what);
    };

    // Method negotiation: "no authentication", and username / password when we have them.
    // No conditional builds the greeting inside the co_await: GCC 12 destroys the temporaries of
    // both branches of such a conditional, one of which was never constructed.
    std::string greeting("\x05\x01\x00", 3);
    if (socks.auth) {
        greeting.assign("\x05\x02\x00\x02", 4);
    }
    co_await socks_write(stream, greeting, "method request");
    const auto method = co_await socks_read(stream, 2, "method reply");
    if (byte(method, 0) != 5) {
        protocol_error("the reply is not a SOCKS5 one");
    }
    if (byte(method, 1) == 0xFF) {
        socks_fail(asio::error::access_denied, "no acceptable authentication method");
    }
    if (byte(method, 1) == 0x02 && socks.auth) {
        const auto& auth = *socks.auth;
        std::string request = "\x01";
        request += static_cast<char>(auth.username.size());
        request += auth.username;
        request += static_cast<char>(auth.password.size());
        request += auth.password;
        co_await socks_write(stream, request, "credentials");
        const auto status = co_await socks_read(stream, 2, "authentication reply");
        if (byte(status, 0) != 1) {
            protocol_error("the authentication reply is malformed");
        }
        if (byte(status, 1) != 0) {
            socks_fail(asio::error::access_denied, "authentication failed");
        }
    } else if (byte(method, 1) != 0x00) {
        socks_fail(asio::error::access_denied, "the proxy chose an authentication method that was "
                                               "not offered");
    }

    // CONNECT request.
    std::string request("\x05\x01\x00", 3);
    const auto port = static_cast<std::uint16_t>(std::stoul(target.port));
    boost::system::error_code ec;
    auto address = asio::ip::make_address(target.host, ec);
    if (ec && !socks.remote_dns) {
        const auto results = co_await resolve(target, deadline);
        address = results.begin()->endpoint().address();
        ec = {};
    }
    if (!ec) {
        if (address.is_v4()) {
            request += '\x01';
            const auto bytes = address.to_v4().to_bytes();
            request.append(bytes.begin(), bytes.end());
        } else {
            request += '\x04';
            const auto bytes = address.to_v6().to_bytes();
            request.append(bytes.begin(), bytes.end());
        }
    } else {
        if (target.host.size() > 255) {
            socks_fail(asio::error::invalid_argument, "the host name is longer than 255 bytes");
        }
        request += '\x03';
        request += static_cast<char>(target.host.size());
        request += target.host;
    }
    request += static_cast<char>(port >> 8);
    request += static_cast<char>(port & 0xFF);
    co_await socks_write(stream, request, "connect request");

    const auto head = co_await socks_read(stream, 4, "connect reply");
    if (byte(head, 0) != 5) {
        protocol_error("the reply is not a SOCKS5 one");
    }
    if (byte(head, 1) != 0) {
        socks_reply_failed(byte(head, 1));
    }
    // The bound address is of no use; it is read so that the tunnel starts after it.
    std::size_t bound = 0;
    switch (byte(head, 3)) {
    case 1:
        bound = 4;
        break;
    case 4:
        bound = 16;
        break;
    case 3: {
        const auto length = co_await socks_read(stream, 1, "bound address");
        bound = byte(length, 0);
        break;
    }
    default:
        protocol_error("the reply has an unknown address type");
    }
    (void)co_await socks_read(stream, bound + 2, "bound address");
}

asio::awaitable<tcp::resolver::results_type>
resolve(const Endpoint& via, std::chrono::steady_clock::time_point deadline) {
    struct State {
        explicit State(const asio::any_io_executor& ex) : resolver(ex), timer(ex) {}
        tcp::resolver resolver;
        asio::steady_timer timer;
        boost::system::error_code ec;
        tcp::resolver::results_type results;
        bool done = false;
    };
    if (deadline <= std::chrono::steady_clock::now()) {
        throw_network(beast::error::timeout, "resolve");
    }
    auto state = std::make_shared<State>(co_await asio::this_coro::executor);
    state->timer.expires_at(deadline);
    state->resolver.async_resolve(
        via.host, via.port,
        [state](const boost::system::error_code& ec, tcp::resolver::results_type results) {
            state->ec = ec;
            state->results = std::move(results);
            state->done = true;
            state->timer.cancel();
        });
    boost::system::error_code ec;
    co_await state->timer.async_wait(asio::redirect_error(asio::use_awaitable, ec));
    if (!state->done) {
        state->resolver.cancel();
        throw_network(ec == asio::error::operation_aborted
                          ? boost::system::error_code(asio::error::operation_aborted)
                          : boost::system::error_code(beast::error::timeout),
                      "resolve");
    }
    if (state->ec) {
        throw_network(state->ec, "resolve");
    }
    co_return state->results;
}

std::vector<tcp::endpoint> interleave_families(const tcp::resolver::results_type& results) {
    std::vector<tcp::endpoint> first;
    std::vector<tcp::endpoint> second;
    for (const auto& entry : results) {
        const auto ep = entry.endpoint();
        (first.empty() || ep.protocol() == first.front().protocol() ? first : second).push_back(ep);
    }
    std::vector<tcp::endpoint> out;
    out.reserve(first.size() + second.size());
    for (std::size_t i = 0; i < std::max(first.size(), second.size()); ++i) {
        if (i < first.size()) {
            out.push_back(first[i]);
        }
        if (i < second.size()) {
            out.push_back(second[i]);
        }
    }
    return out;
}

asio::awaitable<void> connect_staggered(tcp::socket& socket, std::vector<tcp::endpoint> endpoints,
                                        std::chrono::steady_clock::time_point deadline) {
    using Clock = std::chrono::steady_clock;
    constexpr auto kNone = static_cast<std::size_t>(-1);
    struct State {
        explicit State(const asio::any_io_executor& ex) : timer(ex) {}
        asio::steady_timer timer;
        std::vector<std::unique_ptr<tcp::socket>> sockets;
        std::size_t pending = 0;
        std::size_t winner = kNone;
        boost::system::error_code last;
        bool failed = false; // an attempt failed since the last one started
        bool woken = false;  // the timer was cancelled by an attempt, not by the caller
    };
    if (endpoints.empty()) {
        throw_network(asio::error::host_not_found, "connect");
    }
    const auto executor = socket.get_executor();
    const auto state = std::make_shared<State>(executor);
    const auto close_all = [&state] {
        for (auto& s : state->sockets) {
            boost::system::error_code ignored;
            // NOLINTNEXTLINE(bugprone-unused-return-value): the error is in `ignored`.
            s->close(ignored);
        }
    };
    std::size_t next = 0;
    auto next_start = Clock::now();
    while (state->winner == kNone) {
        const auto now = Clock::now();
        if (state->pending == 0 && next == endpoints.size()) {
            close_all();
            throw_network(state->last, "connect");
        }
        if (now >= deadline) {
            close_all();
            throw_network(beast::error::timeout, "connect");
        }
        if (next < endpoints.size() &&
            (state->failed || state->pending == 0 || now >= next_start)) {
            const auto index = state->sockets.size();
            state->failed = false;
            next_start = now + connection_attempt_delay;
            auto& attempt = *state->sockets.emplace_back(std::make_unique<tcp::socket>(executor));
            ++state->pending;
            attempt.async_connect(endpoints[next++],
                                  [state, index](const boost::system::error_code& e) {
                                      --state->pending;
                                      if (!e) {
                                          if (state->winner == kNone) {
                                              state->winner = index;
                                          }
                                      } else if (e != asio::error::operation_aborted) {
                                          state->last = e;
                                          state->failed = true;
                                      }
                                      state->woken = true;
                                      state->timer.cancel();
                                  });
            continue;
        }
        state->woken = false;
        state->timer.expires_at(next < endpoints.size() ? std::min(next_start, deadline)
                                                        : deadline);
        boost::system::error_code ec;
        co_await state->timer.async_wait(asio::redirect_error(asio::use_awaitable, ec));
        if (ec == asio::error::operation_aborted && !state->woken) {
            close_all();
            throw_network(ec, "connect");
        }
    }
    socket = std::move(*state->sockets[state->winner]);
    close_all();
}

} // namespace binance::common::detail
