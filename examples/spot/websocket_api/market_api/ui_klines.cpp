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
        const UiKlinesParams params{.symbol = "BNBUSDT",
                                    .interval = UiKlinesIntervalEnum::Interval1s};
        const auto response = connection.ui_klines(params);
        common::Logger::info("ui_klines() rate limits: " + common::to_json(response.rate_limits()));
        common::Logger::info("ui_klines() response: " + common::to_json(response.data()));
        connection.disconnect();
    } catch (const std::exception& e) {
        common::Logger::error(std::string("ui_klines() error: ") + e.what());
        return 1;
    }
}
