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
#include <binance/stocks/rest_api/models/equity_order_history_response_rows_inner.hpp>

namespace binance::stocks::rest_api {

struct EquityOrderHistoryResponse {
    /// Total number of rows matching the filter.
    std::optional<std::int64_t> total;
    /// Current page (echoes `current`).
    std::optional<std::int64_t> page;
    /// Current page size (echoes `size`).
    std::optional<std::int64_t> size;
    /// Order rows on this page. Empty array if nothing matches.
    std::optional<std::vector<EquityOrderHistoryResponseRowsInner>> rows;

    bool operator==(const EquityOrderHistoryResponse& /*other*/) const = default;
};

BINANCE_STOCKS_EXPORT EquityOrderHistoryResponse tag_invoke(
    boost::json::value_to_tag<EquityOrderHistoryResponse> /*tag*/, const boost::json::value& jv);
BINANCE_STOCKS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const EquityOrderHistoryResponse& v);

} // namespace binance::stocks::rest_api
