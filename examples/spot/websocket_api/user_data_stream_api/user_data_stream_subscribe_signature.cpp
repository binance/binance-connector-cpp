//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <chrono>
#include <cstdlib>
#include <exception>
#include <string>
#include <thread>
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
        auto client = spot::SpotWebsocketApi::production(std::move(cfg));
        auto connection = client.connect();
        const UserDataStreamSubscribeSignatureParams params{};
        auto [response, stream] = connection.user_data_stream_subscribe_signature(params);
        common::Logger::info("user_data_stream_subscribe_signature() rate limits: " +
                             common::to_json(response.rate_limits()));
        common::Logger::info("user_data_stream_subscribe_signature() response: " +
                             common::to_json(response.data()));
        stream.on_message([](const auto& event) {
            common::Logger::info("user_data_stream_subscribe_signature() stream data: " +
                                 common::to_json(event));
        });
        std::this_thread::sleep_for(std::chrono::seconds(20));
        stream.unsubscribe();
        connection.disconnect();
    } catch (const std::exception& e) {
        common::Logger::error(std::string("user_data_stream_subscribe_signature() error: ") +
                              e.what());
        return 1;
    }
}
