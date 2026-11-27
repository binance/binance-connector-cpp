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
        // This operation trades: the example runs on the testnet, so that no real order is
        // placed. Use testnet API keys (they are separate from the production ones).
        auto client =
            derivatives_trading_coin_futures::DerivativesTradingCoinFuturesWebsocketApi::testnet(
                std::move(cfg));
        auto connection = client.connect();
        const NewAlgoOrderParams params{.algo_type = NewAlgoOrderAlgoTypeEnum::Conditional,
                                        .symbol = "BTCUSD_PERP",
                                        .side = NewAlgoOrderSideEnum::Buy,
                                        .type = NewAlgoOrderTypeEnum::StopMarket};
        const auto response = connection.new_algo_order(params);
        common::Logger::info("new_algo_order() rate limits: " +
                             common::to_json(response.rate_limits()));
        common::Logger::info("new_algo_order() response: " + common::to_json(response.data()));
        connection.disconnect();
    } catch (const std::exception& e) {
        common::Logger::error(std::string("new_algo_order() error: ") + e.what());
        return 1;
    }
}
