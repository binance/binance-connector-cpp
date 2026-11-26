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

/// Extension fields.
struct GetPayTradeHistoryResponseDataInnerReceiverInfoExtend {
    /// Bank name or digital wallet name.
    std::optional<std::string> institution_name;
    /// Card number.
    std::optional<std::string> card_number;
    /// Digital wallet ID.
    std::optional<std::string> digital_wallet_id;

    bool operator==(const GetPayTradeHistoryResponseDataInnerReceiverInfoExtend& /*other*/) const =
        default;
};

BINANCE_PAY_EXPORT GetPayTradeHistoryResponseDataInnerReceiverInfoExtend
tag_invoke(boost::json::value_to_tag<GetPayTradeHistoryResponseDataInnerReceiverInfoExtend> /*tag*/,
           const boost::json::value& jv);
BINANCE_PAY_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                   const GetPayTradeHistoryResponseDataInnerReceiverInfoExtend& v);

} // namespace binance::pay::rest_api
