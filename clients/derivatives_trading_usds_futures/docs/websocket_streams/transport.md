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
#include <binance/derivatives_trading_usds_futures/websocket_streams.hpp>

using namespace binance;

int main() {
    common::WebsocketStreamsConfig cfg;
    // Opens the TCP connection itself, e.g. through a tunnel of your own; TLS and the WebSocket
    // upgrade then run over `socket`. This one connects directly, like the SDK.
    cfg.transport = [](boost::asio::ip::tcp::socket& socket, std::string host,
                       std::uint16_t port) -> boost::asio::awaitable<void> {
        boost::asio::ip::tcp::resolver resolver(socket.get_executor());
        const auto endpoints =
            co_await resolver.async_resolve(host, std::to_string(port), boost::asio::use_awaitable);
        co_await boost::asio::async_connect(socket, endpoints, boost::asio::use_awaitable);
    };
    auto client = derivatives_trading_usds_futures::DerivativesTradingUsdsFuturesWebsocketStreams::production(std::move(cfg));
    auto connection = client.connect();

    using namespace derivatives_trading_usds_futures::websocket_streams;
    const AllBookTickersStreamParams params{};
    auto stream = connection.all_book_tickers_stream(params);
    stream.on_message([](const auto& event) { std::cout << common::to_json(event) << "\n"; });
    std::this_thread::sleep_for(std::chrono::seconds(10));
    stream.unsubscribe();
    connection.disconnect();
}
```
