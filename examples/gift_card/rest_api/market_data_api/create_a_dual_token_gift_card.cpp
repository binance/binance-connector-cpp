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
#include <binance/gift_card/rest_api.hpp>

int main() {
    using namespace binance;
    using namespace binance::gift_card::rest_api;

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
        const auto client = gift_card::GiftCardRestApi::production(std::move(cfg));
        const CreateADualTokenGiftCardParams params{
            .base_token = "BUSD", .face_token = "BNB", .base_token_amount = common::Decimal("1")};
        const auto response = client.create_a_dual_token_gift_card(params);
        common::Logger::info("create_a_dual_token_gift_card() rate limits: " +
                             common::to_json(response.rate_limits()));
        common::Logger::info("create_a_dual_token_gift_card() response: " +
                             common::to_json(response.data()));
    } catch (const std::exception& e) {
        common::Logger::error(std::string("create_a_dual_token_gift_card() error: ") + e.what());
        return 1;
    }
}
