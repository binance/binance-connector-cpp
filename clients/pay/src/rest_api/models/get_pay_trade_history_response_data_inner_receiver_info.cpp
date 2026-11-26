//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/pay/rest_api/models/get_pay_trade_history_response_data_inner_receiver_info.hpp>

namespace binance::pay::rest_api {

GetPayTradeHistoryResponseDataInnerReceiverInfo
tag_invoke(boost::json::value_to_tag<GetPayTradeHistoryResponseDataInnerReceiverInfo> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetPayTradeHistoryResponseDataInnerReceiverInfo");
    GetPayTradeHistoryResponseDataInnerReceiverInfo out;
    common::detail::json::read(obj, "name", out.name);
    common::detail::json::read(obj, "type", out.type);
    common::detail::json::read(obj, "email", out.email);
    common::detail::json::read(obj, "binanceId", out.binance_id);
    common::detail::json::read(obj, "accountId", out.account_id);
    common::detail::json::read(obj, "countryCode", out.country_code);
    common::detail::json::read(obj, "phoneNumber", out.phone_number);
    common::detail::json::read(obj, "mobileCode", out.mobile_code);
    common::detail::json::read(obj, "extend", out.extend);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetPayTradeHistoryResponseDataInnerReceiverInfo& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "name", v.name);
    common::detail::json::write(obj, "type", v.type);
    common::detail::json::write(obj, "email", v.email);
    common::detail::json::write(obj, "binanceId", v.binance_id);
    common::detail::json::write(obj, "accountId", v.account_id);
    common::detail::json::write(obj, "countryCode", v.country_code);
    common::detail::json::write(obj, "phoneNumber", v.phone_number);
    common::detail::json::write(obj, "mobileCode", v.mobile_code);
    common::detail::json::write(obj, "extend", v.extend);
}

} // namespace binance::pay::rest_api
