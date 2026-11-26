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
        const SymbolOrderBookTickerParams params{};
        const auto response = connection.symbol_order_book_ticker(params);
        common::Logger::info("symbol_order_book_ticker() rate limits: " +
                             common::to_json(response.rate_limits()));
        common::Logger::info("symbol_order_book_ticker() response: " +
                             common::to_json(response.data()));
        connection.disconnect();
    } catch (const std::exception& e) {
        common::Logger::error(std::string("symbol_order_book_ticker() error: ") + e.what());
        return 1;
    }
}
