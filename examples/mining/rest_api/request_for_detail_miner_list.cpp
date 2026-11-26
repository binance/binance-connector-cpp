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
        const RequestForDetailMinerListParams params{
            .algo = "sha256", .user_name = "test", .worker_name = "bhdc1.16A10404B"};
        const auto response = client.request_for_detail_miner_list(params);
        common::Logger::info("request_for_detail_miner_list() rate limits: " +
                             common::to_json(response.rate_limits()));
        common::Logger::info("request_for_detail_miner_list() response: " +
                             common::to_json(response.data()));
    } catch (const std::exception& e) {
        common::Logger::error(std::string("request_for_detail_miner_list() error: ") + e.what());
        return 1;
    }
}
