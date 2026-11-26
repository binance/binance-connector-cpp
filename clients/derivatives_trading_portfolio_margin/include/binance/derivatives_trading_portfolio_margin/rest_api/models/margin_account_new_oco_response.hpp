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
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/margin_account_new_oco_response_order_reports_inner.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/margin_account_new_oco_response_orders_inner.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

struct MarginAccountNewOcoResponse {
    /// Order List ID.
    std::optional<std::int64_t> order_list_id;
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
    /// Trade symbol, if existing.
    std::optional<std::string> symbol;
    /// will not return if no margin trade happens
    std::optional<std::string> margin_buy_borrow_amount;
    /// will not return if no margin trade happens
    std::optional<std::string> margin_buy_borrow_asset;
    /// Orders.
    std::optional<std::vector<MarginAccountNewOcoResponseOrdersInner>> orders;
    /// Order Reports.
    std::optional<std::vector<MarginAccountNewOcoResponseOrderReportsInner>> order_reports;

    bool operator==(const MarginAccountNewOcoResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT MarginAccountNewOcoResponse tag_invoke(
    boost::json::value_to_tag<MarginAccountNewOcoResponse> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const MarginAccountNewOcoResponse& v);

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
