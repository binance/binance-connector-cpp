# Shared Event Loop

Each client runs its own I/O thread by default. Set `executor` to run many clients on one event loop. Keep the loop running while the clients have work, and do not make blocking calls from its threads.

```cpp
#include <chrono>
#include <iostream>
#include <thread>
#include <utility>

#include <boost/asio/executor_work_guard.hpp>
#include <boost/asio/io_context.hpp>

#include <binance/common/json.hpp>
#include <binance/margin_trading/websocket_streams.hpp>

using namespace binance;

int main() {
    boost::asio::io_context ioc;
    auto work = boost::asio::make_work_guard(ioc);
    std::thread loop([&ioc] { ioc.run(); });
    {
        common::WebsocketStreamsConfig cfg;
        cfg.executor = ioc.get_executor();
        auto client = margin_trading::MarginTradingWebsocketStreams::production(std::move(cfg));
        auto connection = client.connect();

        using namespace margin_trading::websocket_streams;
        const std::string listen_key = "your-listen-key";
        auto stream = connection.risk_data(listen_key);
        stream.on_message([](const auto& event) { std::cout << common::to_json(event) << "\n"; });
        std::this_thread::sleep_for(std::chrono::seconds(10));
        stream.unsubscribe();
        connection.disconnect();
    }  // destroy the clients before stopping the loop
    work.reset();
    loop.join();
}
```
