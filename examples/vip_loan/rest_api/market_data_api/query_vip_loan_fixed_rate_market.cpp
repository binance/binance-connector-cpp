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
        const QueryVIPLoanFixedRateMarketParams params{.loan_coin = "USDT"};
        const auto response = client.query_vip_loan_fixed_rate_market(params);
        common::Logger::info("query_vip_loan_fixed_rate_market() rate limits: " +
                             common::to_json(response.rate_limits()));
        common::Logger::info("query_vip_loan_fixed_rate_market() response: " +
                             common::to_json(response.data()));
    } catch (const std::exception& e) {
        common::Logger::error(std::string("query_vip_loan_fixed_rate_market() error: ") + e.what());
        return 1;
    }
}
