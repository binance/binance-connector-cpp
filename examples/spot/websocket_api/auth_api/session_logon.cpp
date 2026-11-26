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
    // Session logon only accepts Ed25519 keys: PRIVATE_KEY_PATH is the PEM file of the Ed25519
    // key registered as API_KEY.
    if (const char* path = std::getenv("PRIVATE_KEY_PATH")) {
        cfg.private_key = common::PrivateKey::from_file(path);
    }
    if (!cfg.api_key || !cfg.private_key) {
        common::Logger::error("Set API_KEY and PRIVATE_KEY_PATH (Ed25519 key)");
        return 1;
    }

    try {
        auto client = spot::SpotWebsocketApi::production(std::move(cfg));
        auto connection = client.connect();
        const SessionLogonParams params{};
        for (const auto& response : connection.session_logon(params)) {
            common::Logger::info("session_logon() rate limits: " +
                                 common::to_json(response.rate_limits()));
            common::Logger::info("session_logon() response: " + common::to_json(response.data()));
        }
        connection.disconnect();
    } catch (const std::exception& e) {
        common::Logger::error(std::string("session_logon() error: ") + e.what());
        return 1;
    }
}
