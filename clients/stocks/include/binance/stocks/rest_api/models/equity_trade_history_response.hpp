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

#include <binance/stocks/export.hpp>
#include <binance/stocks/rest_api/models/equity_trade_history_response_rows_inner.hpp>

namespace binance::stocks::rest_api {

struct EquityTradeHistoryResponse {
    /// Total number of rows matching the filter.
    std::optional<std::int64_t> total;
    /// Current page.
    std::optional<std::int64_t> page;
    /// Current page size.
    std::optional<std::int64_t> size;
    /// Trade rows on this page. Empty when nothing matches.
    std::optional<std::vector<EquityTradeHistoryResponseRowsInner>> rows;

    bool operator==(const EquityTradeHistoryResponse& /*other*/) const = default;
};

BINANCE_STOCKS_EXPORT EquityTradeHistoryResponse tag_invoke(
    boost::json::value_to_tag<EquityTradeHistoryResponse> /*tag*/, const boost::json::value& jv);
BINANCE_STOCKS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const EquityTradeHistoryResponse& v);

} // namespace binance::stocks::rest_api
