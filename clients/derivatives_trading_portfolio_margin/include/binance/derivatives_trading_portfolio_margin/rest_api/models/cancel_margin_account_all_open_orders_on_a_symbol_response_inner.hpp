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

#include <binance/derivatives_trading_portfolio_margin/export.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/cancel_margin_account_all_open_orders_on_a_symbol_response_inner_order_reports_inner.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/cancel_margin_account_all_open_orders_on_a_symbol_response_inner_orders_inner.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

struct CancelMarginAccountAllOpenOrdersOnASymbolResponseInner {
    /// Trade symbol, if existing.
    std::optional<std::string> symbol;
    /// Orig Client Order ID.
    std::optional<std::string> orig_client_order_id;
    /// Normal orderID after trigger if appliable, only have when the strategy is triggered
    std::optional<std::int64_t> order_id;
    /// Order List ID.
    std::optional<std::int64_t> order_list_id;
    /// Client Order ID.
    std::optional<std::string> client_order_id;
    /// Price.
    std::optional<std::string> price;
    /// Orig Qty.
    std::optional<std::string> orig_qty;
    /// Executed Qty.
    std::optional<std::string> executed_qty;
    /// Cummulative Quote Qty.
    std::optional<std::string> cummulative_quote_qty;
    /// Status.
    std::optional<std::string> status;
    /// Time In Force.
    std::optional<std::string> time_in_force;
    /// Normal order type after trigger if appliable
    std::optional<std::string> type;
    /// Side.
    std::optional<std::string> side;
    /// Contingency Type.
    std::optional<std::string> contingency_type;
    /// List Status Type.
    std::optional<std::string> list_status_type;
    /// List Order Status.
    std::optional<std::string> list_order_status;
    /// List Client Order ID.
    std::optional<std::string> list_client_order_id;
    /// Transaction Time.
    std::optional<std::int64_t> transaction_time;
    /// Orders.
    std::optional<std::vector<CancelMarginAccountAllOpenOrdersOnASymbolResponseInnerOrdersInner>>
        orders;
    /// Order Reports.
    std::optional<
        std::vector<CancelMarginAccountAllOpenOrdersOnASymbolResponseInnerOrderReportsInner>>
        order_reports;

    bool operator==(const CancelMarginAccountAllOpenOrdersOnASymbolResponseInner& /*other*/) const =
        default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT
CancelMarginAccountAllOpenOrdersOnASymbolResponseInner tag_invoke(
    boost::json::value_to_tag<CancelMarginAccountAllOpenOrdersOnASymbolResponseInner> /*tag*/,
    const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const CancelMarginAccountAllOpenOrdersOnASymbolResponseInner& v);

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
