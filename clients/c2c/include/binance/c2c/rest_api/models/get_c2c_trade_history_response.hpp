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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/c2c/export.hpp>
#include <binance/c2c/rest_api/models/get_c2c_trade_history_response_data_inner.hpp>

namespace binance::c2c::rest_api {

struct GetC2CTradeHistoryResponse {
    /// API response code. "000000" indicates success.
    std::optional<std::string> code;
    /// Response message.
    std::optional<std::string> message;
    std::optional<std::vector<GetC2CTradeHistoryResponseDataInner>> data;
    /// Total number of records
    std::optional<std::int64_t> total;
    /// Whether request is successful
    std::optional<bool> success;

    bool operator==(const GetC2CTradeHistoryResponse& /*other*/) const = default;
};

BINANCE_C2C_EXPORT GetC2CTradeHistoryResponse tag_invoke(
    boost::json::value_to_tag<GetC2CTradeHistoryResponse> /*tag*/, const boost::json::value& jv);
BINANCE_C2C_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                   const GetC2CTradeHistoryResponse& v);

} // namespace binance::c2c::rest_api
