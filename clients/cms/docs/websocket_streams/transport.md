# Custom Transport

`transport` opens the TCP connection instead of the SDK, for networks the `proxy` option does not cover. `proxy` is ignored when it is set, and the socket is closed if the hook is still running after `connect_timeout`.

```cpp
#include <chrono>
#include <cstdint>
#include <iostream>
#include <string>
#include <thread>
#include <utility>

#include <boost/asio/awaitable.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/use_awaitable.hpp>

#include <binance/common/json.hpp>
#include <binance/cms/websocket_streams.hpp>

using namespace binance;

int main() {
    common::WebsocketStreamsConfig cfg;
    cfg.api_key = "your-api-key";
    cfg.api_secret = "your-api-secret";
    // Opens the TCP connection itself, e.g. through a tunnel of your own; TLS and the WebSocket
    // upgrade then run over `socket`. This one connects directly, like the SDK.
    cfg.transport = [](boost::asio::ip::tcp::socket& socket, std::string host,
                       std::uint16_t port) -> boost::asio::awaitable<void> {
        boost::asio::ip::tcp::resolver resolver(socket.get_executor());
        const auto endpoints =
            co_await resolver.async_resolve(host, std::to_string(port), boost::asio::use_awaitable);
        co_await boost::asio::async_connect(socket, endpoints, boost::asio::use_awaitable);
    };
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
