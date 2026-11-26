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

struct QueryMarginAccountsOpenOrdersResponseInner {
    /// client Order Id.
    std::optional<std::string> client_order_id;
    /// cummulative Quote Qty.
    std::optional<std::string> cummulative_quote_qty;
    /// executed Qty.
    std::optional<std::string> executed_qty;
    /// iceberg Qty.
    std::optional<std::string> iceberg_qty;
    /// is Working.
    std::optional<bool> is_working;
    /// order Id.
    std::optional<std::int64_t> order_id;
    /// orig Qty.
    std::optional<std::string> orig_qty;
    /// price.
    std::optional<std::string> price;
    /// side.
    std::optional<std::string> side;
    /// status.
    std::optional<std::string> status;
    /// stop Price.
    std::optional<std::string> stop_price;
    /// symbol.
    std::optional<std::string> symbol;
    /// is Isolated.
    std::optional<bool> is_isolated;
    /// time.
    std::optional<std::int64_t> time;
    /// time In Force.
    std::optional<std::string> time_in_force;
    /// type.
    std::optional<std::string> type;
    /// self Trade Prevention Mode.
    std::optional<std::string> self_trade_prevention_mode;
    /// update Time.
    std::optional<std::int64_t> update_time;

    bool operator==(const QueryMarginAccountsOpenOrdersResponseInner& /*other*/) const = default;
};

BINANCE_MARGIN_TRADING_EXPORT QueryMarginAccountsOpenOrdersResponseInner
tag_invoke(boost::json::value_to_tag<QueryMarginAccountsOpenOrdersResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const QueryMarginAccountsOpenOrdersResponseInner& v);

} // namespace binance::margin_trading::rest_api
