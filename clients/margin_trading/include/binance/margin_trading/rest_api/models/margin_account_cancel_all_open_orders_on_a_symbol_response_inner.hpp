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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/margin_trading/export.hpp>
#include <binance/margin_trading/rest_api/models/margin_account_cancel_all_open_orders_on_a_symbol_response_inner_order_reports_inner.hpp>
#include <binance/margin_trading/rest_api/models/margin_account_cancel_all_open_orders_on_a_symbol_response_inner_orders_inner.hpp>

namespace binance::margin_trading::rest_api {

struct MarginAccountCancelAllOpenOrdersOnASymbolResponseInner {
    /// symbol.
    std::optional<std::string> symbol;
    /// if isolated margin
    std::optional<bool> is_isolated;
    /// orig Client Order Id.
    std::optional<std::string> orig_client_order_id;
    /// order Id.
    std::optional<std::int64_t> order_id;
    /// order List Id.
    std::optional<std::int64_t> order_list_id;
    /// client Order Id.
    std::optional<std::string> client_order_id;
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
    /// contingency Type.
    std::optional<std::string> contingency_type;
    /// list Status Type.
    std::optional<std::string> list_status_type;
    /// list Order Status.
    std::optional<std::string> list_order_status;
    /// list Client Order Id.
    std::optional<std::string> list_client_order_id;
    /// transaction Time.
    std::optional<std::int64_t> transaction_time;
    /// orders list.
    std::optional<std::vector<MarginAccountCancelAllOpenOrdersOnASymbolResponseInnerOrdersInner>>
        orders;
    /// order Reports list.
    std::optional<
        std::vector<MarginAccountCancelAllOpenOrdersOnASymbolResponseInnerOrderReportsInner>>
        order_reports;

    bool operator==(const MarginAccountCancelAllOpenOrdersOnASymbolResponseInner& /*other*/) const =
        default;
};

BINANCE_MARGIN_TRADING_EXPORT MarginAccountCancelAllOpenOrdersOnASymbolResponseInner tag_invoke(
    boost::json::value_to_tag<MarginAccountCancelAllOpenOrdersOnASymbolResponseInner> /*tag*/,
    const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const MarginAccountCancelAllOpenOrdersOnASymbolResponseInner& v);

} // namespace binance::margin_trading::rest_api
