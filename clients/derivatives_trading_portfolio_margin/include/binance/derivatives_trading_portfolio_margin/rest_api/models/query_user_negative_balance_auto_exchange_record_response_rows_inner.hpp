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
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/query_user_negative_balance_auto_exchange_record_response_rows_inner_details_inner.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

struct QueryUserNegativeBalanceAutoExchangeRecordResponseRowsInner {
    /// Start Time.
    std::optional<std::int64_t> start_time;
    /// End Time.
    std::optional<std::int64_t> end_time;
    /// Details.
    std::optional<
        std::vector<QueryUserNegativeBalanceAutoExchangeRecordResponseRowsInnerDetailsInner>>
        details;

    bool operator==(const QueryUserNegativeBalanceAutoExchangeRecordResponseRowsInner& /*other*/)
        const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT
QueryUserNegativeBalanceAutoExchangeRecordResponseRowsInner tag_invoke(
    boost::json::value_to_tag<QueryUserNegativeBalanceAutoExchangeRecordResponseRowsInner> /*tag*/,
    const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const QueryUserNegativeBalanceAutoExchangeRecordResponseRowsInner& v);

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
