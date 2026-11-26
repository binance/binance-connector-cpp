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
        const auto response =
            client.query_liability_coin_leverage_bracket_in_cross_margin_pro_mode();
        common::Logger::info(
            "query_liability_coin_leverage_bracket_in_cross_margin_pro_mode() rate limits: " +
            common::to_json(response.rate_limits()));
        common::Logger::info(
            "query_liability_coin_leverage_bracket_in_cross_margin_pro_mode() response: " +
            common::to_json(response.data()));
    } catch (const std::exception& e) {
        common::Logger::error(
            std::string(
                "query_liability_coin_leverage_bracket_in_cross_margin_pro_mode() error: ") +
            e.what());
        return 1;
    }
}
