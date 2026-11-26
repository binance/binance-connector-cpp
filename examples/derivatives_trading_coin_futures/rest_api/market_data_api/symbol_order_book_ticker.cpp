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
#include <binance/derivatives_trading_coin_futures/rest_api.hpp>

int main() {
    using namespace binance;
    using namespace binance::derivatives_trading_coin_futures::rest_api;

    common::RestApiConfig cfg;
    if (const char* key = std::getenv("API_KEY")) {
        cfg.api_key = key;
    }

    try {
        const auto client =
            derivatives_trading_coin_futures::DerivativesTradingCoinFuturesRestApi::production(
                std::move(cfg));
        const SymbolOrderBookTickerParams params{};
        const auto response = client.symbol_order_book_ticker(params);
        common::Logger::info("symbol_order_book_ticker() rate limits: " +
                             common::to_json(response.rate_limits()));
        common::Logger::info("symbol_order_book_ticker() response: " +
                             common::to_json(response.data()));
    } catch (const std::exception& e) {
        common::Logger::error(std::string("symbol_order_book_ticker() error: ") + e.what());
        return 1;
    }
}
