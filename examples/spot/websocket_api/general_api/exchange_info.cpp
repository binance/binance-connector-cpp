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
#include <binance/spot/websocket_api.hpp>

int main() {
    using namespace binance;
    using namespace binance::spot::websocket_api;

    common::WebsocketApiConfig cfg;
    if (const char* key = std::getenv("API_KEY")) {
        cfg.api_key = key;
    }

    try {
        auto client = spot::SpotWebsocketApi::production(std::move(cfg));
        auto connection = client.connect();
        const ExchangeInfoParams params{};
        const auto response = connection.exchange_info(params);
        common::Logger::info("exchange_info() rate limits: " +
                             common::to_json(response.rate_limits()));
        common::Logger::info("exchange_info() response: " + common::to_json(response.data()));
        connection.disconnect();
    } catch (const std::exception& e) {
        common::Logger::error(std::string("exchange_info() error: ") + e.what());
        return 1;
    }
}
