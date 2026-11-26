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

namespace binance::derivatives_trading_usds_futures::rest_api {

struct PlaceMultipleOrdersResponseInner {
    /// Client Order Id.
    std::optional<std::string> client_order_id;
    std::optional<std::string> cum_qty;
    /// Executed Qty.
    std::optional<std::string> executed_qty;
    /// Order Id.
    std::optional<std::int64_t> order_id;
    /// Orig Qty.
    std::optional<std::string> orig_qty;
    /// Price.
    std::optional<std::string> price;
    /// Reduce Only.
    std::optional<bool> reduce_only;
    /// Side.
    std::optional<std::string> side;
    /// Position Side.
    std::optional<std::string> position_side;
    /// Status.
    std::optional<std::string> status;
    std::optional<std::string> stop_price;
    /// Close Position.
    std::optional<bool> close_position;
    /// Symbol.
    std::optional<std::string> symbol;
    /// Time In Force.
    std::optional<std::string> time_in_force;
    /// Type.
    std::optional<std::string> type;
    /// Orig Type.
    std::optional<std::string> orig_type;
    /// Update Time.
    std::optional<std::int64_t> update_time;
    /// Working Type.
    std::optional<std::string> working_type;
    /// if conditional order trigger is protected
    std::optional<bool> price_protect;
    /// price match mode
    std::optional<std::string> price_match;
    /// self trading preventation mode
    std::optional<std::string> self_trade_prevention_mode;
    /// order pre-set auto cancel time for TIF GTD order
    std::optional<std::int64_t> good_till_date;
    std::optional<std::int64_t> code;
    std::optional<std::string> msg;

    bool operator==(const PlaceMultipleOrdersResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT PlaceMultipleOrdersResponseInner
tag_invoke(boost::json::value_to_tag<PlaceMultipleOrdersResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const PlaceMultipleOrdersResponseInner& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
