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
#include <binance/crypto_loan/rest_api.hpp>

int main() {
    using namespace binance;
    using namespace binance::crypto_loan::rest_api;

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
        const auto client = crypto_loan::CryptoLoanRestApi::production(std::move(cfg));
        const CheckCollateralRepayRateParams params{.loan_coin = "BUSD", .collateral_coin = "BNB"};
        const auto response = client.check_collateral_repay_rate(params);
        common::Logger::info("check_collateral_repay_rate() rate limits: " +
                             common::to_json(response.rate_limits()));
        common::Logger::info("check_collateral_repay_rate() response: " +
                             common::to_json(response.data()));
    } catch (const std::exception& e) {
        common::Logger::error(std::string("check_collateral_repay_rate() error: ") + e.what());
        return 1;
    }
}
