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

#include <binance/alpha/websocket_streams.hpp>
#include <binance/common/json.hpp>
#include <binance/common/logger.hpp>

int main() {
    using namespace binance;
    using namespace binance::alpha::websocket_streams;

    try {
        auto client = alpha::AlphaWebsocketStreams::production({});
        auto connection = client.connect();
        const TradeStreamParams params{.symbol = "alpha_116usdt"};
        auto stream = connection.trade_stream(params);
        stream.on_message([](const auto& event) { common::Logger::info(common::to_json(event)); });
        std::this_thread::sleep_for(std::chrono::seconds(20));
        stream.unsubscribe();
        connection.disconnect();
    } catch (const std::exception& e) {
        common::Logger::error(std::string("trade_stream() error: ") + e.what());
        return 1;
    }
}
