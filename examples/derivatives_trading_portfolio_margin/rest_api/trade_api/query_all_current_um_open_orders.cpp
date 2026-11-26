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
#include <binance/derivatives_trading_portfolio_margin/rest_api.hpp>

int main() {
    using namespace binance;
    using namespace binance::derivatives_trading_portfolio_margin::rest_api;

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
        const auto client = derivatives_trading_portfolio_margin::
            DerivativesTradingPortfolioMarginRestApi::production(std::move(cfg));
        const QueryAllCurrentUmOpenOrdersParams params{};
        const auto response = client.query_all_current_um_open_orders(params);
        common::Logger::info("query_all_current_um_open_orders() rate limits: " +
                             common::to_json(response.rate_limits()));
        common::Logger::info("query_all_current_um_open_orders() response: " +
                             common::to_json(response.data()));
    } catch (const std::exception& e) {
        common::Logger::error(std::string("query_all_current_um_open_orders() error: ") + e.what());
        return 1;
    }
}
