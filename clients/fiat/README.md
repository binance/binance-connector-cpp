# Binance C++ Fiat Connector

![C++ Standard](https://img.shields.io/badge/C%2B%2B-20-blue)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

`binance::fiat` is the official C++ connector for the Binance Fiat REST API. Query Binance fiat deposit and withdrawal history.

It is one component of the [Binance C++ Connector](../../README.md), built on the shared
[`binance::common`](../../common/README.md) library.

## Table of Contents

- [Supported Features](#supported-features)
- [Installation](#installation)
- [Documentation](#documentation)
- [REST APIs](#rest-apis)
- [Asynchronous Calls](#asynchronous-calls)
- [Logging](#logging)
- [Examples](#examples)
- [Testing](#testing)
- [Contributing](#contributing)
- [Disclaimer](#disclaimer)
- [License](#license)

## Supported Features

- [REST API](./include/binance/fiat/rest_api/rest_api.hpp): `binance::fiat::FiatRestApi`

- A typed method for every endpoint, with a `Params` struct for its parameters and
  a typed response, decoded on demand. Prices and quantities are exact decimals (`common::Decimal`).
- Blocking calls, and `async_` variants that take any Asio completion token (callback, `use_future`,
  `use_awaitable`, ...).
- Request signing with HMAC-SHA256, RSA or Ed25519 keys.
- REST: connection reuse, retries with backoff, gzip / deflate responses and the rate limits of every
  response.
- HTTP(S) proxies, also from the environment, and a hook to add CAs or pin certificates.

## Installation

With vcpkg, as an overlay port of this repository (see the [root README](../../README.md#installation)):

```bash
vcpkg install "binance-connector-cpp[fiat]" --overlay-ports=/path/to/binance-connector-cpp/ports
```

From source, building only this connector:

```bash
cmake --preset release -DBINANCE_PRODUCTS=fiat
cmake --build --preset release
cmake --install build/release --prefix /opt/binance --strip
```

Then, in your `CMakeLists.txt`:

```cmake
find_package(binance-connector-cpp CONFIG REQUIRED COMPONENTS fiat)
target_link_libraries(app PRIVATE binance::fiat)  # binance::common comes with it
```

`#include <binance/fiat/fiat.hpp>` includes every client of the connector; include
`<binance/fiat/rest_api.hpp>`
for just one of them.

## Documentation

- **API reference:** [binance.github.io/binance-connector-cpp](https://binance.github.io/binance-connector-cpp/)
- **Configuration, errors and connection behaviour:** [`common/README.md`](../../common/README.md)
- **Examples:** [`examples/fiat/`](../../examples/fiat/) has one program for every endpoint.
- **Official Binance Fiat API docs:** [https://developers.binance.com/en/docs/products/fiat/Introduction](https://developers.binance.com/en/docs/products/fiat/Introduction)

### REST APIs

```cpp
#include <iostream>
#include <utility>

#include <binance/common/json.hpp>
#include <binance/fiat/rest_api.hpp>

using namespace binance;

int main() {
    common::RestApiConfig cfg;
    cfg.api_key = "your-api-key";
    cfg.api_secret = "your-api-secret";  // or cfg.private_key = common::PrivateKey::from_file("key.pem")
    const auto client = fiat::FiatRestApi::production(std::move(cfg));

    using namespace fiat::rest_api;
    const GetFiatDepositWithdrawHistoryParams params{.transaction_type = "0"};
    const auto response = client.get_fiat_deposit_withdraw_history(params);
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
| `base_path` | set by the factory | Another endpoint for the client (see [Environments](#fiat-rest-api-environments)). |
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
    const auto response = client.get_fiat_deposit_withdraw_history(params);
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
    "/sapi/v1/endpoint", common::HttpMethod::Get, {{"symbol", "BNBUSDT"}});
```

<a id="fiat-rest-api-environments"></a>
The client is created with `FiatRestApi::production(cfg)`, or with `from_config(cfg)` for the endpoint in
`cfg.base_path`.

### Asynchronous Calls

Every method has an `async_` variant that takes a completion token as its last argument:

```cpp
// In a coroutine
const auto response = co_await client.async_get_fiat_deposit_withdraw_history(params, boost::asio::use_awaitable);

// With a future
auto future = client.async_get_fiat_deposit_withdraw_history(params, boost::asio::use_future);

// With a callback (runs on the client's thread)
client.async_get_fiat_deposit_withdraw_history(params, [](std::exception_ptr error, auto response) { /* ... */ });
```

Callbacks run on the client's executor, so they should not block. Errors are delivered as a
`std::exception_ptr`.

## Logging

The connector logs through `common::Logger`. Set the level with `common::Logger::set_level` or the
`LOG_LEVEL` environment variable (`debug`, `info`, `warn`, `error`, `none`), and send the messages
elsewhere with `common::Logger::set_sink`. Configurations printed with `operator<<` have their
secrets redacted.

## Examples

[`examples/fiat/`](../../examples/fiat/) has one runnable program for every endpoint.
See its [README](../../examples/fiat/README.md) to build and run them.

## Testing

The tests run the connector against local mock servers, with the example responses of the API.
From the root of the repository:

```bash
make test PRODUCTS=fiat
# or, with CMake directly:
cmake --preset dev -DBINANCE_PRODUCTS=fiat
cmake --build --preset dev
ctest --preset dev
```

Tests cover:

- Every REST API endpoint, and the decoding of the models
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
