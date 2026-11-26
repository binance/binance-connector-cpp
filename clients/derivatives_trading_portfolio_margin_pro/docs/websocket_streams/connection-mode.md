# Connection Mode

One connection by default. `WebsocketMode::pool(n)` opens `n` connections and spreads the streams over them, so that one slow or dropped connection does not hold up the others.

```cpp
#include <chrono>
#include <iostream>
#include <thread>
#include <utility>

#include <binance/common/json.hpp>
#include <binance/derivatives_trading_portfolio_margin_pro/websocket_streams.hpp>

using namespace binance;

int main() {
    common::WebsocketStreamsConfig cfg;
    cfg.mode = common::WebsocketMode::pool(3);
    auto client = derivatives_trading_portfolio_margin_pro::DerivativesTradingPortfolioMarginProWebsocketStreams::production(std::move(cfg));
    auto connection = client.connect();

    using namespace derivatives_trading_portfolio_margin_pro::websocket_streams;
    const std::string listen_key = "your-listen-key";
    auto stream = connection.user_data(listen_key);
    stream.on_message([](const auto& event) { std::cout << common::to_json(event) << "\n"; });
    std::this_thread::sleep_for(std::chrono::seconds(10));
    stream.unsubscribe();
    connection.disconnect();
}
```
