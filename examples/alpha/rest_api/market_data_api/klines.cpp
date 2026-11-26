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

#include <binance/alpha/rest_api.hpp>
#include <binance/common/json.hpp>
#include <binance/common/logger.hpp>

int main() {
    using namespace binance;
    using namespace binance::alpha::rest_api;

    common::RestApiConfig cfg;
    if (const char* key = std::getenv("API_KEY")) {
        cfg.api_key = key;
    }

    try {
        const auto client = alpha::AlphaRestApi::production(std::move(cfg));
        const KlinesParams params{.symbol = "ALPHA_175USDT",
                                  .interval = KlinesIntervalEnum::Interval1s};
        const auto response = client.klines(params);
        common::Logger::info("klines() rate limits: " + common::to_json(response.rate_limits()));
        common::Logger::info("klines() response: " + common::to_json(response.data()));
    } catch (const std::exception& e) {
        common::Logger::error(std::string("klines() error: ") + e.what());
        return 1;
    }
}
