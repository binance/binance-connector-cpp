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

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/derivatives_trading_portfolio_margin/export.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/query_cm_modify_order_history_response_inner_amendment_orig_qty.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/query_cm_modify_order_history_response_inner_amendment_price.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

/// Amendment.
struct QueryCmModifyOrderHistoryResponseInnerAmendment {
    std::optional<QueryCmModifyOrderHistoryResponseInnerAmendmentPrice> price;
    std::optional<QueryCmModifyOrderHistoryResponseInnerAmendmentOrigQty> orig_qty;
    /// Order modification count, representing the number of times the order has been modified
    std::optional<std::int64_t> count;
    /// user-defined modification identifier, only returned if provided in the request
    std::optional<std::int64_t> modify_id;

    bool
    operator==(const QueryCmModifyOrderHistoryResponseInnerAmendment& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT QueryCmModifyOrderHistoryResponseInnerAmendment
tag_invoke(boost::json::value_to_tag<QueryCmModifyOrderHistoryResponseInnerAmendment> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const QueryCmModifyOrderHistoryResponseInnerAmendment& v);

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
