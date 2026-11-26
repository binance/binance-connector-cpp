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
        const LongShortRatioParams params{.pair = "pair_example",
                                          .period = LongShortRatioPeriodEnum::Period5m};
        const auto response = client.long_short_ratio(params);
        common::Logger::info("long_short_ratio() rate limits: " +
                             common::to_json(response.rate_limits()));
        common::Logger::info("long_short_ratio() response: " + common::to_json(response.data()));
    } catch (const std::exception& e) {
        common::Logger::error(std::string("long_short_ratio() error: ") + e.what());
        return 1;
    }
}
