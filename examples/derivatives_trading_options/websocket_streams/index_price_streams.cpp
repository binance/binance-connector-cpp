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
#include <binance/derivatives_trading_options/websocket_streams.hpp>

int main() {
    using namespace binance;
    using namespace binance::derivatives_trading_options::websocket_streams;

    try {
        auto client =
            derivatives_trading_options::DerivativesTradingOptionsWebsocketStreams::production({});
        auto connection = client.connect();
        const IndexPriceStreamsParams params{};
        auto stream = connection.index_price_streams(params);
        stream.on_message([](const auto& event) { common::Logger::info(common::to_json(event)); });
        std::this_thread::sleep_for(std::chrono::seconds(20));
        stream.unsubscribe();
        connection.disconnect();
    } catch (const std::exception& e) {
        common::Logger::error(std::string("index_price_streams() error: ") + e.what());
        return 1;
    }
}
