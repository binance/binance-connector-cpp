//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <iosfwd>
#include <map>
#include <optional>
#include <string>
#include <string_view>
#include <utility>

#include <boost/asio/any_io_executor.hpp>
#include <boost/asio/awaitable.hpp>
#include <boost/asio/ip/tcp.hpp>

namespace boost::asio::ssl {
class context; // NOLINT(readability-identifier-naming): forward declaration, see TlsContextHook
} // namespace boost::asio::ssl

#include <binance/common/export.hpp>
#include <binance/common/models.hpp>

namespace binance::common {

struct ProxyAuth {
    std::string username;
    std::string password;
};

/// How the SDK talks to the proxy itself.
enum class ProxyProtocol { Http, Https, Socks5, Socks5h };

/// `"http"` / `"https"` / `"socks5"` / `"socks5h"`.
[[nodiscard]] BINANCE_COMMON_EXPORT std::string_view to_string(ProxyProtocol protocol) noexcept;

/// HTTP(S) or SOCKS5 proxy.
///
/// - HTTP(S): requests to an `https://` base path go through a `CONNECT` tunnel; requests to an
///   `http://` base path are sent to the proxy in absolute form. With `ProxyProtocol::Https`, the
///   connection to the proxy itself also uses TLS. The proxy certificate is verified with the
///   same trust store and `agent` hook as the target's. `auth` is sent as Basic credentials.
/// - SOCKS5 (RFC 1928), over plain TCP, for REST and WebSockets alike: the connection to the
///   target is tunnelled, and TLS and the WebSocket upgrade run end to end over it.
///   `Socks5` resolves the target's host name in the client and gives the proxy its address;
///   `Socks5h` gives the proxy the host name to resolve. IP literals are always sent as
///   addresses. `auth` is sent as username / password (RFC 1929), each at most 255 bytes, if the
///   proxy asks for it; without `auth` only "no authentication" is offered. A refusal by the
///   proxy or the target is a network error whose transport error maps the SOCKS reply (e.g.
///   `connection_refused`, `host_unreachable`, `access_denied` for failed authentication).
struct ProxyConfig {
    std::string host;
    std::uint16_t port = 0;
    ProxyProtocol protocol = ProxyProtocol::Http;
    std::optional<ProxyAuth> auth;
};

/// A PEM private key (RSA or Ed25519), given inline or as a file path read on first use.
class PrivateKey {
public:
    [[nodiscard]] static PrivateKey from_file(std::string path) {
        return PrivateKey{Kind::File, std::move(path)};
    }
    [[nodiscard]] static PrivateKey from_pem(std::string pem) {
        return PrivateKey{Kind::Raw, std::move(pem)};
    }

    [[nodiscard]] bool is_file() const noexcept { return kind_ == Kind::File; }
    /// The file path or the PEM contents.
    [[nodiscard]] const std::string& value() const noexcept { return value_; }

private:
    enum class Kind { File, Raw };
    PrivateKey(Kind kind, std::string value) : kind_{kind}, value_{std::move(value)} {}

