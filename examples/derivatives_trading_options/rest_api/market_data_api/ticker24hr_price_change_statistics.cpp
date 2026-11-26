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
#include <binance/derivatives_trading_options/rest_api.hpp>

int main() {
    using namespace binance;
    using namespace binance::derivatives_trading_options::rest_api;

    common::RestApiConfig cfg;
    if (const char* key = std::getenv("API_KEY")) {
        cfg.api_key = key;
    }

    try {
        const auto client =
            derivatives_trading_options::DerivativesTradingOptionsRestApi::production(
                std::move(cfg));
        const Ticker24hrPriceChangeStatisticsParams params{};
        const auto response = client.ticker24hr_price_change_statistics(params);
        common::Logger::info("ticker24hr_price_change_statistics() rate limits: " +
                             common::to_json(response.rate_limits()));
        common::Logger::info("ticker24hr_price_change_statistics() response: " +
                             common::to_json(response.data()));
    } catch (const std::exception& e) {
        common::Logger::error(std::string("ticker24hr_price_change_statistics() error: ") +
                              e.what());
        return 1;
    }
}
