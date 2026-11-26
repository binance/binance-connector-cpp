//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

// Transport pieces shared by the REST client and the WebSocket engine: URL parsing, proxy
// settings, DNS with a deadline, staggered TCP connects, CONNECT tunnels, TLS set-up and zlib
// decoding.

#include <chrono>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

#include <boost/asio/awaitable.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/redirect_error.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/asio/use_awaitable.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <openssl/err.h>
#include <openssl/ssl.h>
#include <openssl/x509v3.h>

#include <binance/common/config.hpp>
#include <binance/common/export.hpp>

namespace binance::common::detail {

struct Endpoint {
    bool tls = false;
    std::string host;
    std::string port;
    /// Path without a trailing `/`, e.g. `/ws-api/v3`.
    std::string prefix;
    /// Query string without the `?`.
    std::string query;

    /// `host[:port]` for a `Host` header: the port is omitted when it is the scheme's default.
    [[nodiscard]] std::string authority() const;
    /// `host:port` (IPv6 hosts in brackets) for a CONNECT request.
    [[nodiscard]] std::string host_port() const;
};

/// Parses `<plain_scheme>://…` or `<tls_scheme>://…`. Throws `ConfigError` naming `field`.
/// Credentials in the URL are rejected without being echoed.
[[nodiscard]] Endpoint parse_url(std::string_view url, std::string_view plain_scheme,
                                 std::string_view tls_scheme, std::string_view field);

/// A SOCKS5 proxy to tunnel through.
struct SocksRoute {
    Endpoint server;
    /// Gives the proxy the host name to resolve, instead of resolving it here.
    bool remote_dns = false;
    std::optional<ProxyAuth> auth;
};

/// The proxy to use for `target`, validated: an HTTP(S) one with its `Proxy-Authorization` value,
/// or a SOCKS5 one (then `proxy` is empty).
struct ProxyRoute {
    std::optional<Endpoint> proxy;
    std::string authorization;
    std::optional<SocksRoute> socks;
};

/// `configured`, or the environment's proxy when `from_env` is set. Throws `ConfigError`.
[[nodiscard]] ProxyRoute make_proxy_route(const std::optional<ProxyConfig>& configured,
                                          bool from_env, const Endpoint& target);

/// TLS 1.2+, peer verification against the system roots, then the user's `agent` hook.
void init_tls_context(boost::asio::ssl::context& ctx, const TlsContextHook& agent);

[[nodiscard]] std::string lower(std::string_view s);
[[nodiscard]] std::string base64(std::string_view in);

enum class InflateStatus { Ok, TooLarge, Invalid };

/// gzip / zlib (auto-detected) or, failing that, raw deflate, producing at most `limit` bytes.
[[nodiscard]] InflateStatus inflate(std::string_view in, std::size_t limit, std::string& out);

[[noreturn]] void throw_network(const boost::system::error_code& ec, const char* what);

/// `e.what()` without the error code and source location Boost appends.
[[nodiscard]] std::string error_message(const boost::system::system_error& e);

/// Resolves with a hard deadline. `getaddrinfo` cannot be interrupted, so on timeout the lookup
/// is abandoned: its state stays alive until it returns, and the caller goes on without it.
/// Throws `boost::system::system_error`.
boost::asio::awaitable<boost::asio::ip::tcp::resolver::results_type>
resolve(const Endpoint& via, std::chrono::steady_clock::time_point deadline);

/// Opens a tunnel to `target` over `stream`, which is connected to the SOCKS5 server: the method
/// negotiation (with username / password, RFC 1929, if `socks.auth` is set) and the CONNECT
/// request (RFC 1928). Without `socks.remote_dns`, a host name is first resolved before
/// `deadline`, and the first address is used. The stream's own timeout bounds each read and write.
/// Throws `boost::system::system_error`, whose code maps the SOCKS reply (e.g.
/// `connection_refused`, `access_denied` for a failed authentication).
boost::asio::awaitable<void> socks5_connect(boost::beast::tcp_stream& stream,
                                            const Endpoint& target, const SocksRoute& socks,
                                            std::chrono::steady_clock::time_point deadline);

/// Delay before the next address is tried while the earlier attempts are still pending.
inline constexpr std::chrono::milliseconds connection_attempt_delay{250};

/// The addresses ordered for `connect_staggered`: IPv6 and IPv4 alternate, starting with the
/// family the resolver returned first; the order within a family is kept.
[[nodiscard]] BINANCE_COMMON_EXPORT std::vector<boost::asio::ip::tcp::endpoint>
interleave_families(const boost::asio::ip::tcp::resolver::results_type& results);

/// Connects `socket` to the first of `endpoints` that answers. The first attempt starts at once;
/// each next one starts when the previous failed or after `connection_attempt_delay`, without
/// cancelling those in progress. The first to connect wins and the others are closed. All share
/// the one `deadline`. Throws `boost::system::system_error`: `beast::error::timeout` at the
/// deadline, otherwise the error of the last attempt to fail.
BINANCE_COMMON_EXPORT boost::asio::awaitable<void>
connect_staggered(boost::asio::ip::tcp::socket& socket,
                  std::vector<boost::asio::ip::tcp::endpoint> endpoints,
                  std::chrono::steady_clock::time_point deadline);

/// Sends `CONNECT target` and reads the reply. Returns the status code; any 2xx means the tunnel
/// is open. Throws `boost::system::system_error` on transport failure.
template <class Stream>
boost::asio::awaitable<unsigned> proxy_connect(Stream& stream, boost::beast::flat_buffer& buffer,
                                               const Endpoint& target,
                                               const std::string& authorization) {
    namespace asio = boost::asio;
    namespace http = boost::beast::http;
    const auto authority = target.host_port();
    http::request<http::empty_body> req{http::verb::connect, authority, 11};
    req.set(http::field::host, authority);
    if (!authorization.empty()) {
        req.set(http::field::proxy_authorization, authorization);
    }
    boost::system::error_code ec;
    co_await http::async_write(stream, req, asio::redirect_error(asio::use_awaitable, ec));
    if (ec) {
        throw_network(ec, "proxy CONNECT");
    }
    http::response_parser<http::empty_body> parser;
    parser.skip(true);
    co_await http::async_read(stream, buffer, parser,
                              asio::redirect_error(asio::use_awaitable, ec));
    if (ec) {
        throw_network(ec, "proxy CONNECT");
    }
    buffer.clear();
    co_return parser.get().result_int();
}

/// Client handshake with SNI (for host names only, RFC 6066 section 3) and host name
/// verification. Throws `boost::system::system_error`.
template <class Stream>
boost::asio::awaitable<void> tls_handshake(Stream& stream, const std::string& host,
                                           const char* what) {
    namespace asio = boost::asio;
    // OpenSSL checks the name itself, so a verify callback set by the `agent` hook (pinning)
    // still runs.
    SSL* ssl = stream.native_handle();
    boost::system::error_code ec;
    (void)asio::ip::make_address(host, ec);
    const bool is_host_name = static_cast<bool>(ec);
    const bool ok = is_host_name
                        ? SSL_set_tlsext_host_name(ssl, host.c_str()) == 1 &&
                              SSL_set1_host(ssl, host.c_str()) == 1
                        : X509_VERIFY_PARAM_set1_ip_asc(SSL_get0_param(ssl), host.c_str()) == 1;
    if (!ok) {
        throw_network(boost::system::error_code(static_cast<int>(::ERR_get_error()),
                                                asio::error::get_ssl_category()),
                      what);
    }
    SSL_set_hostflags(ssl, X509_CHECK_FLAG_NO_PARTIAL_WILDCARDS);
    ec = {};
    co_await stream.async_handshake(asio::ssl::stream_base::client,
                                    asio::redirect_error(asio::use_awaitable, ec));
    if (ec) {
        throw_network(ec, what);
    }
}

} // namespace binance::common::detail
