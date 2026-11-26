//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/fiat/rest_api/models/get_fiat_deposit_withdraw_history_response_data_inner.hpp>

namespace binance::fiat::rest_api {

GetFiatDepositWithdrawHistoryResponseDataInner
tag_invoke(boost::json::value_to_tag<GetFiatDepositWithdrawHistoryResponseDataInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetFiatDepositWithdrawHistoryResponseDataInner");
    GetFiatDepositWithdrawHistoryResponseDataInner out;
    common::detail::json::read(obj, "orderNo", out.order_no);
    common::detail::json::read(obj, "fiatCurrency", out.fiat_currency);
    common::detail::json::read(obj, "indicatedAmount", out.indicated_amount);
    common::detail::json::read(obj, "amount", out.amount);
    common::detail::json::read(obj, "totalFee", out.total_fee);
    common::detail::json::read(obj, "method", out.method);
    common::detail::json::read(obj, "status", out.status);
    common::detail::json::read(obj, "createTime", out.create_time);
    common::detail::json::read(obj, "updateTime", out.update_time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetFiatDepositWithdrawHistoryResponseDataInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "orderNo", v.order_no);
    common::detail::json::write(obj, "fiatCurrency", v.fiat_currency);
    common::detail::json::write(obj, "indicatedAmount", v.indicated_amount);
    common::detail::json::write(obj, "amount", v.amount);
    common::detail::json::write(obj, "totalFee", v.total_fee);
    common::detail::json::write(obj, "method", v.method);
    common::detail::json::write(obj, "status", v.status);
    common::detail::json::write(obj, "createTime", v.create_time);
    common::detail::json::write(obj, "updateTime", v.update_time);
}

} // namespace binance::fiat::rest_api
