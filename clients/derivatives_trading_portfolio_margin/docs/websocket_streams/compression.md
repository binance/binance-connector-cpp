# Compression

permessage-deflate is negotiated by default. `max_message_size` (64 MiB) caps a message after decompression; a larger one closes the connection.

```cpp
#include <chrono>
#include <iostream>
#include <thread>
#include <utility>

#include <binance/common/json.hpp>
#include <binance/derivatives_trading_portfolio_margin/websocket_streams.hpp>

using namespace binance;

int main() {
    common::WebsocketStreamsConfig cfg;
    cfg.compression = false;
    cfg.max_message_size = 16ULL * 1024 * 1024;
    auto client = derivatives_trading_portfolio_margin::DerivativesTradingPortfolioMarginWebsocketStreams::production(std::move(cfg));
    auto connection = client.connect();

    using namespace derivatives_trading_portfolio_margin::websocket_streams;
    const std::string listen_key = "your-listen-key";
    auto stream = connection.user_data(listen_key);
    stream.on_message([](const auto& event) { std::cout << common::to_json(event) << "\n"; });
    std::this_thread::sleep_for(std::chrono::seconds(10));
    stream.unsubscribe();
    connection.disconnect();
}
```
