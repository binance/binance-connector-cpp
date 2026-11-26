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

#include <binance/stock_options/export.hpp>
#include <binance/stock_options/rest_api/models/option_order_history_response_rows_inner.hpp>

namespace binance::stock_options::rest_api {

struct OptionOrderHistoryResponse {
    /// Total number of records.
    std::optional<std::int64_t> total;
    /// Current page number.
    std::optional<std::int64_t> page;
    /// Current page size.
    std::optional<std::int64_t> size;
    /// Order records.
    std::optional<std::vector<OptionOrderHistoryResponseRowsInner>> rows;

    bool operator==(const OptionOrderHistoryResponse& /*other*/) const = default;
};

BINANCE_STOCK_OPTIONS_EXPORT OptionOrderHistoryResponse tag_invoke(
    boost::json::value_to_tag<OptionOrderHistoryResponse> /*tag*/, const boost::json::value& jv);
BINANCE_STOCK_OPTIONS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                             boost::json::value& jv,
                                             const OptionOrderHistoryResponse& v);

} // namespace binance::stock_options::rest_api
