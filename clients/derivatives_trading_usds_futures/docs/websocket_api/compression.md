# Compression

permessage-deflate is negotiated by default. `max_message_size` (64 MiB) caps a message after decompression; a larger one closes the connection.

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
    cfg.compression = false;
    cfg.max_message_size = 16ULL * 1024 * 1024;
    auto client = derivatives_trading_usds_futures::DerivativesTradingUsdsFuturesWebsocketApi::production(std::move(cfg));
    auto connection = client.connect();

    using namespace derivatives_trading_usds_futures::websocket_api;
    const SymbolOrderBookTickerParams params{};
    const auto response = connection.symbol_order_book_ticker(params);
    std::cout << common::to_json(response.data()) << "\n";
    connection.disconnect();
}
```
