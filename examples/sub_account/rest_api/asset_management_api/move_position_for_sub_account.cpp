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
        const MovePositionForSubAccountParams params{
            .from_user_email = "testFrom@google.com",
            .to_user_email = "testTo@google.com",
            .product_type = MovePositionForSubAccountProductTypeEnum::Um,
            .order_args = std::vector<MovePositionForSubAccountOrderArgsParameterInner>{}};
        const auto response = client.move_position_for_sub_account(params);
        common::Logger::info("move_position_for_sub_account() rate limits: " +
                             common::to_json(response.rate_limits()));
        common::Logger::info("move_position_for_sub_account() response: " +
                             common::to_json(response.data()));
    } catch (const std::exception& e) {
        common::Logger::error(std::string("move_position_for_sub_account() error: ") + e.what());
        return 1;
    }
}
