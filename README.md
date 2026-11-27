# Binance C++ Connector

[![Build Status](https://img.shields.io/github/actions/workflow/status/binance/binance-connector-cpp/ci.yaml)](https://github.com/binance/binance-connector-cpp/actions)
[![Open Issues](https://img.shields.io/github/issues/binance/binance-connector-cpp)](https://github.com/binance/binance-connector-cpp/issues)
![C++ Standard](https://img.shields.io/badge/C%2B%2B-20-blue)
![CMake Version](https://img.shields.io/badge/CMake-%3E=3.24-brightgreen)
[![Docs](https://img.shields.io/badge/docs-online-blue?style=flat-square)](https://binance.github.io/binance-connector-cpp/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

Official collection of auto-generated C++ connectors for Binance APIs.

Every connector offers typed REST API, WebSocket API and WebSocket Streams clients, built on the
shared [`binance::common`](./common) library (signing, HTTP, WebSocket connection management,
errors and utilities).

## Prerequisites

Before using the connectors, ensure you have:

- **A C++20 compiler**: GCC 12+, Clang 15+, Apple Clang 15+ or MSVC 19.34+ (Visual Studio 2022 17.4)
- **CMake** (version 3.24 or later) and **Ninja**
- **[vcpkg](https://github.com/microsoft/vcpkg)**, with `VCPKG_ROOT` set. It installs the dependencies
  listed in [`vcpkg.json`](./vcpkg.json): Boost.Asio, Boost.Beast, Boost.JSON, OpenSSL 3 and zlib.

```bash
git clone https://github.com/microsoft/vcpkg.git ~/vcpkg
~/vcpkg/bootstrap-vcpkg.sh
export VCPKG_ROOT=~/vcpkg
```

## Available Connectors

Each connector is a CMake component and target. Build or install only the ones you need:

| Connector | Product | REST API | WebSocket API | WebSocket Streams |
| --- | --- | :---: | :---: | :---: |
| [`algo`](./clients/algo/) | Algo Trading | ✅ | | |
| [`alpha`](./clients/alpha/) | Alpha | ✅ | | ✅ |
| [`c2c`](./clients/c2c/) | C2C | ✅ | | |
| [`cms`](./clients/cms/) | CMS (Announcements) | | | ✅ |
| [`convert`](./clients/convert/) | Convert | ✅ | | |
| [`copy_trading`](./clients/copy_trading/) | Copy Trading | ✅ | | |
| [`crypto_loan`](./clients/crypto_loan/) | Crypto Loan | ✅ | | |
| [`derivatives_trading_coin_futures`](./clients/derivatives_trading_coin_futures/) | Derivatives Trading (COIN-M Futures) | ✅ | ✅ | ✅ |
| [`derivatives_trading_options`](./clients/derivatives_trading_options/) | Derivatives Trading (Options) | ✅ | | ✅ |
| [`derivatives_trading_portfolio_margin`](./clients/derivatives_trading_portfolio_margin/) | Derivatives Trading (Portfolio Margin) | ✅ | | ✅ |
| [`derivatives_trading_portfolio_margin_pro`](./clients/derivatives_trading_portfolio_margin_pro/) | Derivatives Trading (Portfolio Margin Pro) | ✅ | | ✅ |
| [`derivatives_trading_usds_futures`](./clients/derivatives_trading_usds_futures/) | Derivatives Trading (USDS-M Futures) | ✅ | ✅ | ✅ |
| [`dual_investment`](./clients/dual_investment/) | Dual Investment | ✅ | | |
| [`fiat`](./clients/fiat/) | Fiat | ✅ | | |
| [`gift_card`](./clients/gift_card/) | Gift Card | ✅ | | |
| [`margin_trading`](./clients/margin_trading/) | Margin Trading | ✅ | | ✅ |
| [`mining`](./clients/mining/) | Mining | ✅ | | |
| [`pay`](./clients/pay/) | Pay | ✅ | | |
| [`rebate`](./clients/rebate/) | Rebate | ✅ | | |
| [`simple_earn`](./clients/simple_earn/) | Simple Earn | ✅ | | |
| [`spot`](./clients/spot/) | Spot Trading | ✅ | ✅ | ✅ |
| [`staking`](./clients/staking/) | Staking | ✅ | | |
| [`stock_options`](./clients/stock_options/) | Stock Options | ✅ | | ✅ |
| [`stocks`](./clients/stocks/) | Stocks | ✅ | | ✅ |
| [`sub_account`](./clients/sub_account/) | Sub Account | ✅ | | |
| [`vip_loan`](./clients/vip_loan/) | VIP Loan | ✅ | | |
| [`w3w_prediction`](./clients/w3w_prediction/) | W3W Prediction | ✅ | | ✅ |
| [`wallet`](./clients/wallet/) | Wallet | ✅ | | |

## Documentation

- **API reference:** [binance.github.io/binance-connector-cpp](https://binance.github.io/binance-connector-cpp/)
- **Common library:** [`common/README.md`](./common/README.md) — configuration, error handling,
  WebSocket behaviour and the low-level clients.
- **Examples:** [`examples/<connector>/`](./examples) has one program for every endpoint.
- **Official Binance API docs:** [Binance API Documentation](https://developers.binance.com)

## Installation

### With vcpkg

The repository contains a vcpkg port in [`ports/binance-connector-cpp`](./ports/binance-connector-cpp).
Use it as an overlay port: it builds the checkout it is in, so check out the release you want first
(`git checkout v2.0.0`). Every connector is a feature named like the product, with hyphens instead
of underscores (vcpkg does not allow them): `copy-trading` builds the `copy_trading` component. Name
the connectors you need (there is no default one: without features, only `binance::common` is built), or
`all` for every connector:

```bash
vcpkg install "binance-connector-cpp[spot]" --overlay-ports=/path/to/binance-connector-cpp/ports
vcpkg install "binance-connector-cpp[wallet,derivatives-trading-usds-futures]" --overlay-ports=/path/to/binance-connector-cpp/ports
vcpkg install "binance-connector-cpp[all]" --overlay-ports=/path/to/binance-connector-cpp/ports
```

In a `vcpkg.json` manifest, list the features you need:
`{ "name": "binance-connector-cpp", "features": ["spot", "wallet"] }`.

In manifest mode, pass `--overlay-ports` the same way or set `VCPKG_OVERLAY_PORTS`.

### From source

Build and install the connectors you need, for example `spot` (list several with semicolons,
e.g. `-DBINANCE_PRODUCTS="spot;wallet"`; by default every connector under `clients/` is built):

```bash
cmake --preset release -DBINANCE_PRODUCTS=spot
cmake --build --preset release
cmake --install build/release --prefix /opt/binance --strip
```

Then use them from your CMake project, with the same vcpkg toolchain:

```cmake
find_package(binance-connector-cpp CONFIG REQUIRED COMPONENTS spot)
target_link_libraries(app PRIVATE binance::spot)  # binance::common comes with it
```

Signed order on the Spot testnet, with the credentials read from the environment (`order_test` validates
the order without placing it; use `new_order` to place it):

```cpp
#include <cstdlib>
#include <iostream>
#include <utility>

#include <binance/spot/rest_api.hpp>

using namespace binance;

int main() {
    common::RestApiConfig cfg;
    if (const char* key = std::getenv("API_KEY")) cfg.api_key = key;
    if (const char* secret = std::getenv("API_SECRET")) cfg.api_secret = secret;
    // Ed25519/RSA keys: cfg.private_key = common::PrivateKey::from_file("key.pem") instead of the secret
    const auto rest = spot::SpotRestApi::testnet(std::move(cfg));

    std::cout << rest.time().data().server_time.value_or(0) << "\n";

    using namespace spot::rest_api;
    const auto response = rest.order_test({.symbol = "BNBUSDT",
                     .side = OrderTestSideEnum::Buy,
                     .type = OrderTestTypeEnum::Limit,
                     .time_in_force = OrderTestTimeInForceEnum::Gtc,
                     .quantity = common::Decimal("0.1"),
                     .price = common::Decimal("100")});
    std::cout << "order accepted, HTTP " << response.status() << "\n";
}
```

Market data stream (public, no credentials):

```cpp
#include <chrono>
#include <iostream>
#include <thread>
#include <utility>

#include <binance/spot/websocket_streams.hpp>

using namespace binance;

int main() {
    auto client = spot::SpotWebsocketStreams::production({});
    auto connection = client.connect();  // open once connect() returns
    auto trades = connection.agg_trade({.symbol = "bnbusdt"});
    trades.on_message([](const auto&) { std::cout << "trade\n"; });
    std::this_thread::sleep_for(std::chrono::seconds(10));  // messages arrive on the client's threads
    connection.disconnect();
}
```

### Adding it to your CMake project

Instead of installing it, you can also build the SDK as part of your project with `FetchContent`
(or `add_subdirectory`). Your project then provides the dependencies, e.g. by listing
`boost-asio`, `boost-beast`, `boost-json`, `openssl` and `zlib` in its own `vcpkg.json`:

```cmake
include(FetchContent)
set(BINANCE_PRODUCTS "spot" CACHE STRING "" FORCE)
FetchContent_Declare(binance-connector-cpp
    GIT_REPOSITORY https://github.com/binance/binance-connector-cpp.git
    GIT_TAG v2.0.0)
FetchContent_MakeAvailable(binance-connector-cpp)
target_link_libraries(app PRIVATE binance::spot)
```

vcpkg is not required: Boost 1.86+ (Asio, Beast, JSON), OpenSSL 3 and zlib from your system
package manager work too, e.g. `cmake -S . -B build -DBINANCE_PRODUCTS=spot` with
`libboost-all-dev libssl-dev zlib1g-dev` on Ubuntu 25.10 (24.04 ships Boost 1.83, which is too old). An installed SDK requires at least the Boost version it was built with, and
should be used with that same version, because its public headers include Boost.Asio templates.

### Including the headers

`<binance/spot/spot.hpp>` includes every client of a connector; including only the module you use
(`rest_api.hpp`, `websocket_api.hpp` or `websocket_streams.hpp`) keeps compile times down. Each
module has factories for its environments: `production`, `testnet` and, where available, `demo`.

### Build options

| CMake option                 | Default               | Description                                                                            |
| ---------------------------- | --------------------- | -------------------------------------------------------------------------------------- |
| `BINANCE_PRODUCTS`           | `all`                 | Connectors to build, e.g. `spot;derivatives_trading_usds_futures` (`""` = common only) |
| `BINANCE_BUILD_TESTS`        | `OFF`                 | Build the GoogleTest suites (`ON` in `dev`, `ci`, `asan`, `tsan` and `release-tests`)   |
| `BINANCE_BUILD_EXAMPLES`     | `OFF`                 | Build the examples (`ON` in `dev`, `ci`, `asan` and `tsan`)                             |
| `BINANCE_WARNINGS_AS_ERRORS` | `OFF`                 | Treat warnings as errors (`ON` in the `dev`, `ci` and `release-tests` presets)         |
| `BUILD_SHARED_LIBS`          | `OFF`                 | Build shared libraries                                                                 |
| `BINANCE_LTO`                | `ON`                  | Link-time optimisation of shared Release builds                                        |
| `BINANCE_BUILD_C_API`        | `OFF`                 | Build `libbinance_c`, the C interface for language bindings (see [C API](#c-api))      |
| `BINANCE_INSTALL`            | `ON` when top-level   | Generate the install rules and the CMake package                                       |

Release builds put every function in its own section so the linker can drop unused code: link
your program with `-Wl,-dead_strip` (macOS) or `-Wl,--gc-sections` (Linux) to benefit from it.
Shared libraries hide the symbols of the static dependencies they bundle on Linux; on macOS, use a
dynamic vcpkg triplet (`-DVCPKG_TARGET_TRIPLET=arm64-osx-dynamic`) to keep them out of the library.
On Windows, a DLL build must be used with the MSVC toolset and runtime (`/MD` or `/MDd`) it was
built with, and `binance::common` sets `_WIN32_WINNT=0x0A00` (Windows 10) for its consumers, since
Asio's types depend on it.

### C API

`-DBINANCE_BUILD_C_API=ON` builds `libbinance_c`, a shared library with a plain C interface to
`binance::common`, for bindings in other languages. The interface is declared and documented in
[`c_api/include/binance/binance_c.h`](./c_api/include/binance/binance_c.h); the library exports
only the `bnc_*` functions and bundles its dependencies.

### Versioning

Releases follow [Semantic Versioning](https://semver.org) for the API: only a major release breaks
code that builds against the SDK, and `find_package` accepts any release with the requested major
version. The C++ ABI is kept only between patch releases: a minor release adds fields to the request
and response structs whenever the Binance API adds parameters, which changes their layout. Shared
libraries therefore carry `<major>.<minor>` as their SOVERSION (`libbinance_spot.so.1.0`), so that a
program is never loaded with a library it was not built against: rebuild it for a new minor release.
Static libraries, vcpkg and FetchContent build from source and are not affected. The stable binary
interface is the C API: `libbinance_c` is versioned by its C ABI, and its SOVERSION is
`BNC_ABI_VERSION`, which changes with every incompatible change to `binance_c.h`. Headers under `binance/common/detail/` and names in
`detail` namespaces are internal and may change in any release.

## Development

Besides the [prerequisites](#prerequisites), `make format`, `make lint` and `make docs` need
clang-format, clang-tidy (with its `run-clang-tidy` script), Doxygen and jq:

```bash
# macOS
brew install cmake ninja llvm doxygen jq
export PATH="$(brew --prefix llvm)/bin:$PATH"

# Debian / Ubuntu
sudo apt install build-essential cmake ninja-build clang-format clang-tidy doxygen jq

# Windows
winget install Kitware.CMake Ninja-build.Ninja LLVM.LLVM DimitriVanHeesch.Doxygen jqlang.jq
```

The checks of `make lint` are listed one by one in [`.clang-tidy`](./.clang-tidy), so that a newer
clang-tidy adds none by itself; it lints the library sources (`common/src`, `clients/*/src`).

The build is driven by the [CMake presets](./CMakePresets.json):

| Preset          | Build                                                      |
| --------------- | ---------------------------------------------------------- |
| `dev`           | Debug, tests, examples, warnings as errors (pull requests) |
| `release-tests` | Release (optimised), tests, warnings as errors             |
| `asan`, `tsan`  | `dev` with the address / undefined or thread sanitizers    |
| `release`       | Release without tests, for installing                      |
| `ci`            | RelWithDebInfo, tests (the full CI, started manually)      |

```bash
cmake --preset dev -DBINANCE_PRODUCTS=spot   # configure, one connector (or "all")
cmake --build --preset dev                   # build
ctest --preset dev                           # run the tests, 4 in parallel (override with -j N)
```

`make` wraps the same commands, and `make help` shows its usage:

| Command                                         | What it does                                                 |
| ----------------------------------------------- | ------------------------------------------------------------ |
| `make test [PRODUCTS=spot] [PRESET=dev] [JOBS=8]` | configure, build and test (`JOBS` applies to build and tests) |
| `make example NAME=spot/websocket_streams/agg_trade` | build and run one example                                   |
| `make format` / `make format-check`             | format the sources with clang-format / check the formatting  |
| `make lint` / `make lint-fix`                   | run clang-tidy (fails on a warning) / apply its fixes        |
| `make asan`                                     | the tests under the address and undefined behaviour sanitizers |
| `make install` / `make install-check`           | install into `build/<preset>/install` / build a consumer against it |
| `make docs`                                     | generate the API reference with Doxygen                      |
| `make clean`                                    | remove `build/`                                              |

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

This project is licensed under the MIT License - see the [LICENCE](./LICENCE) file for details.
