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
#include <binance/derivatives_trading_usds_futures/rest_api.hpp>

int main() {
    using namespace binance;
    using namespace binance::derivatives_trading_usds_futures::rest_api;

    common::RestApiConfig cfg;
    if (const char* key = std::getenv("API_KEY")) {
        cfg.api_key = key;
    }
    if (const char* secret = std::getenv("API_SECRET")) {
        cfg.api_secret = secret;
    }
    if (!cfg.api_key || !cfg.api_secret) {
        common::Logger::error("Set API_KEY and API_SECRET");
        return 1;
    }

    try {
        const auto client =
            derivatives_trading_usds_futures::DerivativesTradingUsdsFuturesRestApi::production(
                std::move(cfg));
        const NotionalAndLeverageBracketsParams params{};
        const auto response = client.notional_and_leverage_brackets(params);
        common::Logger::info("notional_and_leverage_brackets() rate limits: " +
                             common::to_json(response.rate_limits()));
        common::Logger::info("notional_and_leverage_brackets() response: " +
                             common::to_json(response.data()));
    } catch (const std::exception& e) {
        common::Logger::error(std::string("notional_and_leverage_brackets() error: ") + e.what());
        return 1;
    }
}
