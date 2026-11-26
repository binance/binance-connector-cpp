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
#include <binance/vip_loan/rest_api.hpp>

int main() {
    using namespace binance;
    using namespace binance::vip_loan::rest_api;

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
        const auto client = vip_loan::VipLoanRestApi::production(std::move(cfg));
        const VipLoanFixedRateBorrowParams params{.supply_request = "1212:0.12:100;3434:0.13:50",
                                                  .borrow_coin = "BUSD",
                                                  .loan_term = 30,
                                                  .borrow_uid = 12345678,
                                                  .collateral_coin = "BNB,BNB-Earn,ETH,BTC",
                                                  .collateral_account_id = "12345,67890,13579"};
        const auto response = client.vip_loan_fixed_rate_borrow(params);
        common::Logger::info("vip_loan_fixed_rate_borrow() rate limits: " +
                             common::to_json(response.rate_limits()));
        common::Logger::info("vip_loan_fixed_rate_borrow() response: " +
                             common::to_json(response.data()));
    } catch (const std::exception& e) {
        common::Logger::error(std::string("vip_loan_fixed_rate_borrow() error: ") + e.what());
        return 1;
    }
}
