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

#include <binance/c2c/rest_api.hpp>
#include <binance/common/json.hpp>
#include <binance/common/logger.hpp>

int main() {
    using namespace binance;
    using namespace binance::c2c::rest_api;

    common::RestApiConfig cfg;
    if (const char* key = std::getenv("API_KEY")) {
        cfg.api_key = key;
    }

    try {
        const auto client = c2c::C2CRestApi::production(std::move(cfg));
        const GetC2CTradeHistoryParams params{};
        const auto response = client.get_c2c_trade_history(params);
        common::Logger::info("get_c2c_trade_history() rate limits: " +
                             common::to_json(response.rate_limits()));
        common::Logger::info("get_c2c_trade_history() response: " +
                             common::to_json(response.data()));
    } catch (const std::exception& e) {
        common::Logger::error(std::string("get_c2c_trade_history() error: ") + e.what());
        return 1;
    }
}
