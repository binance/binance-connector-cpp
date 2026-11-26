# Compression

permessage-deflate is negotiated by default. `max_message_size` (64 MiB) caps a message after decompression; a larger one closes the connection.

```cpp
#include <chrono>
#include <iostream>
#include <thread>
#include <utility>

#include <binance/common/json.hpp>
#include <binance/alpha/websocket_streams.hpp>

using namespace binance;

int main() {
    common::WebsocketStreamsConfig cfg;
    cfg.compression = false;
    cfg.max_message_size = 16ULL * 1024 * 1024;
    auto client = alpha::AlphaWebsocketStreams::production(std::move(cfg));
    auto connection = client.connect();

    using namespace alpha::websocket_streams;
    const AllBookTickerStreamParams params{};
    auto stream = connection.all_book_ticker_stream(params);
    stream.on_message([](const auto& event) { std::cout << common::to_json(event) << "\n"; });
    std::this_thread::sleep_for(std::chrono::seconds(10));
    stream.unsubscribe();
    connection.disconnect();
}
```
