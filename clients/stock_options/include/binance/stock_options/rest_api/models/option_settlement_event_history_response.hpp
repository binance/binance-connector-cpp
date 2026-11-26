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
#include <binance/stock_options/rest_api/models/option_settlement_event_history_response_rows_inner.hpp>

namespace binance::stock_options::rest_api {

struct OptionSettlementEventHistoryResponse {
    /// Event records.
    std::optional<std::vector<OptionSettlementEventHistoryResponseRowsInner>> rows;
    /// Whether there is a next page.
    std::optional<bool> has_more;
    /// Cursor for the next page.
    std::optional<std::int64_t> next_last_id;

    bool operator==(const OptionSettlementEventHistoryResponse& /*other*/) const = default;
};

BINANCE_STOCK_OPTIONS_EXPORT OptionSettlementEventHistoryResponse
tag_invoke(boost::json::value_to_tag<OptionSettlementEventHistoryResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_STOCK_OPTIONS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                             boost::json::value& jv,
                                             const OptionSettlementEventHistoryResponse& v);

} // namespace binance::stock_options::rest_api
