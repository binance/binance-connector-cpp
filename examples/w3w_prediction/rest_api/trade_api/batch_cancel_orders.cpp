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
#include <binance/w3w_prediction/rest_api.hpp>

int main() {
    using namespace binance;
    using namespace binance::w3w_prediction::rest_api;

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
        const auto client = w3w_prediction::W3WPredictionRestApi::production(std::move(cfg));
        const BatchCancelOrdersParams params{.wallet_address =
                                                 "0x12e32db8817e292508c34111cbc4b23340df542c",
                                             .wallet_id = "5b5c1ec3be4e4416a5872b21c1ca5d20"};
        const auto response = client.batch_cancel_orders(params);
        common::Logger::info("batch_cancel_orders() rate limits: " +
                             common::to_json(response.rate_limits()));
        common::Logger::info("batch_cancel_orders() response: " + common::to_json(response.data()));
    } catch (const std::exception& e) {
        common::Logger::error(std::string("batch_cancel_orders() error: ") + e.what());
        return 1;
    }
}
