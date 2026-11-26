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

struct CancelOrderResponse {
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
    /// please ignore when order type is TRAILING_STOP_MARKET
    std::optional<std::string> stop_price;
    /// if Close-All
    std::optional<bool> close_position;
    /// Symbol.
    std::optional<std::string> symbol;
    /// Time In Force.
    std::optional<std::string> time_in_force;
    /// Orig Type.
    std::optional<std::string> orig_type;
    /// Type.
    std::optional<std::string> type;
    /// activation price, only return with TRAILING_STOP_MARKET order
    std::optional<std::string> activate_price;
    /// callback rate, only return with TRAILING_STOP_MARKET order
    std::optional<std::string> price_rate;
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
    /// order pre-set auot cancel time for TIF GTD order
    std::optional<std::int64_t> good_till_date;

    bool operator==(const CancelOrderResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT CancelOrderResponse
tag_invoke(boost::json::value_to_tag<CancelOrderResponse> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                                boost::json::value& jv,
                                                                const CancelOrderResponse& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
