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
        const ApplyMmWithdrawParams params{.coin = "USDT", .network = "BEP20", .amount = "100.00"};
        const auto response = client.apply_mm_withdraw(params);
        common::Logger::info("apply_mm_withdraw() rate limits: " +
                             common::to_json(response.rate_limits()));
        common::Logger::info("apply_mm_withdraw() response: " + common::to_json(response.data()));
    } catch (const std::exception& e) {
        common::Logger::error(std::string("apply_mm_withdraw() error: ") + e.what());
        return 1;
    }
}
