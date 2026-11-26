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
    if (const char* secret = std::getenv("API_SECRET")) {
        cfg.api_secret = secret;
    }
    if (!cfg.api_key || !cfg.api_secret) {
        common::Logger::error("Set API_KEY and API_SECRET");
        return 1;
    }

    try {
        const auto client = margin_trading::MarginTradingRestApi::production(std::move(cfg));
        const QueryCrossMarginFeeDataParams params{};
        const auto response = client.query_cross_margin_fee_data(params);
        common::Logger::info("query_cross_margin_fee_data() rate limits: " +
                             common::to_json(response.rate_limits()));
        common::Logger::info("query_cross_margin_fee_data() response: " +
                             common::to_json(response.data()));
    } catch (const std::exception& e) {
        common::Logger::error(std::string("query_cross_margin_fee_data() error: ") + e.what());
        return 1;
    }
}
