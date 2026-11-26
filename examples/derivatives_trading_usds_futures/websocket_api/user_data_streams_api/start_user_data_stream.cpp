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

    try {
        auto client =
            derivatives_trading_usds_futures::DerivativesTradingUsdsFuturesWebsocketApi::production(
                std::move(cfg));
        auto connection = client.connect();
        const StartUserDataStreamParams params{};
        const auto response = connection.start_user_data_stream(params);
        common::Logger::info("start_user_data_stream() rate limits: " +
                             common::to_json(response.rate_limits()));
        common::Logger::info("start_user_data_stream() response: " +
                             common::to_json(response.data()));
        connection.disconnect();
    } catch (const std::exception& e) {
        common::Logger::error(std::string("start_user_data_stream() error: ") + e.what());
        return 1;
    }
}
