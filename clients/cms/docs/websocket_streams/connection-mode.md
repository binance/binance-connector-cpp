# Connection Mode

One connection by default. `WebsocketMode::pool(n)` opens `n` connections and spreads the streams over them, so that one slow or dropped connection does not hold up the others.

```cpp
#include <chrono>
#include <iostream>
#include <thread>
#include <utility>

#include <binance/common/json.hpp>
#include <binance/cms/websocket_streams.hpp>

using namespace binance;

int main() {
    common::WebsocketStreamsConfig cfg;
    cfg.api_key = "your-api-key";
    cfg.api_secret = "your-api-secret";
    cfg.mode = common::WebsocketMode::pool(3);
    auto client = cms::CmsWebsocketStreams::production(std::move(cfg));
    auto connection = client.connect();

    using namespace cms::websocket_streams;
    auto stream = connection.com_announcement_en();
    stream.on_message([](const auto& event) { std::cout << common::to_json(event) << "\n"; });
    std::this_thread::sleep_for(std::chrono::seconds(10));
    stream.unsubscribe();
    connection.disconnect();
}
```
