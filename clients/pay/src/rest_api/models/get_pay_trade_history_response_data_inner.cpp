//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/pay/rest_api/models/get_pay_trade_history_response_data_inner.hpp>

namespace binance::pay::rest_api {

GetPayTradeHistoryResponseDataInner
tag_invoke(boost::json::value_to_tag<GetPayTradeHistoryResponseDataInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetPayTradeHistoryResponseDataInner");
    GetPayTradeHistoryResponseDataInner out;
    common::detail::json::read(obj, "orderType", out.order_type);
    common::detail::json::read(obj, "transactionId", out.transaction_id);
    common::detail::json::read(obj, "transactionTime", out.transaction_time);
    common::detail::json::read(obj, "amount", out.amount);
    common::detail::json::read(obj, "currency", out.currency);
    common::detail::json::read(obj, "walletType", out.wallet_type);
    common::detail::json::read(obj, "walletTypes", out.wallet_types);
    common::detail::json::read(obj, "fundsDetail", out.funds_detail);
    common::detail::json::read(obj, "payerInfo", out.payer_info);
    common::detail::json::read(obj, "receiverInfo", out.receiver_info);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetPayTradeHistoryResponseDataInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "orderType", v.order_type);
    common::detail::json::write(obj, "transactionId", v.transaction_id);
    common::detail::json::write(obj, "transactionTime", v.transaction_time);
    common::detail::json::write(obj, "amount", v.amount);
    common::detail::json::write(obj, "currency", v.currency);
    common::detail::json::write(obj, "walletType", v.wallet_type);
    common::detail::json::write(obj, "walletTypes", v.wallet_types);
    common::detail::json::write(obj, "fundsDetail", v.funds_detail);
    common::detail::json::write(obj, "payerInfo", v.payer_info);
    common::detail::json::write(obj, "receiverInfo", v.receiver_info);
}

} // namespace binance::pay::rest_api
