# Timestamp Provider

The `timestamp` of signed connection URLs comes from the host clock. When the host clock is off by more than `recvWindow` (error `-1021`), provide a corrected one. Keep it cheap and thread-safe: it may be called from the client thread.

```cpp
#include <atomic>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <thread>
#include <utility>

#include <binance/common/json.hpp>
#include <binance/w3w_prediction/websocket_streams.hpp>

using namespace binance;

// Host clock offset to Binance, in milliseconds: `serverTime` minus the local time, measured at
// start-up and refreshed from time to time (e.g. from the time endpoint).
std::atomic<std::int64_t> clock_offset{0};

int main() {
    common::WebsocketStreamsConfig cfg;
    cfg.api_key = "your-api-key";
    cfg.api_secret = "your-api-secret";
    cfg.timestamp_provider = [] {
        const auto now = std::chrono::system_clock::now().time_since_epoch();
        return std::chrono::duration_cast<std::chrono::milliseconds>(now).count() + clock_offset.load();
    };
    auto client = w3w_prediction::W3WPredictionWebsocketStreams::production(std::move(cfg));
    auto connection = client.connect();

    using namespace w3w_prediction::websocket_streams;
    auto stream = connection.market_buy_order_failed();
    stream.on_message([](const auto& event) { std::cout << common::to_json(event) << "\n"; });
    std::this_thread::sleep_for(std::chrono::seconds(10));
    stream.unsubscribe();
    connection.disconnect();
}
```
