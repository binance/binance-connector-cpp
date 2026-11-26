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
#include <binance/pay/rest_api/models/get_pay_trade_history_response_data_inner_receiver_info_extend.hpp>

namespace binance::pay::rest_api {

struct GetPayTradeHistoryResponseDataInnerReceiverInfo {
    /// Nickname or merchant name.
    std::optional<std::string> name;
    /// Account type: USER for personal, MERCHANT for merchant.
    std::optional<std::string> type;
    /// Email.
    std::optional<std::string> email;
    /// Binance UID.
    std::optional<std::string> binance_id;
    /// Binance Pay ID.
    std::optional<std::string> account_id;
    /// International area code.
    std::optional<std::string> country_code;
    /// Phone number.
    std::optional<std::string> phone_number;
    /// Country code.
    std::optional<std::string> mobile_code;
    std::optional<GetPayTradeHistoryResponseDataInnerReceiverInfoExtend> extend;

    bool
    operator==(const GetPayTradeHistoryResponseDataInnerReceiverInfo& /*other*/) const = default;
};

BINANCE_PAY_EXPORT GetPayTradeHistoryResponseDataInnerReceiverInfo
tag_invoke(boost::json::value_to_tag<GetPayTradeHistoryResponseDataInnerReceiverInfo> /*tag*/,
           const boost::json::value& jv);
BINANCE_PAY_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                   const GetPayTradeHistoryResponseDataInnerReceiverInfo& v);

} // namespace binance::pay::rest_api
