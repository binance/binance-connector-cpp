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

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/pay/export.hpp>

namespace binance::pay::rest_api {

struct GetPayTradeHistoryResponseDataInnerPayerInfo {
    /// Nickname or merchant name.
    std::optional<std::string> name;
    /// Account type: USER for personal, MERCHANT for merchant.
    std::optional<std::string> type;
    /// Binance UID.
    std::optional<std::string> binance_id;

    bool operator==(const GetPayTradeHistoryResponseDataInnerPayerInfo& /*other*/) const = default;
};

BINANCE_PAY_EXPORT GetPayTradeHistoryResponseDataInnerPayerInfo
tag_invoke(boost::json::value_to_tag<GetPayTradeHistoryResponseDataInnerPayerInfo> /*tag*/,
           const boost::json::value& jv);
BINANCE_PAY_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                   const GetPayTradeHistoryResponseDataInnerPayerInfo& v);

} // namespace binance::pay::rest_api
