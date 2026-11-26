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
        const ExecutionRulesParams params{};
        const auto response = connection.execution_rules(params);
        common::Logger::info("execution_rules() rate limits: " +
                             common::to_json(response.rate_limits()));
        common::Logger::info("execution_rules() response: " + common::to_json(response.data()));
        connection.disconnect();
    } catch (const std::exception& e) {
        common::Logger::error(std::string("execution_rules() error: ") + e.what());
        return 1;
    }
}
