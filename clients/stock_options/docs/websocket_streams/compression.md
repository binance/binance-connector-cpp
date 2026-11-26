# Compression

permessage-deflate is negotiated by default. `max_message_size` (64 MiB) caps a message after decompression; a larger one closes the connection.

```cpp
#include <chrono>
#include <iostream>
#include <thread>
#include <utility>

#include <binance/common/json.hpp>
#include <binance/stock_options/websocket_streams.hpp>

using namespace binance;

int main() {
    common::WebsocketStreamsConfig cfg;
    cfg.compression = false;
    cfg.max_message_size = 16ULL * 1024 * 1024;
    auto client = stock_options::StockOptionsWebsocketStreams::production(std::move(cfg));
    auto connection = client.connect();

    using namespace stock_options::websocket_streams;
    const OrderReportV2StreamParams params{.listen_key =
                                               "3f9a1c2e-7b4d-4e8a-9c61-0d2f5b7e8a13"};
    auto stream = connection.order_report_v2_stream(params);
    stream.on_message([](const auto& event) { std::cout << common::to_json(event) << "\n"; });
    std::this_thread::sleep_for(std::chrono::seconds(10));
    stream.unsubscribe();
    connection.disconnect();
}
```
