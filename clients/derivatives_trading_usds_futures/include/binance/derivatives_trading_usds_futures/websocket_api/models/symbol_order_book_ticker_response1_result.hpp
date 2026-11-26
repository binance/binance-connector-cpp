//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <cstdint>
#include <optional>
#include <string>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/derivatives_trading_usds_futures/export.hpp>

namespace binance::derivatives_trading_usds_futures::websocket_api {

struct SymbolOrderBookTickerResponse1Result {
    std::optional<std::int64_t> last_update_id;
    std::optional<std::string> symbol;
    std::optional<std::string> bid_price;
    std::optional<std::string> bid_qty;
    std::optional<std::string> ask_price;
    std::optional<std::string> ask_qty;
    /// Transaction time
    std::optional<std::int64_t> time;

    bool operator==(const SymbolOrderBookTickerResponse1Result& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT SymbolOrderBookTickerResponse1Result
tag_invoke(boost::json::value_to_tag<SymbolOrderBookTickerResponse1Result> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const SymbolOrderBookTickerResponse1Result& v);

} // namespace binance::derivatives_trading_usds_futures::websocket_api
