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
#include <binance/derivatives_trading_usds_futures/websocket_streams.hpp>

int main() {
    using namespace binance;
    using namespace binance::derivatives_trading_usds_futures::websocket_streams;

    try {
        auto client = derivatives_trading_usds_futures::
            DerivativesTradingUsdsFuturesWebsocketStreams::production({});
        auto connection = client.connect();
        const ContinuousContractKlineCandlestickStreamsParams params{
            .pair = "btcusdt",
            .contract_type = ContinuousContractKlineCandlestickStreamsContractTypeEnum::Perpetual,
            .interval = ContinuousContractKlineCandlestickStreamsIntervalEnum::Interval1s};
        auto stream = connection.continuous_contract_kline_candlestick_streams(params);
        stream.on_message([](const auto& event) { common::Logger::info(common::to_json(event)); });
        std::this_thread::sleep_for(std::chrono::seconds(20));
        stream.unsubscribe();
        connection.disconnect();
    } catch (const std::exception& e) {
        common::Logger::error(
            std::string("continuous_contract_kline_candlestick_streams() error: ") + e.what());
        return 1;
    }
}
