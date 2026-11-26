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

#include <binance/derivatives_trading_options/export.hpp>

namespace binance::derivatives_trading_options::rest_api {

struct RecentBlockTradesListResponseInner {
    /// id
    std::optional<std::int64_t> id;
    /// trade Id
    std::optional<std::int64_t> trade_id;
    /// symbol
    std::optional<std::string> symbol;
    /// price
    std::optional<std::string> price;
    /// qty
    std::optional<std::string> qty;
    /// quote Qty
    std::optional<std::string> quote_qty;
    /// side
    std::optional<std::int64_t> side;
    /// time
    std::optional<std::int64_t> time;

    bool operator==(const RecentBlockTradesListResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT RecentBlockTradesListResponseInner
tag_invoke(boost::json::value_to_tag<RecentBlockTradesListResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const RecentBlockTradesListResponseInner& v);

} // namespace binance::derivatives_trading_options::rest_api
