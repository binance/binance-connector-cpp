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
#include <binance/margin_trading/rest_api.hpp>

int main() {
    using namespace binance;
    using namespace binance::margin_trading::rest_api;

    common::RestApiConfig cfg;
    if (const char* key = std::getenv("API_KEY")) {
        cfg.api_key = key;
    }

    try {
        const auto client = margin_trading::MarginTradingRestApi::production(std::move(cfg));
        const GetListScheduleParams params{};
        const auto response = client.get_list_schedule(params);
        common::Logger::info("get_list_schedule() rate limits: " +
                             common::to_json(response.rate_limits()));
        common::Logger::info("get_list_schedule() response: " + common::to_json(response.data()));
    } catch (const std::exception& e) {
        common::Logger::error(std::string("get_list_schedule() error: ") + e.what());
        return 1;
    }
}
