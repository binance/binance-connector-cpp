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
#include <binance/derivatives_trading_usds_futures/websocket_api.hpp>

int main() {
    using namespace binance;
    using namespace binance::derivatives_trading_usds_futures::websocket_api;

    common::WebsocketApiConfig cfg;
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
        auto client =
            derivatives_trading_usds_futures::DerivativesTradingUsdsFuturesWebsocketApi::production(
                std::move(cfg));
        auto connection = client.connect();
        const AccountInformationV2Params params{};
        const auto response = connection.account_information_v2(params);
        common::Logger::info("account_information_v2() rate limits: " +
                             common::to_json(response.rate_limits()));
        common::Logger::info("account_information_v2() response: " +
                             common::to_json(response.data()));
        connection.disconnect();
    } catch (const std::exception& e) {
        common::Logger::error(std::string("account_information_v2() error: ") + e.what());
        return 1;
    }
}
