# Binance C++ CMS Connector

![C++ Standard](https://img.shields.io/badge/C%2B%2B-20-blue)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

`binance::cms` is the official C++ connector for the Binance CMS WebSocket Streams. Access the Binance CMS APIs.

It is one component of the [Binance C++ Connector](../../README.md), built on the shared
[`binance::common`](../../common/README.md) library.

## Table of Contents

- [Supported Features](#supported-features)
- [Installation](#installation)
- [Documentation](#documentation)
- [WebSocket Streams](#websocket-streams)
- [Automatic Connection Renewal](#automatic-connection-renewal)
- [Logging](#logging)
- [Examples](#examples)
- [Testing](#testing)
- [Contributing](#contributing)
- [Disclaimer](#disclaimer)
- [License](#license)

## Supported Features

- [WebSocket Streams](./include/binance/cms/websocket_streams/websocket_streams.hpp): `binance::cms::CmsWebsocketStreams`

- A typed method for every endpoint and stream, with a `Params` struct for its parameters and
  a typed response, decoded on demand. Prices and quantities are exact decimals (`common::Decimal`).
- Blocking calls, and `async_` variants that take any Asio completion token (callback, `use_future`,
  `use_awaitable`, ...).
- Request signing with HMAC-SHA256, RSA or Ed25519 keys.
- WebSocket: reconnects with backoff, connection pools, and connections renewed before Binance closes
  them.
- HTTP(S) proxies, also from the environment, and a hook to add CAs or pin certificates.

## Installation

With vcpkg, as an overlay port of this repository (see the [root README](../../README.md#installation)):

```bash
vcpkg install "binance-connector-cpp[cms]" --overlay-ports=/path/to/binance-connector-cpp/ports
```

From source, building only this connector:

```bash
cmake --preset release -DBINANCE_PRODUCTS=cms
cmake --build --preset release
cmake --install build/release --prefix /opt/binance --strip
```

Then, in your `CMakeLists.txt`:

```cmake
find_package(binance-connector-cpp CONFIG REQUIRED COMPONENTS cms)
target_link_libraries(app PRIVATE binance::cms)  # binance::common comes with it
```

`#include <binance/cms/cms.hpp>` includes every client of the connector; include
`<binance/cms/websocket_streams.hpp>`
for just one of them.

## Documentation

- **API reference:** [binance.github.io/binance-connector-cpp](https://binance.github.io/binance-connector-cpp/)
- **Configuration, errors and connection behaviour:** [`common/README.md`](../../common/README.md)
- **Examples:** [`examples/cms/`](../../examples/cms/) has one program for every endpoint and stream.
- **Official Binance CMS API docs:** [https://developers.binance.com/en/docs/products/announcements/cms-log](https://developers.binance.com/en/docs/products/announcements/cms-log)

### WebSocket Streams

```cpp
#include <chrono>
#include <iostream>
#include <thread>
#include <utility>

#include <binance/common/json.hpp>
#include <binance/cms/websocket_streams.hpp>

using namespace binance;

int main() {
    common::WebsocketStreamsConfig cfg;
    cfg.api_key = "your-api-key";
    cfg.api_secret = "your-api-secret";  // or cfg.private_key = common::PrivateKey::from_file("key.pem")
    auto client = cms::CmsWebsocketStreams::production(std::move(cfg));
    auto connection = client.connect();

    using namespace cms::websocket_streams;
    auto stream = connection.com_announcement_en();
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

These streams are signed: the configuration needs `api_key` and `api_secret` (or `private_key`),
and every connection signs its URL again when it reconnects.

#### Configuration Options

The client is configured with a `common::WebsocketStreamsConfig`:

| Option | Default | Description |
| --- | --- | --- |
| `api_key`, `api_secret`, `private_key` | none | Credentials of the signed streams. |
| `timestamp_provider` | host clock | The `timestamp` of the signed connection URLs. |
| `url` | set by the factory | Another endpoint for the client (see [Environments](#cms-websocket-streams-environments)). |
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
- [Key Pair Based Authentication](./docs/websocket_streams/key-pair-authentication.md)
- [Timestamp Provider](./docs/websocket_streams/timestamp-provider.md)
- [Shared Event Loop](./docs/websocket_streams/executor.md)

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

<a id="cms-websocket-streams-environments"></a>
The client is created with `CmsWebsocketStreams::production(cfg)`, or with `from_config(cfg)` for the endpoint in
`cfg.url`.

### Automatic Connection Renewal

WebSocket connections are renewed every 23 hours, before Binance closes them after 24, and when the
server announces a shutdown. The new connection is opened before the old one is closed, so
streams carry on without a gap.

## Logging

The connector logs through `common::Logger`. Set the level with `common::Logger::set_level` or the
`LOG_LEVEL` environment variable (`debug`, `info`, `warn`, `error`, `none`), and send the messages
elsewhere with `common::Logger::set_sink`. Configurations printed with `operator<<` have their
secrets redacted.

## Examples

[`examples/cms/`](../../examples/cms/) has one runnable program for every endpoint and stream.
See its [README](../../examples/cms/README.md) to build and run them.

## Testing

The tests run the connector against local mock servers, with the example responses of the API.
From the root of the repository:

```bash
make test PRODUCTS=cms
# or, with CMake directly:
cmake --preset dev -DBINANCE_PRODUCTS=cms
cmake --build --preset dev
ctest --preset dev
```

Tests cover:

- Every WebSocket stream, and the decoding of the models
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
