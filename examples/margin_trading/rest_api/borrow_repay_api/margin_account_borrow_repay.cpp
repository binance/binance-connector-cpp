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
#include <binance/margin_trading/rest_api.hpp>

int main() {
    using namespace binance;
    using namespace binance::margin_trading::rest_api;

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
        const auto client = margin_trading::MarginTradingRestApi::production(std::move(cfg));
        const MarginAccountBorrowRepayParams params{
            .asset = "USDT",
            .is_isolated = MarginAccountBorrowRepayIsIsolatedEnum::True_,
            .amount = "1.0",
            .type = MarginAccountBorrowRepayTypeEnum::Borrow};
        const auto response = client.margin_account_borrow_repay(params);
        common::Logger::info("margin_account_borrow_repay() rate limits: " +
                             common::to_json(response.rate_limits()));
        common::Logger::info("margin_account_borrow_repay() response: " +
                             common::to_json(response.data()));
    } catch (const std::exception& e) {
        common::Logger::error(std::string("margin_account_borrow_repay() error: ") + e.what());
        return 1;
    }
}
