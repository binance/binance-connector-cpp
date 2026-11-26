//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/c2c/rest_api/models/get_c2c_trade_history_response_data_inner.hpp>
#include <binance/common/detail/json.hpp>

namespace binance::c2c::rest_api {

GetC2CTradeHistoryResponseDataInner
tag_invoke(boost::json::value_to_tag<GetC2CTradeHistoryResponseDataInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetC2CTradeHistoryResponseDataInner");
    GetC2CTradeHistoryResponseDataInner out;
    common::detail::json::read(obj, "orderNumber", out.order_number);
    common::detail::json::read(obj, "advNo", out.adv_no);
    common::detail::json::read(obj, "tradeType", out.trade_type);
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "fiat", out.fiat);
    common::detail::json::read(obj, "fiatSymbol", out.fiat_symbol);
    common::detail::json::read(obj, "amount", out.amount);
    common::detail::json::read(obj, "totalPrice", out.total_price);
    common::detail::json::read(obj, "unitPrice", out.unit_price);
    common::detail::json::read(obj, "orderStatus", out.order_status);
    common::detail::json::read(obj, "createTime", out.create_time);
    common::detail::json::read(obj, "commission", out.commission);
    common::detail::json::read(obj, "counterPartNickName", out.counter_part_nick_name);
    common::detail::json::read(obj, "payMethodName", out.pay_method_name);
    common::detail::json::read(obj, "additionalKycVerify", out.additional_kyc_verify);
    common::detail::json::read(obj, "takerCommissionRate", out.taker_commission_rate);
    common::detail::json::read(obj, "takerCommission", out.taker_commission);
    common::detail::json::read(obj, "takerAmount", out.taker_amount);
    common::detail::json::read(obj, "advertisementRole", out.advertisement_role);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetC2CTradeHistoryResponseDataInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "orderNumber", v.order_number);
    common::detail::json::write(obj, "advNo", v.adv_no);
    common::detail::json::write(obj, "tradeType", v.trade_type);
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "fiat", v.fiat);
    common::detail::json::write(obj, "fiatSymbol", v.fiat_symbol);
    common::detail::json::write(obj, "amount", v.amount);
    common::detail::json::write(obj, "totalPrice", v.total_price);
    common::detail::json::write(obj, "unitPrice", v.unit_price);
    common::detail::json::write(obj, "orderStatus", v.order_status);
    common::detail::json::write(obj, "createTime", v.create_time);
    common::detail::json::write(obj, "commission", v.commission);
    common::detail::json::write(obj, "counterPartNickName", v.counter_part_nick_name);
    common::detail::json::write(obj, "payMethodName", v.pay_method_name);
    common::detail::json::write(obj, "additionalKycVerify", v.additional_kyc_verify);
    common::detail::json::write(obj, "takerCommissionRate", v.taker_commission_rate);
    common::detail::json::write(obj, "takerCommission", v.taker_commission);
    common::detail::json::write(obj, "takerAmount", v.taker_amount);
    common::detail::json::write(obj, "advertisementRole", v.advertisement_role);
}

} // namespace binance::c2c::rest_api
