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

#include <binance/margin_trading/export.hpp>
#include <binance/margin_trading/rest_api/models/get_interest_history_response_rows_inner.hpp>

namespace binance::margin_trading::rest_api {

struct GetInterestHistoryResponse {
    /// rows list.
    std::optional<std::vector<GetInterestHistoryResponseRowsInner>> rows;
    /// total.
    std::optional<std::int64_t> total;

    bool operator==(const GetInterestHistoryResponse& /*other*/) const = default;
};

BINANCE_MARGIN_TRADING_EXPORT GetInterestHistoryResponse tag_invoke(
    boost::json::value_to_tag<GetInterestHistoryResponse> /*tag*/, const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const GetInterestHistoryResponse& v);

} // namespace binance::margin_trading::rest_api
