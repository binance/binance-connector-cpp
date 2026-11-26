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
        // This operation trades: the example runs on the testnet, so that no real order is
        // placed. Use testnet API keys (they are separate from the production ones).
        const auto client =
            derivatives_trading_portfolio_margin::DerivativesTradingPortfolioMarginRestApi::testnet(
                std::move(cfg));
        const QueryUmModifyOrderHistoryParams params{.symbol = "BTCUSDT"};
        const auto response = client.query_um_modify_order_history(params);
        common::Logger::info("query_um_modify_order_history() rate limits: " +
                             common::to_json(response.rate_limits()));
        common::Logger::info("query_um_modify_order_history() response: " +
                             common::to_json(response.data()));
    } catch (const std::exception& e) {
        common::Logger::error(std::string("query_um_modify_order_history() error: ") + e.what());
        return 1;
    }
}
