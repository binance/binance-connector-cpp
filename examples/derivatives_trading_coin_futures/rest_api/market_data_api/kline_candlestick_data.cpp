//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <cstdlib>
#include <exception>
#include <string>
#include <utility>

#include <binance/common/json.hpp>
#include <binance/common/logger.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api.hpp>

int main() {
    using namespace binance;
    using namespace binance::derivatives_trading_coin_futures::rest_api;

    common::RestApiConfig cfg;
    if (const char* key = std::getenv("API_KEY")) {
        cfg.api_key = key;
    }

    try {
        const auto client =
            derivatives_trading_coin_futures::DerivativesTradingCoinFuturesRestApi::production(
                std::move(cfg));
        const KlineCandlestickDataParams params{
            .symbol = "BTCUSD", .interval = KlineCandlestickDataIntervalEnum::Interval1m};
        const auto response = client.kline_candlestick_data(params);
        common::Logger::info("kline_candlestick_data() rate limits: " +
                             common::to_json(response.rate_limits()));
        common::Logger::info("kline_candlestick_data() response: " +
                             common::to_json(response.data()));
    } catch (const std::exception& e) {
        common::Logger::error(std::string("kline_candlestick_data() error: ") + e.what());
        return 1;
    }
}
