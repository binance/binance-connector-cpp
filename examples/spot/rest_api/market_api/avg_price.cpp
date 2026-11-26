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
#include <binance/spot/rest_api.hpp>

int main() {
    using namespace binance;
    using namespace binance::spot::rest_api;

    common::RestApiConfig cfg;
    if (const char* key = std::getenv("API_KEY")) {
        cfg.api_key = key;
    }

    try {
        const auto client = spot::SpotRestApi::production(std::move(cfg));
        const AvgPriceParams params{.symbol = "BNBUSDT"};
        const auto response = client.avg_price(params);
        common::Logger::info("avg_price() rate limits: " + common::to_json(response.rate_limits()));
        common::Logger::info("avg_price() response: " + common::to_json(response.data()));
    } catch (const std::exception& e) {
        common::Logger::error(std::string("avg_price() error: ") + e.what());
        return 1;
    }
}
