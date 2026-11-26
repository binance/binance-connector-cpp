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
#include <binance/stocks/rest_api.hpp>

int main() {
    using namespace binance;
    using namespace binance::stocks::rest_api;

    common::RestApiConfig cfg;
    if (const char* key = std::getenv("API_KEY")) {
        cfg.api_key = key;
    }

    try {
        const auto client = stocks::StocksRestApi::production(std::move(cfg));
        const ExchangeInfoParams params{};
        const auto response = client.exchange_info(params);
        common::Logger::info("exchange_info() rate limits: " +
                             common::to_json(response.rate_limits()));
        common::Logger::info("exchange_info() response: " + common::to_json(response.data()));
    } catch (const std::exception& e) {
        common::Logger::error(std::string("exchange_info() error: ") + e.what());
        return 1;
    }
}
