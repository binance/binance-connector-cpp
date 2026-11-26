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

struct GetForceLiquidationRecordResponseRowsInner {
    /// avg Price.
    std::optional<std::string> avg_price;
    /// executed Qty.
    std::optional<std::string> executed_qty;
    /// order Id.
    std::optional<std::int64_t> order_id;
    /// price.
    std::optional<std::string> price;
    /// qty.
    std::optional<std::string> qty;
    /// side.
    std::optional<std::string> side;
    /// symbol.
    std::optional<std::string> symbol;
    /// time In Force.
    std::optional<std::string> time_in_force;
    /// is Isolated.
    std::optional<bool> is_isolated;
    /// updated Time.
    std::optional<std::int64_t> updated_time;

    bool operator==(const GetForceLiquidationRecordResponseRowsInner& /*other*/) const = default;
};

BINANCE_MARGIN_TRADING_EXPORT GetForceLiquidationRecordResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetForceLiquidationRecordResponseRowsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const GetForceLiquidationRecordResponseRowsInner& v);

} // namespace binance::margin_trading::rest_api
