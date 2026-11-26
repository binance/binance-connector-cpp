//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/pay/rest_api/models/get_pay_trade_history_response_data_inner_receiver_info_extend.hpp>

namespace binance::pay::rest_api {

GetPayTradeHistoryResponseDataInnerReceiverInfoExtend
tag_invoke(boost::json::value_to_tag<GetPayTradeHistoryResponseDataInnerReceiverInfoExtend> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "GetPayTradeHistoryResponseDataInnerReceiverInfoExtend");
    GetPayTradeHistoryResponseDataInnerReceiverInfoExtend out;
    common::detail::json::read(obj, "institutionName", out.institution_name);
    common::detail::json::read(obj, "cardNumber", out.card_number);
    common::detail::json::read(obj, "digitalWalletId", out.digital_wallet_id);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetPayTradeHistoryResponseDataInnerReceiverInfoExtend& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "institutionName", v.institution_name);
    common::detail::json::write(obj, "cardNumber", v.card_number);
    common::detail::json::write(obj, "digitalWalletId", v.digital_wallet_id);
}

} // namespace binance::pay::rest_api
