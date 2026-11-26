# TLS Agent

`agent` customises the TLS context before it is used: add certificate authorities, a client certificate, or verify certificates yourself. The system trust store is loaded first.

```cpp
#include <chrono>
#include <iostream>
#include <thread>
#include <utility>

#include <boost/asio/ssl.hpp>

#include <binance/common/json.hpp>
#include <binance/stock_options/websocket_streams.hpp>

using namespace binance;

int main() {
    common::WebsocketStreamsConfig cfg;
    cfg.agent = [](boost::asio::ssl::context& ctx) {
        // Trusted in addition to the system store, e.g. for a TLS-inspecting corporate proxy.
        ctx.load_verify_file("/path/to/ca.pem");
    };
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
