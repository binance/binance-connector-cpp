# Connection Mode

One connection by default. `WebsocketMode::pool(n)` opens `n` connections and spreads the requests over them, so that one slow or dropped connection does not hold up the others.

```cpp
#include <iostream>
#include <utility>

#include <binance/common/json.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_api.hpp>

using namespace binance;

int main() {
    common::WebsocketApiConfig cfg;
    cfg.api_key = "your-api-key";
    cfg.api_secret = "your-api-secret";
    cfg.mode = common::WebsocketMode::pool(3);
    auto client = derivatives_trading_usds_futures::DerivativesTradingUsdsFuturesWebsocketApi::production(std::move(cfg));
    auto connection = client.connect();

    using namespace derivatives_trading_usds_futures::websocket_api;
    const SymbolOrderBookTickerParams params{};
    const auto response = connection.symbol_order_book_ticker(params);
    std::cout << common::to_json(response.data()) << "\n";
    connection.disconnect();
}
```