    Kind kind_;
    std::string value_;
};

/// Customises the TLS context before it is used: add CAs or client certificates, or pin
/// certificates. Include `<boost/asio/ssl/context.hpp>` to write one.
using TlsContextHook = std::function<void(boost::asio::ssl::context&)>;

/// Opens the TCP connection of a WebSocket instead of the SDK: connect `socket` to `host:port`
/// (e.g. through a proxy of your own), then return. The SDK then runs TLS (with `agent`) and the
/// WebSocket upgrade over it. `proxy` is ignored when set. The socket is closed if the hook is
/// still running after `connect_timeout`.
using WebsocketTransportHook = std::function<boost::asio::awaitable<void>(
    boost::asio::ip::tcp::socket& socket, std::string host, std::uint16_t port)>;

/// Source of the `timestamp` (Unix time in milliseconds) of signed requests, used instead of the
/// host clock. It is called once per signed REST attempt (so each retry is signed with a fresh
/// value), per signed WebSocket API request and per signed WebSocket streams connection URL
/// (reconnects and renewals included), possibly from the client's threads: keep it cheap,
/// non-blocking and thread-safe. Empty: `system_clock`.
///
/// Typical use is compensating a host clock that is skewed against Binance beyond `recvWindow`
/// (error `-1021`): measure `serverTime - local time` and add it from an `std::atomic`.
using TimestampProvider = std::function<std::int64_t()>;

struct RestApiConfig {
    std::optional<std::string> api_key;
    std::optional<std::string> api_secret;
    /// Set by the product factory (`SpotRestApi::production(...)`, …) when empty.
    std::optional<std::string> base_path;
    /// How long one attempt of a request may take as a whole, as in the other Binance connectors:
    /// DNS, connect, proxy, TLS handshake, writing the request and reading the whole response. A
    /// retry starts a new attempt. When a host resolves to several addresses, the connect step
    /// tries them with staggered attempts (the next address after 250 ms or as soon as the
    /// previous one fails, earlier attempts keep running, the first to connect wins). Any
    /// value up to `milliseconds::max()` is accepted; one too large to represent as a deadline
    /// means no timeout.
    std::chrono::milliseconds timeout{1000};
    bool keep_alive = true;
    /// Asks for gzip / deflate responses and decodes them.
    bool compression = true;
    /// Largest response body accepted, both on the wire and after decompression. Larger
    /// responses fail with `ConnectorClientError`, which guards against decompression bombs.
    std::size_t max_response_size = 128ULL * 1024 * 1024;
    /// Total attempts for retriable failures (GET and DELETE on a network error or
    /// 500/502/503/504). 0 and 1 both mean a single attempt.
    /// Each retry is signed again with a fresh `timestamp`.
    std::uint32_t retries = 3;
    /// Linear backoff: attempt `n` waits `n * backoff` before retrying.
    std::chrono::milliseconds backoff{1000};
    std::optional<ProxyConfig> proxy;
    /// When `proxy` is unset, use the proxy from the environment. See `proxy_from_environment`.
    bool proxy_from_env = true;
    /// Extra headers on every request. Join multiple values with `", "`.
    std::map<std::string, std::string> custom_headers;
    TlsContextHook agent;
    std::optional<PrivateKey> private_key;
    std::optional<std::string> private_key_passphrase;
    std::optional<TimeUnit> time_unit;
    /// Source of the `timestamp` of signed requests; empty: the host clock. See
    /// `TimestampProvider`.
    TimestampProvider timestamp_provider;
    /// Runs the client on this executor instead of a thread of its own, so that many clients
    /// can share one event loop. Keep it running for as long as the client has work, and do not
    /// make blocking calls from its threads. Empty: the client starts a dedicated thread.
    boost::asio::any_io_executor executor;
};

/// WebSocket API (request / response) configuration.
struct WebsocketApiConfig {
    std::optional<std::string> api_key;
    std::optional<std::string> api_secret;
    /// `wss://…` (or `ws://…`). Set by the product factory when empty.
    std::optional<std::string> url;
    /// How long to wait for a response.
    std::chrono::milliseconds timeout{5000};
    /// Delay before reconnecting a connection that dropped. After a failed attempt, a backoff of
    /// 1 s doubling up to 60 s, with random jitter, is added to it.
    std::chrono::milliseconds reconnect_delay{5000};
    /// Time allowed to open one connection: DNS, TCP, proxy, TLS and the WebSocket upgrade. When
    /// the host resolves to several addresses, they are tried with staggered attempts (the next
    /// address after 250 ms or as soon as the previous one fails, earlier attempts keep running,
    /// the first to connect wins) within this one time, not a part of it per address.
    std::chrono::milliseconds connect_timeout{10000};
    WebsocketMode mode;
    /// Negotiates permessage-deflate.
    bool compression = true;
    /// Largest message accepted (after decompression). Larger messages close the connection.
    std::size_t max_message_size = 64ULL * 1024 * 1024;
    /// HTTP(S) proxy (reached with a `CONNECT` tunnel) or SOCKS5 proxy.
    std::optional<ProxyConfig> proxy;
    /// When `proxy` is unset, use the proxy from the environment (`proxy_from_environment`). Off by
    /// default, as in the other Binance connectors, whose WebSocket connections ignore it.
    bool proxy_from_env = false;
    TlsContextHook agent;
    WebsocketTransportHook transport;
    std::optional<PrivateKey> private_key;
    std::optional<std::string> private_key_passphrase;
    std::optional<TimeUnit> time_unit;
    /// Source of the `timestamp` of signed requests; empty: the host clock. See
    /// `TimestampProvider`.
    TimestampProvider timestamp_provider;
    /// After a reconnect or renewal, logs the session on again if it was logged on through
    /// `session.logon`, and lets authenticated requests skip `apiKey` / `signature` meanwhile.
    bool auto_session_relogon = true;
    /// Runs the client on this executor instead of a thread of its own, so that many clients
    /// can share one event loop. Keep it running for as long as the client has work, and do not
    /// make blocking calls from its threads. Empty: the client starts a dedicated thread.
    boost::asio::any_io_executor executor;
};

/// WebSocket market / user streams configuration.
struct WebsocketStreamsConfig {
    /// `wss://…` (or `ws://…`). Set by the product factory when empty.
    std::optional<std::string> url;
    std::chrono::milliseconds reconnect_delay{5000};
    /// Time allowed to open one connection. When the host resolves to several addresses, they are
    /// tried with staggered attempts (the next address after 250 ms or as soon as the previous one
    /// fails, earlier attempts keep running, the first to connect wins) within this one time.
    std::chrono::milliseconds connect_timeout{10000};
    WebsocketMode mode;
    bool compression = true;
    std::size_t max_message_size = 64ULL * 1024 * 1024;
    std::optional<ProxyConfig> proxy;
    /// When `proxy` is unset, use the proxy from the environment. Off by default, as for the
    /// WebSocket API.
    bool proxy_from_env = false;
    TlsContextHook agent;
    WebsocketTransportHook transport;
    std::optional<TimeUnit> time_unit;
    /// Source of the `timestamp` of signed requests; empty: the host clock. See
    /// `TimestampProvider`.
    TimestampProvider timestamp_provider;
    std::optional<std::string> api_key;
    std::optional<std::string> api_secret;
    std::optional<PrivateKey> private_key;
    std::optional<std::string> private_key_passphrase;
    /// Runs the client on this executor instead of a thread of its own, so that many clients
    /// can share one event loop. Keep it running for as long as the client has work, and do not
    /// make blocking calls from its threads. Empty: the client starts a dedicated thread.
    boost::asio::any_io_executor executor;
};

/// The proxy configured in the environment for a target host, or `nullopt`.
///
/// - Variables: `https_proxy` / `HTTPS_PROXY` for TLS targets and `http_proxy` / `HTTP_PROXY`
///   otherwise, then `all_proxy` / `ALL_PROXY`. Lower case wins. Upper-case `HTTP_PROXY` is
///   ignored when `REQUEST_METHOD` is set (CGI, "httpoxy").
/// - Values: `[http|https|socks5|socks5h://][user:password@]host[:port]`. Credentials are
///   percent-decoded. Without a port, 80 (http), 443 (https) or 1080 (socks5, socks5h) is used.
///   Other schemes are ignored with a warning.
/// - `no_proxy` / `NO_PROXY` is a comma-separated list. `*` matches everything; `example.com`
///   and `.example.com` match the domain and its subdomains; IP literals match exactly. An entry
///   may carry a `:port`.
[[nodiscard]] BINANCE_COMMON_EXPORT std::optional<ProxyConfig>
proxy_from_environment(bool tls, std::string_view host, std::uint16_t port);

/// Debug representation with credentials redacted.
BINANCE_COMMON_EXPORT std::ostream& operator<<(std::ostream& os, const RestApiConfig& cfg);
BINANCE_COMMON_EXPORT std::ostream& operator<<(std::ostream& os, const WebsocketApiConfig& cfg);
BINANCE_COMMON_EXPORT std::ostream& operator<<(std::ostream& os, const WebsocketStreamsConfig& cfg);

namespace detail {

/// Set by the product clients (and the C interface), not part of the user configuration.
struct ClientOptions {
    /// The `User-Agent` header; empty: `build_user_agent("common")`.
    std::string user_agent;
    /// WebSocket streams: the product's streams are signed with the configured credentials.
    bool signed_streams = false;
    /// WebSocket streams: SUBSCRIBE / UNSUBSCRIBE ids are always numbers (some products reject
    /// string ids).
    bool stream_id_is_strictly_number = false;
};

} // namespace detail

} // namespace binance::common
