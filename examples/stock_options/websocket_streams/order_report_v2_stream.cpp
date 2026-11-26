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
#include <binance/stock_options/websocket_streams.hpp>

int main() {
    using namespace binance;
    using namespace binance::stock_options::websocket_streams;

    try {
        auto client = stock_options::StockOptionsWebsocketStreams::production({});
        auto connection = client.connect();
        const OrderReportV2StreamParams params{.listen_key =
                                                   "3f9a1c2e-7b4d-4e8a-9c61-0d2f5b7e8a13"};
        auto stream = connection.order_report_v2_stream(params);
        stream.on_message([](const auto& event) { common::Logger::info(common::to_json(event)); });
        std::this_thread::sleep_for(std::chrono::seconds(20));
        stream.unsubscribe();
        connection.disconnect();
    } catch (const std::exception& e) {
        common::Logger::error(std::string("order_report_v2_stream() error: ") + e.what());
        return 1;
    }
}
