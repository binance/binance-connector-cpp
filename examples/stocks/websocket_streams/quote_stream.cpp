//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <chrono>
#include <exception>
#include <string>
#include <thread>

#include <binance/common/json.hpp>
#include <binance/common/logger.hpp>
#include <binance/stocks/websocket_streams.hpp>

int main() {
    using namespace binance;
    using namespace binance::stocks::websocket_streams;

    try {
        auto client = stocks::StocksWebsocketStreams::production({});
        auto connection = client.connect();
        const QuoteStreamParams params{.symbol = "AAPL"};
        auto stream = connection.quote_stream(params);
        stream.on_message([](const auto& event) { common::Logger::info(common::to_json(event)); });
        std::this_thread::sleep_for(std::chrono::seconds(20));
        stream.unsubscribe();
        connection.disconnect();
    } catch (const std::exception& e) {
        common::Logger::error(std::string("quote_stream() error: ") + e.what());
        return 1;
    }
}
