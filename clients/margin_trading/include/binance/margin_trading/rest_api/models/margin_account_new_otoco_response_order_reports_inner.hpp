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

#include <binance/margin_trading/export.hpp>

namespace binance::margin_trading::rest_api {

struct MarginAccountNewOtocoResponseOrderReportsInner {
    /// symbol.
    std::optional<std::string> symbol;
    /// order Id.
    std::optional<std::int64_t> order_id;
    /// order List Id.
    std::optional<std::int64_t> order_list_id;
    /// client Order Id.
    std::optional<std::string> client_order_id;
    /// transact Time.
    std::optional<std::int64_t> transact_time;
    /// price.
    std::optional<std::string> price;
    /// orig Qty.
    std::optional<std::string> orig_qty;
    /// executed Qty.
    std::optional<std::string> executed_qty;
    /// cummulative Quote Qty.
    std::optional<std::string> cummulative_quote_qty;
    /// status.
    std::optional<std::string> status;
    /// time In Force.
    std::optional<std::string> time_in_force;
    /// type.
    std::optional<std::string> type;
    /// side.
    std::optional<std::string> side;
    /// self Trade Prevention Mode.
    std::optional<std::string> self_trade_prevention_mode;
    /// stop Price.
    std::optional<std::string> stop_price;

    bool
    operator==(const MarginAccountNewOtocoResponseOrderReportsInner& /*other*/) const = default;
};

BINANCE_MARGIN_TRADING_EXPORT MarginAccountNewOtocoResponseOrderReportsInner
tag_invoke(boost::json::value_to_tag<MarginAccountNewOtocoResponseOrderReportsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const MarginAccountNewOtocoResponseOrderReportsInner& v);

} // namespace binance::margin_trading::rest_api
