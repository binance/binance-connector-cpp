# Connection Mode

One connection by default. `WebsocketMode::pool(n)` opens `n` connections and spreads the streams over them, so that one slow or dropped connection does not hold up the others.

```cpp
#include <chrono>
#include <iostream>
#include <thread>
#include <utility>

#include <binance/common/json.hpp>
#include <binance/stocks/websocket_streams.hpp>

using namespace binance;

int main() {
    common::WebsocketStreamsConfig cfg;
    cfg.mode = common::WebsocketMode::pool(3);
    auto client = stocks::StocksWebsocketStreams::production(std::move(cfg));
    auto connection = client.connect();

    using namespace stocks::websocket_streams;
    const CalendarStreamParams params{};
    auto stream = connection.calendar_stream(params);
    stream.on_message([](const auto& event) { std::cout << common::to_json(event) << "\n"; });
    std::this_thread::sleep_for(std::chrono::seconds(10));
    stream.unsubscribe();
    connection.disconnect();
}
```
