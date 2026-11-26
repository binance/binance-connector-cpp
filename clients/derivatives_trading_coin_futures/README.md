# Binance C++ Derivatives Trading (COIN-M Futures) Connector

![C++ Standard](https://img.shields.io/badge/C%2B%2B-20-blue)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

`binance::derivatives_trading_coin_futures` is the official C++ connector for the Binance Derivatives Trading (COIN-M Futures) REST API, WebSocket API and WebSocket Streams. Access market data, manage accounts, and trade COIN-M perpetual and delivery futures.

It is one component of the [Binance C++ Connector](../../README.md), built on the shared
[`binance::common`](../../common/README.md) library.

## Table of Contents

- [Supported Features](#supported-features)
- [Installation](#installation)
- [Documentation](#documentation)
- [REST APIs](#rest-apis)
- [WebSocket APIs](#websocket-apis)
- [WebSocket Streams](#websocket-streams)
- [Asynchronous Calls](#asynchronous-calls)
- [Automatic Connection Renewal](#automatic-connection-renewal)
- [Logging](#logging)
- [Examples](#examples)
- [Testing](#testing)
- [Contributing](#contributing)
- [Disclaimer](#disclaimer)
- [License](#license)

## Supported Features

- [REST API](./include/binance/derivatives_trading_coin_futures/rest_api/rest_api.hpp): `binance::derivatives_trading_coin_futures::DerivativesTradingCoinFuturesRestApi`
- [WebSocket API](./include/binance/derivatives_trading_coin_futures/websocket_api/websocket_api.hpp): `binance::derivatives_trading_coin_futures::DerivativesTradingCoinFuturesWebsocketApi`
- [WebSocket Streams](./include/binance/derivatives_trading_coin_futures/websocket_streams/websocket_streams.hpp): `binance::derivatives_trading_coin_futures::DerivativesTradingCoinFuturesWebsocketStreams`

- A typed method for every endpoint and stream, with a `Params` struct for its parameters and
  a typed response, decoded on demand. Prices and quantities are exact decimals (`common::Decimal`).
- Blocking calls, and `async_` variants that take any Asio completion token (callback, `use_future`,
  `use_awaitable`, ...).
- Request signing with HMAC-SHA256, RSA or Ed25519 keys.
- REST: connection reuse, retries with backoff, gzip / deflate responses and the rate limits of every
  response.
- WebSocket: reconnects with backoff, connection pools, and connections renewed before Binance closes
  them.
- HTTP(S) proxies, also from the environment, and a hook to add CAs or pin certificates.

## Installation

With vcpkg, as an overlay port of this repository (see the [root README](../../README.md#installation)):

```bash
vcpkg install "binance-connector-cpp[derivatives-trading-coin-futures]" --overlay-ports=/path/to/binance-connector-cpp/ports
```

From source, building only this connector:

```bash
cmake --preset release -DBINANCE_PRODUCTS=derivatives_trading_coin_futures
cmake --build --preset release
cmake --install build/release --prefix /opt/binance --strip
```

Then, in your `CMakeLists.txt`:

```cmake
find_package(binance-connector-cpp CONFIG REQUIRED COMPONENTS derivatives_trading_coin_futures)
target_link_libraries(app PRIVATE binance::derivatives_trading_coin_futures)  # binance::common comes with it
```

`#include <binance/derivatives_trading_coin_futures/derivatives_trading_coin_futures.hpp>` includes every client of the connector; include
`<binance/derivatives_trading_coin_futures/rest_api.hpp>`, `<binance/derivatives_trading_coin_futures/websocket_api.hpp>`, `<binance/derivatives_trading_coin_futures/websocket_streams.hpp>`
for just one of them.

## Documentation

- **API reference:** [binance.github.io/binance-connector-cpp](https://binance.github.io/binance-connector-cpp/)
- **Configuration, errors and connection behaviour:** [`common/README.md`](../../common/README.md)
- **Examples:** [`examples/derivatives_trading_coin_futures/`](../../examples/derivatives_trading_coin_futures/) has one program for every endpoint and stream.
- **Official Binance Derivatives Trading (COIN-M Futures) API docs:** [https://developers.binance.com/en/docs/products/derivatives-trading-coin-futures/general-info](https://developers.binance.com/en/docs/products/derivatives-trading-coin-futures/general-info)

### REST APIs

```cpp
#include <iostream>
#include <utility>

#include <binance/common/json.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api.hpp>

using namespace binance;

int main() {
    common::RestApiConfig cfg;
    const auto client = derivatives_trading_coin_futures::DerivativesTradingCoinFuturesRestApi::production(std::move(cfg));

    using namespace derivatives_trading_coin_futures::rest_api;
    const auto response = client.check_server_time();
    std::cout << common::to_json(response.data()) << "\n";
}
```

Each call returns a `common::RestApiResponse<T>`: `data()` is the decoded response, `status()` the
HTTP status, `headers()` the response headers and `rate_limits()` the request weight and order
counts Binance reported for the call.

#### Configuration Options

The client is configured with a `common::RestApiConfig`:

| Option | Default | Description |
| --- | --- | --- |
| `api_key`, `api_secret` | none | Credentials for signed endpoints (HMAC). |
| `private_key`, `private_key_passphrase` | none | An RSA or Ed25519 key instead of `api_secret`: `common::PrivateKey::from_file(path)` or `from_pem(text)`. |
| `base_path` | set by the factory | Another endpoint for the client (see [Environments](#derivatives_trading_coin_futures-rest-api-environments)). |
| `timeout` | 1000 ms | How long a request attempt may take as a whole (connect, write, read the response); a retry starts a new one. |
| `retries`, `backoff` | 3, 1000 ms | Attempts for GET and DELETE on a network error or a 5xx response, with a linear backoff. |
| `keep_alive` | `true` | Reuses connections. |
| `compression` | `true` | Asks for gzip / deflate responses. |
| `max_response_size` | 128 MiB | Larger responses fail with `ConnectorClientError`. |
| `proxy`, `proxy_from_env` | none, `true` | An HTTP(S) proxy with Basic auth, or a SOCKS5 proxy (`ProxyProtocol::Socks5` / `Socks5h`); without one, `HTTPS_PROXY` / `HTTP_PROXY` / `ALL_PROXY` / `NO_PROXY` are used. |
| `custom_headers` | none | Headers added to every request. |
| `agent` | none | A hook on the TLS context: add CAs, client certificates, or pin certificates. |
| `timestamp_provider` | host clock | The `timestamp` of signed requests, e.g. the host clock corrected by its offset from `serverTime` (error `-1021`). |
| `executor` | own thread | An Asio executor to share one event loop between many clients. |

An example for each option:

- [Timeout](./docs/rest_api/timeout.md)
- [Proxy](./docs/rest_api/proxy.md)
- [Keep-Alive](./docs/rest_api/keep-alive.md)
- [Compression](./docs/rest_api/compression.md)
- [Retries](./docs/rest_api/retries.md)
- [Custom Headers](./docs/rest_api/custom-headers.md)
- [TLS Agent](./docs/rest_api/agent.md)
- [Certificate Pinning](./docs/rest_api/certificate-pinning.md)
- [Key Pair Based Authentication](./docs/rest_api/key-pair-authentication.md)
- [Timestamp Provider](./docs/rest_api/timestamp-provider.md)
- [Shared Event Loop](./docs/rest_api/executor.md)
- [Error Handling](./docs/rest_api/error-handling.md)

See [`common/README.md`](../../common/README.md#configuration) for the details.

#### Error Handling

Every error derives from `common::Error`, with the Binance `code()` and `msg()` when there is one.
REST errors are subclasses of `common::ConnectorError` and carry the HTTP `response()`:

```cpp
#include <binance/common/errors.hpp>

try {
    const auto response = client.check_server_time();
} catch (const common::BadRequestError& e) {         // HTTP 400: invalid parameters
    std::cerr << e.code().value_or(0) << " " << e.msg() << "\n";
} catch (const common::TooManyRequestsError& e) {    // 429: back off for e.retry_after()
} catch (const common::RateLimitBanError& e) {       // 418: the IP is banned for e.retry_after()
} catch (const common::NetworkError& e) {            // check e.request_sent() before retrying an order
} catch (const common::ConnectorError& e) {          // any other HTTP or client error
}
```

The full list is in [`common/README.md`](../../common/README.md#errors).

#### Endpoints Without a Method

`send_request` and `send_signed_request` call an endpoint the connector does not have a method for
yet, and decode the response into any type, for example `boost::json::value`:

```cpp
const auto response = client.send_signed_request<boost::json::value>(
    "/dapi/v1/endpoint", common::HttpMethod::Get, {{"symbol", "BNBUSDT"}});
```

<a id="derivatives_trading_coin_futures-rest-api-environments"></a>
The client is created with `DerivativesTradingCoinFuturesRestApi::production(cfg)`, `DerivativesTradingCoinFuturesRestApi::testnet(cfg)`, `DerivativesTradingCoinFuturesRestApi::demo(cfg)`, or with `from_config(cfg)` for the endpoint in
`cfg.base_path`.

#### Testnet

For testing, `DerivativesTradingCoinFuturesRestApi::testnet(cfg)` connects to the testnet, which uses API keys of its own.

#### Demo

`DerivativesTradingCoinFuturesRestApi::demo(cfg)` connects to the demo environment, which uses API keys of its own.

### WebSocket APIs

```cpp
#include <iostream>
#include <utility>

#include <binance/common/json.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_api.hpp>

using namespace binance;

int main() {
    common::WebsocketApiConfig cfg;
    cfg.api_key = "your-api-key";
    cfg.api_secret = "your-api-secret";  // or cfg.private_key = common::PrivateKey::from_file("key.pem")
    auto client = derivatives_trading_coin_futures::DerivativesTradingCoinFuturesWebsocketApi::production(std::move(cfg));
    auto connection = client.connect();

    using namespace derivatives_trading_coin_futures::websocket_api;
    const AccountInformationParams params{};
    const auto response = connection.account_information(params);
    std::cout << common::to_json(response.data()) << "\n";
    connection.disconnect();
}
```

`connect()` opens a connection and returns it once it is open; every call opens an independent one,
and `connect(common::WebsocketMode::pool(n))` opens a pool of `n`. The connection reconnects on its
own until `disconnect()`, and fails a request with `common::WebsocketNotConnectedError` while it is
reconnecting. Each call returns a `common::WebsocketApiResponse<T>` with `data()` and
`rate_limits()`.

#### Configuration Options

The client is configured with a `common::WebsocketApiConfig`:

| Option | Default | Description |
| --- | --- | --- |
| `api_key`, `api_secret` | none | Credentials for signed requests (HMAC). |
| `private_key`, `private_key_passphrase` | none | An RSA or Ed25519 key instead of `api_secret`. |
| `url` | set by the factory | Another endpoint for the client (see [Environments](#derivatives_trading_coin_futures-websocket-api-environments)). |
| `timeout` | 5000 ms | How long to wait for a response. |
| `connect_timeout` | 10000 ms | Time allowed to open a connection (DNS, TCP, proxy, TLS and upgrade). |
| `reconnect_delay` | 5000 ms | Delay before reconnecting; failed attempts add a backoff up to 60 s. |
| `mode` | single | `common::WebsocketMode::pool(n)` spreads the requests over `n` connections. |
| `compression` | `true` | Negotiates permessage-deflate. |
| `max_message_size` | 64 MiB | Larger messages close the connection. |
| `proxy`, `proxy_from_env` | none, `false` | An HTTP(S) proxy (a `CONNECT` tunnel) or a SOCKS5 proxy; `proxy_from_env` reads `HTTPS_PROXY` / `ALL_PROXY` / `NO_PROXY`. |
| `agent`, `transport` | none | Hooks on the TLS context and on opening the TCP connection yourself. |
| `timestamp_provider` | host clock | The `timestamp` of signed requests, e.g. the host clock corrected by its offset from `serverTime` (error `-1021`). |
| `auto_session_relogon` | `true` | Logs on again after a reconnect if the session was logged on. |
| `executor` | own thread | An Asio executor to share one event loop between many clients. |

An example for each option:

- [Timeout](./docs/websocket_api/timeout.md)
- [Reconnect Delay](./docs/websocket_api/reconnect-delay.md)
- [Connection Mode](./docs/websocket_api/connection-mode.md)
- [Compression](./docs/websocket_api/compression.md)
- [Proxy](./docs/websocket_api/proxy.md)
- [TLS Agent](./docs/websocket_api/agent.md)
- [Certificate Pinning](./docs/websocket_api/certificate-pinning.md)
- [Custom Transport](./docs/websocket_api/transport.md)
- [Key Pair Based Authentication](./docs/websocket_api/key-pair-authentication.md)
- [Timestamp Provider](./docs/websocket_api/timestamp-provider.md)
- [Shared Event Loop](./docs/websocket_api/executor.md)

#### Requests Without a Method

`send_message` and `send_signed_message` send any WebSocket API method:

```cpp
const auto response =
    connection.send_message<boost::json::value>("method.name", {{"symbol", "BNBUSDT"}});
```

<a id="derivatives_trading_coin_futures-websocket-api-environments"></a>
The client is created with `DerivativesTradingCoinFuturesWebsocketApi::production(cfg)`, `DerivativesTradingCoinFuturesWebsocketApi::testnet(cfg)`, or with `from_config(cfg)` for the endpoint in
`cfg.url`.

#### Testnet

For testing, `DerivativesTradingCoinFuturesWebsocketApi::testnet(cfg)` connects to the testnet, which uses API keys of its own.

### WebSocket Streams

```cpp
#include <chrono>
#include <iostream>
#include <thread>
#include <utility>

#include <binance/common/json.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_streams.hpp>

using namespace binance;

int main() {
    common::WebsocketStreamsConfig cfg;
    auto client = derivatives_trading_coin_futures::DerivativesTradingCoinFuturesWebsocketStreams::production(std::move(cfg));
    auto connection = client.connect();

    using namespace derivatives_trading_coin_futures::websocket_streams;
    const AllBookTickersStreamParams params{};
    auto stream = connection.all_book_tickers_stream(params);
    stream.on_message([](const auto& event) { std::cout << common::to_json(event) << "\n"; });

    std::this_thread::sleep_for(std::chrono::seconds(10));  // events arrive on the client's thread
    stream.unsubscribe();
    connection.disconnect();
}
```

`connect()` opens a connection and returns it once it is open, subscribed to the streams you pass it
by name (`connect({"btcusdt@trade"})`); every call opens an independent one. Each stream method of
the connection returns a handle: `on_message` sets its callback, and `unsubscribe()` (or destroying
the handle) ends the subscription. Subscriptions are restored after every reconnect.

#### Configuration Options

The client is configured with a `common::WebsocketStreamsConfig`:

| Option | Default | Description |
| --- | --- | --- |
| `url` | set by the factory | Another endpoint for the client (see [Environments](#derivatives_trading_coin_futures-websocket-streams-environments)). |
| `connect_timeout` | 10000 ms | Time allowed to open a connection. |
| `reconnect_delay` | 5000 ms | Delay before reconnecting; failed attempts add a backoff up to 60 s. |
| `mode` | single | `common::WebsocketMode::pool(n)` spreads the streams over `n` connections. |
| `compression` | `true` | Negotiates permessage-deflate. |
| `max_message_size` | 64 MiB | Larger messages close the connection. |
| `proxy`, `proxy_from_env` | none, `false` | An HTTP(S) proxy (a `CONNECT` tunnel) or a SOCKS5 proxy; `proxy_from_env` reads `HTTPS_PROXY` / `ALL_PROXY` / `NO_PROXY`. |
| `agent`, `transport` | none | Hooks on the TLS context and on opening the TCP connection. |
| `executor` | own thread | An Asio executor to share one event loop between many clients. |

An example for each option:

- [Reconnect Delay](./docs/websocket_streams/reconnect-delay.md)
- [Connection Mode](./docs/websocket_streams/connection-mode.md)
- [Compression](./docs/websocket_streams/compression.md)
- [Proxy](./docs/websocket_streams/proxy.md)
- [TLS Agent](./docs/websocket_streams/agent.md)
- [Certificate Pinning](./docs/websocket_streams/certificate-pinning.md)
- [Custom Transport](./docs/websocket_streams/transport.md)
- [Shared Event Loop](./docs/websocket_streams/executor.md)

#### Subscribe to User Data Streams

The account events arrive on user data streams (`user_data(listen_key)`), opened with a listen
key from `start_user_data_stream()` of the REST API. The listen key expires after 60 minutes
without a keepalive. The subscriptions are restored after every reconnect.

```cpp
#include <chrono>
#include <iostream>
#include <thread>
#include <utility>

#include <binance/common/json.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_streams.hpp>

using namespace binance;

int main() {
    common::RestApiConfig cfg;
    cfg.api_key = "your-api-key";
    cfg.api_secret = "your-api-secret";
    const auto rest = derivatives_trading_coin_futures::DerivativesTradingCoinFuturesRestApi::production(std::move(cfg));
    // Keep it open with keepalive_user_data_stream() at least every 60 minutes.
    const std::string listen_key = rest.start_user_data_stream().data().listen_key.value_or("");

    auto client = derivatives_trading_coin_futures::DerivativesTradingCoinFuturesWebsocketStreams::production({});
    auto connection = client.connect();
    auto stream = connection.user_data(listen_key);
    stream.on_message([](const auto& event) { std::cout << common::to_json(event) << "\n"; });

    std::this_thread::sleep_for(std::chrono::seconds(10));  // events arrive on the client's thread
    stream.unsubscribe();
    connection.disconnect();
}
```

#### Unsubscribing from Streams

A handle's `unsubscribe()` ends its subscription without closing the connection; destroying the
handle does the same, and `release()` keeps the subscription for the lifetime of the connection.
`connection.unsubscribe({"<stream name>"})` unsubscribes from streams by name, whatever subscribed
them.

```cpp
stream.unsubscribe();                       // this handle's subscription
connection.unsubscribe({"<stream name>"});  // by name
```

#### Streams by Name

`connection.stream("<stream name>")` subscribes to a stream by its name, for streams the connector
has no method for; its events are `boost::json::value`. Every stream handle has
`wait_subscribed()` (and `async_wait_subscribed(token)`), which returns once the server has
acknowledged the subscription.

<a id="derivatives_trading_coin_futures-websocket-streams-environments"></a>
The client is created with `DerivativesTradingCoinFuturesWebsocketStreams::production(cfg)`, `DerivativesTradingCoinFuturesWebsocketStreams::testnet(cfg)`, `DerivativesTradingCoinFuturesWebsocketStreams::demo(cfg)`, or with `from_config(cfg)` for the endpoint in
`cfg.url`.

#### Testnet

For testing, `DerivativesTradingCoinFuturesWebsocketStreams::testnet(cfg)` connects to the testnet, which uses API keys of its own.

#### Demo

`DerivativesTradingCoinFuturesWebsocketStreams::demo(cfg)` connects to the demo environment, which uses API keys of its own.

### Asynchronous Calls

Every method has an `async_` variant that takes a completion token as its last argument:

```cpp
const auto response = co_await client.async_<method>(params, boost::asio::use_awaitable);
```

Callbacks run on the client's executor, so they should not block. Errors are delivered as a
`std::exception_ptr`. `async_connect` opens a connection the same way:
`auto connection = co_await client.async_connect(boost::asio::use_awaitable);`. Stream methods do not block: the subscription is sent
once the connection is open, and the events arrive on the client's thread.

### Automatic Connection Renewal

WebSocket connections are renewed every 23 hours, before Binance closes them after 24, and when the
server announces a shutdown. The new connection is opened before the old one is closed, so
requests and streams carry on without a gap.

## Logging

The connector logs through `common::Logger`. Set the level with `common::Logger::set_level` or the
`LOG_LEVEL` environment variable (`debug`, `info`, `warn`, `error`, `none`), and send the messages
elsewhere with `common::Logger::set_sink`. Configurations printed with `operator<<` have their
secrets redacted.

## Examples

[`examples/derivatives_trading_coin_futures/`](../../examples/derivatives_trading_coin_futures/) has one runnable program for every endpoint and stream.
See its [README](../../examples/derivatives_trading_coin_futures/README.md) to build and run them.

## Testing

The tests run the connector against local mock servers, with the example responses of the API.
From the root of the repository:

```bash
make test PRODUCTS=derivatives_trading_coin_futures
# or, with CMake directly:
cmake --preset dev -DBINANCE_PRODUCTS=derivatives_trading_coin_futures
cmake --build --preset dev
ctest --preset dev
```

Tests cover:

- Every REST API endpoint, WebSocket API request and WebSocket stream, and the decoding of the models
- Error scenarios and edge cases

## Contributing

Since this repository contains auto-generated code using OpenAPI Generator, we encourage you to:

1. Open a GitHub issue to discuss your ideas or report bugs
2. Allow maintainers to implement necessary changes through the code generation process

Manual edits to the generated connectors under `clients/` and `examples/` will be overwritten.

## Disclaimer

This SDK is provided by Binance on an "as is" and "as available" basis for use at your own risk. Binance makes no representations or warranties of any kind, whether express or implied, as to the operation of the SDK, its accuracy, reliability, completeness, or fitness for any particular purpose.

To the fullest extent permitted by law, Binance shall not be liable for any losses, damages, or expenses of any kind arising from or in connection with your use of, or inability to use, this SDK, including but not limited to any financial losses resulting from errors, bugs, interruptions, or inaccuracies in the SDK.

Your use of this SDK to access the Binance Platform is subject to the Binance API Key Terms and the Binance Terms of Use, which shall prevail in the event of any conflict with this disclaimer. You are solely responsible for any orders or transactions executed through the Binance Platform using this SDK.

This SDK is not intended to constitute investment advice or a recommendation to buy, sell, or hold any digital asset. You should independently evaluate and verify all information before acting.

- [Binance Terms of Use](https://www.binance.com/en/terms)
- [Binance API Key Terms](https://www.binance.com/en/about-legal/terms-binance-api)

## License

This project is licensed under the MIT License - see the [LICENCE](../../LICENCE) file for details.
