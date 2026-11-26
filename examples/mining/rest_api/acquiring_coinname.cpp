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

    try {
        const auto client = mining::MiningRestApi::production(std::move(cfg));
        const auto response = client.acquiring_coinname();
        common::Logger::info("acquiring_coinname() rate limits: " +
                             common::to_json(response.rate_limits()));
        common::Logger::info("acquiring_coinname() response: " + common::to_json(response.data()));
    } catch (const std::exception& e) {
        common::Logger::error(std::string("acquiring_coinname() error: ") + e.what());
        return 1;
    }
}
