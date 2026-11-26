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

#include <binance/convert/export.hpp>
#include <binance/convert/rest_api/models/get_convert_trade_history_response_list_inner.hpp>

namespace binance::convert::rest_api {

struct GetConvertTradeHistoryResponse {
    std::optional<std::vector<GetConvertTradeHistoryResponseListInner>> list;
    std::optional<std::int64_t> start_time;
    std::optional<std::int64_t> end_time;
    std::optional<std::int64_t> limit;
    std::optional<bool> more_data;

    bool operator==(const GetConvertTradeHistoryResponse& /*other*/) const = default;
};

BINANCE_CONVERT_EXPORT GetConvertTradeHistoryResponse
tag_invoke(boost::json::value_to_tag<GetConvertTradeHistoryResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_CONVERT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                       const GetConvertTradeHistoryResponse& v);

} // namespace binance::convert::rest_api
