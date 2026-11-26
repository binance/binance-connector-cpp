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
        const HashrateResaleRequestParams params{.user_name = "test",
                                                 .algo = "sha256",
                                                 .end_date = 1770736694138,
                                                 .start_date = 1770736694138,
                                                 .to_pool_user = "S19pro",
                                                 .hash_rate = 100000000};
        const auto response = client.hashrate_resale_request(params);
        common::Logger::info("hashrate_resale_request() rate limits: " +
                             common::to_json(response.rate_limits()));
        common::Logger::info("hashrate_resale_request() response: " +
                             common::to_json(response.data()));
    } catch (const std::exception& e) {
        common::Logger::error(std::string("hashrate_resale_request() error: ") + e.what());
        return 1;
    }
}
