# Binance Common Types and Utilities for Binance C++ Connectors

![C++ Standard](https://img.shields.io/badge/C%2B%2B-20-blue)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

`binance::common` is the **shared library** of the Binance C++ connectors. It implements what every
connector needs to talk to the Binance REST and WebSocket APIs: configuration, request signing,
HTTP and WebSocket transports, connection management, error types and utilities. The connectors
under [`clients/`](../clients) are generated on top of it, and it can also be used on its own.

## Installation

`binance::common` is built and installed with every connector (see the
[root README](../README.md#installation)). To use it on its own:

```bash
cmake --preset release -DBINANCE_PRODUCTS=""
cmake --build --preset release
cmake --install build/release --prefix /opt/binance --strip
```

```cmake
find_package(binance-connector-cpp CONFIG REQUIRED)
target_link_libraries(app PRIVATE binance::common)
```

## Features

- **REST client** with connection reuse, retries with backoff (GET and DELETE), gzip/deflate
  decoding and rate-limit headers.
- **Request signing** with HMAC-SHA256, RSA or Ed25519 keys.
- **WebSocket API client**: request/response matching, connection pools, session logon that is
  repeated after reconnects, and user-data subscriptions that are restored after reconnects.
- **WebSocket Streams client**: subscriptions over connection pools and URL paths, restored after
  reconnects.
- **Automatic connection management**: reconnects with backoff, renewal every 23 hours and on
  `serverShutdown`, and dead-connection detection.
- **Typed responses and events** decoded on demand, with exact decimals (`Decimal`) and 64-bit
  integers.
- **Blocking or asynchronous** calls: every request also accepts any Asio completion token
  (callback, `use_future`, `use_awaitable`, ...).
- **Proxies** (HTTP and HTTPS, with Basic auth, or from the environment) and a TLS hook to add CAs
  or pin certificates.
- **Errors** as one exception hierarchy carrying Binance's `code()` and `msg()`.

## Usage

### REST

`RestClient` sends any Binance REST request:

```cpp
#include <binance/common/rest.hpp>

using namespace binance::common;

RestApiConfig cfg;
cfg.base_path = "https://testnet.binance.vision";
cfg.api_key = "...";
cfg.api_secret = "...";  // or cfg.private_key = PrivateKey::from_file("ed25519.pem");
RestClient client(cfg);

// Blocking
const RestApiResponse<boost::json::object> time(
    client.send_request({.method = HttpMethod::Get, .endpoint = "/api/v3/time"}));
std::cout << time.data().at("serverTime") << "\n";

// Signed (timestamp + signature are added)
RestRequest order{.method = HttpMethod::Post, .endpoint = "/api/v3/order"};
order.query = {{"symbol", "BNBUSDT"}, {"side", "BUY"}, {"type", "MARKET"}, {"quantity", "0.01"}};
order.is_signed = true;
const auto placed = client.send_request(order);

// Asynchronous: any Asio completion token (callback, use_future, use_awaitable, ...)
const auto depth = co_await client.async_send_request(
    {.method = HttpMethod::Get, .endpoint = "/api/v3/depth", .query = {{"symbol", "BNBUSDT"}}},
    boost::asio::use_awaitable);
```

### WebSocket API and Streams

`WebsocketApi` sends WebSocket API requests; `WebsocketStreams` subscribes to market streams. Both
reconnect, renew their connections every 23 hours and survive `serverShutdown` on their own.

```cpp
#include <binance/common/websocket_api.hpp>
#include <binance/common/websocket_streams.hpp>

WebsocketApiConfig api_cfg;
api_cfg.url = "wss://ws-api.testnet.binance.vision/ws-api/v3";
api_cfg.api_key = "...";
api_cfg.private_key = PrivateKey::from_file("ed25519.pem");
auto api = std::make_shared<WebsocketApi>(api_cfg);
api->connect();

// Logs every connection on, and again after reconnects (auto_session_relogon)
api->send_message("session.logon", {}, {.is_signed = true, .is_session_logon = true});
const auto time = send<boost::json::object>(*api, "time", {});
const auto order = co_await async_send<boost::json::object>(
    api, "order.place",
    {{"symbol", "BNBUSDT"}, {"side", "BUY"}, {"type", "MARKET"}, {"quantity", "0.01"}},
    {.is_signed = true}, boost::asio::use_awaitable);

WebsocketStreamsConfig streams_cfg;
streams_cfg.url = "wss://stream.testnet.binance.vision";
WebsocketStreams streams(streams_cfg);
streams.connect();
auto trades = streams.create_stream("btcusdt@aggTrade");  // SUBSCRIBE is queued until open
trades.on_message([](const boost::json::value& msg) { /* runs on the client's executor */ });
trades.wait_subscribed(std::chrono::seconds(5));  // optional: until the server acknowledges it
auto events = streams.on_event([](const WebsocketEvent& e) { /* Open, Close, ... */ });
// ...
trades.unsubscribe();
streams.disconnect();
```

User-data subscriptions return the response and a stream of their events. The request is sent
again after every reconnect and renewal (after the session logon, if any):

```cpp
auto sub = api->subscribe("userDataStream.subscribe", {});
sub.stream.on_message([](const boost::json::value& event) { /* executionReport, ... */ });
// Typed, and asynchronous with any completion token:
auto [response, stream] = co_await async_subscribe<Result, Event>(
    api, "userDataStream.subscribe", {}, {}, boost::asio::use_awaitable);
```

Some streams (`cms`, `w3w_prediction`) are signed: the connection is authenticated with the
credentials in the configuration. The product clients pass `detail::ClientOptions` with
`signed_streams` on (and their `User-Agent`), which is not part of the configuration.

```cpp
WebsocketStreamsConfig cfg;
cfg.url = "wss://api.binance.com/sapi/wss";
cfg.api_key = "...";
cfg.api_secret = "...";  // or cfg.private_key = PrivateKey::from_file("ed25519.pem")
// Throws ConfigError without an API key and a secret or key.
WebsocketStreams streams(cfg, {}, {.signed_streams = true});
streams.connect();
auto announcements = streams.create_stream("com_announcement_en");
```

Every connection signs its own URL, with a fresh timestamp after each reconnect and renewal, and
subscribes all its streams with one command once it opens. `time_unit` and stream ids do not apply.

- `mode = WebsocketMode::pool(n)` spreads requests or streams over `n` connections.
  `session.logon` / `session.logout` go to every connection; `send_all<T>` returns each response.
- Callbacks run on the client's executor unless bound to another, so they should not block.
  Blocking calls made from it throw; `subscribe`, `unsubscribe` and callback changes are safe from
  anywhere. No callback runs once its handle is unsubscribed or its client is destroyed.
- Stream handles and `on_event` subscriptions are move-only: destroying one unsubscribes, and
  `release()` keeps the callback for the client's lifetime.
- Stream data that arrives before the first callback is added is kept for it.
- Reconnects wait `reconnect_delay`. After a failed attempt, a backoff of 1 s doubling up to 60 s,
  with random jitter, is added; the wait is at least the `Retry-After` of a rejected upgrade. Streams of a connection that closes for good move to
  another connection of the pool.

### Errors

Every error derives from `binance::common::Error`, which carries the Binance `code()` (when there is
one) and `msg()`.

- REST errors are subclasses of `ConnectorError`, for example `BadRequestError`, `ConflictError` (409),
  `UnauthorizedError`, `TooManyRequestsError`, `RateLimitBanError`, `ServerError` or `NetworkError`.
  They carry the HTTP `response()` (headers, rate limits) when there was one.
- `RequestTimeoutError` (a `NetworkError`) means the attempt took longer than `timeout`.
- `NetworkError::request_sent()` says whether a failed request may have reached Binance. Check it
  before placing an order again.
- `NetworkError::transport_error()` and `WebsocketNetworkError::transport_error()` give the
  `boost::system::error_code` behind the failure (`boost::asio::error::connection_refused`,
  `host_not_found`, `connection_reset`, `boost::beast::error::timeout`, an SSL error, ...), or an
  empty code when there is none. A cancelled request reports `operation_aborted`.
- `ConnectorError::retry_after()` is the `Retry-After` delay (in seconds) of a 418 / 429 response;
  the HTTP-date form is not read. `WebsocketResponseError::retry_at()` is the time from the
  `retryAfter` of a WebSocket API error, which Binance sends as an epoch timestamp.
- WebSocket errors derive from `WebsocketError`: `WebsocketResponseError` (Binance `code()` /
  `msg()`, `status()`, `rate_limits()`, and `data()`: the `error.data` of the answer), `WebsocketTimeoutError`,
  `WebsocketNoResponseError`, `WebsocketNotConnectedError`, ...
- Invalid configurations throw `ConfigError`.
- Asynchronous operations deliver errors as a `std::exception_ptr`.

### Configuration

- `timeout`: how long one attempt of a request may take as a whole (DNS, connect, proxy, TLS,
  writing the request and reading the response), as in the other Binance connectors; a retry starts
  a new attempt. A host with several addresses is tried with staggered attempts (the next address
  after 250 ms or when the previous one fails, the first to connect wins) within that time. `retries` / `backoff` (GET and DELETE only) and `keep_alive`.
- `compression` and `max_response_size`.
- `proxy`: HTTP or HTTPS (Basic auth), or SOCKS5 (`ProxyProtocol::Socks5` / `Socks5h`, with optional
  username / password), for REST and WebSockets. TLS to the target runs end to end through a
  tunnel. `Socks5` resolves the target's host name in the client; `Socks5h` has the proxy resolve
  it. Without `proxy`, `HTTPS_PROXY` / `HTTP_PROXY` / `ALL_PROXY` / `NO_PROXY` from the
  environment are used (`http://`, `https://`, `socks5://` or `socks5h://` values; SOCKS port
  1080 by default) when `proxy_from_env` is set: by default for REST, and not for WebSockets, as in
  the other Binance connectors.
- `timestamp_provider` (`std::function<std::int64_t()>`, milliseconds since the epoch; default: the
  host clock): the `timestamp` of signed REST requests, signed WebSocket API requests and signed
  WebSocket streams URLs. It is called for every signed attempt, so each retry, re-logon,
  reconnect and renewal is signed with a fresh value, and may run on the client's threads (keep
  it cheap and thread-safe). Use it to compensate a clock that is off against Binance
  (error `-1021`):

  ```cpp
  auto offset_ms = std::make_shared<std::atomic<std::int64_t>>(0);  // serverTime - local time
  cfg.timestamp_provider = [offset_ms] {
      return std::chrono::duration_cast<std::chrono::milliseconds>(
                 std::chrono::system_clock::now().time_since_epoch()).count() + offset_ms->load();
  };
  ```

- `custom_headers`, and `agent`: a hook to adjust the TLS context of REST and WebSocket
  connections, e.g. to add a CA or pin certificates:

  ```cpp
  cfg.agent = [](boost::asio::ssl::context& ctx) {
      ctx.set_verify_callback([](bool preverified, boost::asio::ssl::verify_context& vc) {
          auto* store = vc.native_handle();
          // Depth 0 is the server certificate; `is_pinned` compares its public key.
          return preverified && (X509_STORE_CTX_get_error_depth(store) != 0 ||
                                 is_pinned(X509_STORE_CTX_get_current_cert(store)));
      });
  };
  ```

  It also presents a client certificate (mutual TLS):

  ```cpp
  cfg.agent = [](boost::asio::ssl::context& ctx) {
      ctx.use_certificate_chain_file("client.pem");
      ctx.use_private_key_file("client.key", boost::asio::ssl::context::pem);
  };
  ```

- `transport` (WebSocket): a coroutine that opens the TCP connection itself, e.g. through a
  tunnel of your own. TLS and the WebSocket upgrade then run over it.
- `executor`: by default each client runs its own I/O thread. Set it to share one event loop between
  many clients (`cfg.executor = ioc.get_executor();`); the loop must keep running while the
  clients have work, and blocking calls must not be made from its threads.

`operator<<` on a configuration redacts every secret. The log level is set with `Logger::set_level`
or the `LOG_LEVEL` environment variable (`debug`, `info`, `warn`, `error`, `none`).

## Contributing

Contributions are welcome!

1. Open a GitHub issue before making changes.
2. Discuss proposed changes with maintainers.
3. Follow the existing C++ structure.

## Disclaimer

This SDK is provided by Binance on an "as is" and "as available" basis for use at your own risk. Binance makes no representations or warranties of any kind, whether express or implied, as to the operation of the SDK, its accuracy, reliability, completeness, or fitness for any particular purpose.

To the fullest extent permitted by law, Binance shall not be liable for any losses, damages, or expenses of any kind arising from or in connection with your use of, or inability to use, this SDK, including but not limited to any financial losses resulting from errors, bugs, interruptions, or inaccuracies in the SDK.

Your use of this SDK to access the Binance Platform is subject to the Binance API Key Terms and the Binance Terms of Use, which shall prevail in the event of any conflict with this disclaimer. You are solely responsible for any orders or transactions executed through the Binance Platform using this SDK.

This SDK is not intended to constitute investment advice or a recommendation to buy, sell, or hold any digital asset. You should independently evaluate and verify all information before acting.

- [Binance Terms of Use](https://www.binance.com/en/terms)
- [Binance API Key Terms](https://www.binance.com/en/about-legal/terms-binance-api)

## License

This project is licensed under the MIT License - see the [LICENCE](../LICENCE) file for details.
