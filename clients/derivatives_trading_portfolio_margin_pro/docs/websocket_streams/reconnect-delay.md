# Reconnect Delay

Delay before reconnecting a connection that dropped (5000 ms by default). After a failed attempt, a backoff of 1 s doubling up to 60 s, with random jitter, is added to it. The subscriptions are restored after the reconnect.

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
    cfg.reconnect_delay = std::chrono::milliseconds(1000);
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
