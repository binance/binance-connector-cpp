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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/derivatives_trading_portfolio_margin/export.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/query_user_negative_balance_auto_exchange_record_response_rows_inner.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

struct QueryUserNegativeBalanceAutoExchangeRecordResponse {
    /// Total.
    std::optional<std::int64_t> total;
    /// Rows.
    std::optional<std::vector<QueryUserNegativeBalanceAutoExchangeRecordResponseRowsInner>> rows;

    bool
    operator==(const QueryUserNegativeBalanceAutoExchangeRecordResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT
QueryUserNegativeBalanceAutoExchangeRecordResponse
tag_invoke(boost::json::value_to_tag<QueryUserNegativeBalanceAutoExchangeRecordResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const QueryUserNegativeBalanceAutoExchangeRecordResponse& v);

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
