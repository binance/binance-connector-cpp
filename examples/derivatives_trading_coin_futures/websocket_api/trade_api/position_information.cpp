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
#include <binance/derivatives_trading_coin_futures/websocket_api.hpp>

int main() {
    using namespace binance;
    using namespace binance::derivatives_trading_coin_futures::websocket_api;

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
            derivatives_trading_coin_futures::DerivativesTradingCoinFuturesWebsocketApi::production(
                std::move(cfg));
        auto connection = client.connect();
        const PositionInformationParams params{};
        const auto response = connection.position_information(params);
        common::Logger::info("position_information() rate limits: " +
                             common::to_json(response.rate_limits()));
        common::Logger::info("position_information() response: " +
                             common::to_json(response.data()));
        connection.disconnect();
    } catch (const std::exception& e) {
        common::Logger::error(std::string("position_information() error: ") + e.what());
        return 1;
    }
}
