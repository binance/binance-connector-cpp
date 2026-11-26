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

#include <binance/cms/websocket_streams.hpp>
#include <binance/common/json.hpp>
#include <binance/common/logger.hpp>

int main() {
    using namespace binance;
    using namespace binance::cms::websocket_streams;

    common::WebsocketStreamsConfig cfg;
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
        auto client = cms::CmsWebsocketStreams::production(std::move(cfg));
        auto connection = client.connect();
        auto stream = connection.com_announcement_en();
        stream.on_message([](const auto& event) { common::Logger::info(common::to_json(event)); });
        std::this_thread::sleep_for(std::chrono::seconds(20));
        stream.unsubscribe();
        connection.disconnect();
    } catch (const std::exception& e) {
        common::Logger::error(std::string("com_announcement_en() error: ") + e.what());
        return 1;
    }
}
