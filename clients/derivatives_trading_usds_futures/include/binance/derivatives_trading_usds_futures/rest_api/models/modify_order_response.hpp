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

struct ModifyOrderResponse {
    std::optional<std::int64_t> order_id;
    std::optional<std::string> symbol;
    std::optional<std::string> pair;
    std::optional<std::string> status;
    std::optional<std::string> client_order_id;
    /// user-defined modification identifier, only returned if provided in the request
    std::optional<std::int64_t> modify_id;
    std::optional<std::string> price;
    std::optional<std::string> orig_qty;
    std::optional<std::string> executed_qty;
    std::optional<std::string> cum_qty;
    std::optional<std::string> time_in_force;
    std::optional<std::string> type;
    std::optional<bool> reduce_only;
    std::optional<bool> close_position;
    std::optional<std::string> side;
    std::optional<std::string> position_side;
    std::optional<std::string> stop_price;
    std::optional<std::string> working_type;
    std::optional<bool> price_protect;
    std::optional<std::string> orig_type;
    /// price match mode
    std::optional<std::string> price_match;
    /// self trading preventation mode
    std::optional<std::string> self_trade_prevention_mode;
    /// order pre-set auot cancel time for TIF GTD order
    std::optional<std::int64_t> good_till_date;
    std::optional<std::int64_t> update_time;

    bool operator==(const ModifyOrderResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT ModifyOrderResponse
tag_invoke(boost::json::value_to_tag<ModifyOrderResponse> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                                boost::json::value& jv,
                                                                const ModifyOrderResponse& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
