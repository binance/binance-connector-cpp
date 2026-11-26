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
#include <binance/derivatives_trading_portfolio_margin_pro/rest_api.hpp>

int main() {
    using namespace binance;
    using namespace binance::derivatives_trading_portfolio_margin_pro::rest_api;

    common::RestApiConfig cfg;
    if (const char* key = std::getenv("API_KEY")) {
        cfg.api_key = key;
    }

    try {
        const auto client = derivatives_trading_portfolio_margin_pro::
            DerivativesTradingPortfolioMarginProRestApi::production(std::move(cfg));
        const auto response = client.get_portfolio_margin_tiered_collateral_rates();
        common::Logger::info("get_portfolio_margin_tiered_collateral_rates() rate limits: " +
                             common::to_json(response.rate_limits()));
        common::Logger::info("get_portfolio_margin_tiered_collateral_rates() response: " +
                             common::to_json(response.data()));
    } catch (const std::exception& e) {
        common::Logger::error(
            std::string("get_portfolio_margin_tiered_collateral_rates() error: ") + e.what());
        return 1;
    }
}
