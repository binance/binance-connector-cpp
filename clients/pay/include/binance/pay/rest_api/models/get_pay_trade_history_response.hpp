//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <optional>
#include <string>
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/pay/export.hpp>
#include <binance/pay/rest_api/models/get_pay_trade_history_response_data_inner.hpp>

namespace binance::pay::rest_api {

struct GetPayTradeHistoryResponse {
    std::optional<std::string> code;
    std::optional<std::string> message;
    std::optional<std::vector<GetPayTradeHistoryResponseDataInner>> data;
    std::optional<bool> success;

    bool operator==(const GetPayTradeHistoryResponse& /*other*/) const = default;
};

BINANCE_PAY_EXPORT GetPayTradeHistoryResponse tag_invoke(
    boost::json::value_to_tag<GetPayTradeHistoryResponse> /*tag*/, const boost::json::value& jv);
BINANCE_PAY_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                   const GetPayTradeHistoryResponse& v);

} // namespace binance::pay::rest_api
