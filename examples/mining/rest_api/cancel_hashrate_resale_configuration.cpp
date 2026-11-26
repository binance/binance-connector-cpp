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
#include <binance/mining/rest_api.hpp>

int main() {
    using namespace binance;
    using namespace binance::mining::rest_api;

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
        const auto client = mining::MiningRestApi::production(std::move(cfg));
        const CancelHashrateResaleConfigurationParams params{.config_id = 168, .user_name = "test"};
        const auto response = client.cancel_hashrate_resale_configuration(params);
        common::Logger::info("cancel_hashrate_resale_configuration() rate limits: " +
                             common::to_json(response.rate_limits()));
        common::Logger::info("cancel_hashrate_resale_configuration() response: " +
                             common::to_json(response.data()));
    } catch (const std::exception& e) {
        common::Logger::error(std::string("cancel_hashrate_resale_configuration() error: ") +
                              e.what());
        return 1;
    }
}
