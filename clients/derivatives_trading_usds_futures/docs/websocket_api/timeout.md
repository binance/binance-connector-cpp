# Timeout

How long to wait for the response of a request (5000 ms by default). `connect_timeout` (10000 ms) is the time allowed to open a connection: DNS, TCP, proxy, TLS and the WebSocket upgrade.

```cpp
#include <chrono>
#include <iostream>
#include <utility>

#include <binance/common/json.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_api.hpp>

using namespace binance;

int main() {
    common::WebsocketApiConfig cfg;
    cfg.api_key = "your-api-key";
    cfg.api_secret = "your-api-secret";
    cfg.timeout = std::chrono::milliseconds(10000);
    cfg.connect_timeout = std::chrono::milliseconds(5000);
    auto client = derivatives_trading_usds_futures::DerivativesTradingUsdsFuturesWebsocketApi::production(std::move(cfg));
    auto connection = client.connect();

    using namespace derivatives_trading_usds_futures::websocket_api;
    const SymbolOrderBookTickerParams params{};
    const auto response = connection.symbol_order_book_ticker(params);
    std::cout << common::to_json(response.data()) << "\n";
    connection.disconnect();
}
```
