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
    if (const char* secret = std::getenv("API_SECRET")) {
        cfg.api_secret = secret;
    }
    if (!cfg.api_key || !cfg.api_secret) {
        common::Logger::error("Set API_KEY and API_SECRET");
        return 1;
    }

    try {
        // This operation trades: the example runs on the demo environment, so that no real order is
        // placed. Use demo API keys (they are separate from the production ones).
        auto client = spot::SpotWebsocketApi::demo(std::move(cfg));
        auto connection = client.connect();
        const OrderListPlaceOpocoParams params{
            .symbol = "BNBUSDT",
            .working_type = OrderListPlaceOpocoWorkingTypeEnum::Limit,
            .working_side = OrderListPlaceOpocoWorkingSideEnum::Buy,
            .working_price = common::Decimal("1"),
            .working_quantity = common::Decimal("1"),
            .pending_side = OrderListPlaceOpocoPendingSideEnum::Buy,
            .pending_above_type = OrderListPlaceOpocoPendingAboveTypeEnum::StopLossLimit};
        const auto response = connection.order_list_place_opoco(params);
        common::Logger::info("order_list_place_opoco() rate limits: " +
                             common::to_json(response.rate_limits()));
        common::Logger::info("order_list_place_opoco() response: " +
                             common::to_json(response.data()));
        connection.disconnect();
    } catch (const std::exception& e) {
        common::Logger::error(std::string("order_list_place_opoco() error: ") + e.what());
        return 1;
    }
}
