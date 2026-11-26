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
        // This operation trades: the example runs on the demo environment, so that no real order is
        // placed. Use demo API keys (they are separate from the production ones).
        const auto client =
            derivatives_trading_usds_futures::DerivativesTradingUsdsFuturesRestApi::demo(
                std::move(cfg));
        const ChangeInitialLeverageParams params{.symbol = "BTCUSDT", .leverage = 1};
        const auto response = client.change_initial_leverage(params);
        common::Logger::info("change_initial_leverage() rate limits: " +
                             common::to_json(response.rate_limits()));
        common::Logger::info("change_initial_leverage() response: " +
                             common::to_json(response.data()));
    } catch (const std::exception& e) {
        common::Logger::error(std::string("change_initial_leverage() error: ") + e.what());
        return 1;
    }
}
