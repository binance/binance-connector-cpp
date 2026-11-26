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
#include <binance/dual_investment/rest_api.hpp>

int main() {
    using namespace binance;
    using namespace binance::dual_investment::rest_api;

    common::RestApiConfig cfg;
    if (const char* key = std::getenv("API_KEY")) {
        cfg.api_key = key;
    }

    try {
        const auto client = dual_investment::DualInvestmentRestApi::production(std::move(cfg));
        const GetDualInvestmentProductListParams params{
            .option_type = GetDualInvestmentProductListOptionTypeEnum::Call,
            .exercised_coin = "USDT",
            .invest_coin = "BNB"};
        const auto response = client.get_dual_investment_product_list(params);
        common::Logger::info("get_dual_investment_product_list() rate limits: " +
                             common::to_json(response.rate_limits()));
        common::Logger::info("get_dual_investment_product_list() response: " +
                             common::to_json(response.data()));
    } catch (const std::exception& e) {
        common::Logger::error(std::string("get_dual_investment_product_list() error: ") + e.what());
        return 1;
    }
}
