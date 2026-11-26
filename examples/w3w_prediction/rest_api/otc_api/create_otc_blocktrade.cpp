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
#include <binance/w3w_prediction/rest_api.hpp>

int main() {
    using namespace binance;
    using namespace binance::w3w_prediction::rest_api;

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
        const auto client = w3w_prediction::W3WPredictionRestApi::production(std::move(cfg));
        const CreateOtcBlocktradeParams params{
            .market_id = "123",
            .token_id =
                "71321045679252212594626385532706912750332728571942532289631379312455583992563",
            .side = CreateOtcBlocktradeSideEnum::Buy,
            .maker_amount = "600000000000000000000",
            .taker_amount = "1000000000000000000000",
            .price_per_share = "0.65",
            .expiration = 1790000000};
        const auto response = client.create_otc_blocktrade(params);
        common::Logger::info("create_otc_blocktrade() rate limits: " +
                             common::to_json(response.rate_limits()));
        common::Logger::info("create_otc_blocktrade() response: " +
                             common::to_json(response.data()));
    } catch (const std::exception& e) {
        common::Logger::error(std::string("create_otc_blocktrade() error: ") + e.what());
        return 1;
    }
}
