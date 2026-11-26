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
#include <binance/sub_account/rest_api.hpp>

int main() {
    using namespace binance;
    using namespace binance::sub_account::rest_api;

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
        const auto client = sub_account::SubAccountRestApi::production(std::move(cfg));
        const AddIpRestrictionForSubAccountApiKeyParams params{
            .email = "123@test.com",
            .sub_account_api_key = "k5V49ldtn4tszj6W3hystegdfvmGbqDzjmkCtpTvC0G74WhK7yd4rfCTo4lShf",
            .status = 1};
        const auto response = client.add_ip_restriction_for_sub_account_api_key(params);
        common::Logger::info("add_ip_restriction_for_sub_account_api_key() rate limits: " +
                             common::to_json(response.rate_limits()));
        common::Logger::info("add_ip_restriction_for_sub_account_api_key() response: " +
                             common::to_json(response.data()));
    } catch (const std::exception& e) {
        common::Logger::error(std::string("add_ip_restriction_for_sub_account_api_key() error: ") +
                              e.what());
        return 1;
    }
}
