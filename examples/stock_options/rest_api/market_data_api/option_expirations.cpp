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
#include <binance/stock_options/rest_api.hpp>

int main() {
    using namespace binance;
    using namespace binance::stock_options::rest_api;

    common::RestApiConfig cfg;
    if (const char* key = std::getenv("API_KEY")) {
        cfg.api_key = key;
    }

    try {
        const auto client = stock_options::StockOptionsRestApi::production(std::move(cfg));
        const OptionExpirationsParams params{.underlying_symbol = "NVDA"};
        const auto response = client.option_expirations(params);
        common::Logger::info("option_expirations() rate limits: " +
                             common::to_json(response.rate_limits()));
        common::Logger::info("option_expirations() response: " + common::to_json(response.data()));
    } catch (const std::exception& e) {
        common::Logger::error(std::string("option_expirations() error: ") + e.what());
        return 1;
    }
}
