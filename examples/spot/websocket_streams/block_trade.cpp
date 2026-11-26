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
#include <binance/spot/websocket_streams.hpp>

int main() {
    using namespace binance;
    using namespace binance::spot::websocket_streams;

    try {
        auto client = spot::SpotWebsocketStreams::production({});
        auto connection = client.connect();
        const BlockTradeParams params{.symbol = "bnbusdt"};
        auto stream = connection.block_trade(params);
        stream.on_message([](const auto& event) { common::Logger::info(common::to_json(event)); });
        std::this_thread::sleep_for(std::chrono::seconds(20));
        stream.unsubscribe();
        connection.disconnect();
    } catch (const std::exception& e) {
        common::Logger::error(std::string("block_trade() error: ") + e.what());
        return 1;
    }
}
