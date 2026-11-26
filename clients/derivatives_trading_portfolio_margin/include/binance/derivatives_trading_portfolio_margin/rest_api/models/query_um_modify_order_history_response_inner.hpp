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

#include <binance/derivatives_trading_portfolio_margin/export.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/query_cm_modify_order_history_response_inner_amendment.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

struct QueryUmModifyOrderHistoryResponseInner {
    /// Order modification ID
    std::optional<std::int64_t> amendment_id;
    /// Trade symbol, if existing.
    std::optional<std::string> symbol;
    /// Pair.
    std::optional<std::string> pair;
    /// Normal orderID after trigger if appliable, only have when the strategy is triggered
    std::optional<std::int64_t> order_id;
    /// Client Order ID.
    std::optional<std::string> client_order_id;
    /// Order modification time
    std::optional<std::int64_t> time;
    std::optional<QueryCmModifyOrderHistoryResponseInnerAmendment> amendment;
    /// Price Match.
    std::optional<std::string> price_match;

    bool operator==(const QueryUmModifyOrderHistoryResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT QueryUmModifyOrderHistoryResponseInner
tag_invoke(boost::json::value_to_tag<QueryUmModifyOrderHistoryResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const QueryUmModifyOrderHistoryResponseInner& v);

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
