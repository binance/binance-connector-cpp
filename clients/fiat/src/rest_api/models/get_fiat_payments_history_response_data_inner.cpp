//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/fiat/rest_api/models/get_fiat_payments_history_response_data_inner.hpp>

namespace binance::fiat::rest_api {

GetFiatPaymentsHistoryResponseDataInner
tag_invoke(boost::json::value_to_tag<GetFiatPaymentsHistoryResponseDataInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetFiatPaymentsHistoryResponseDataInner");
    GetFiatPaymentsHistoryResponseDataInner out;
    common::detail::json::read(obj, "orderNo", out.order_no);
    common::detail::json::read(obj, "sourceAmount", out.source_amount);
    common::detail::json::read(obj, "fiatCurrency", out.fiat_currency);
    common::detail::json::read(obj, "obtainAmount", out.obtain_amount);
    common::detail::json::read(obj, "cryptoCurrency", out.crypto_currency);
    common::detail::json::read(obj, "totalFee", out.total_fee);
    common::detail::json::read(obj, "price", out.price);
    common::detail::json::read(obj, "status", out.status);
    common::detail::json::read(obj, "paymentMethod", out.payment_method);
    common::detail::json::read(obj, "createTime", out.create_time);
    common::detail::json::read(obj, "updateTime", out.update_time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetFiatPaymentsHistoryResponseDataInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "orderNo", v.order_no);
    common::detail::json::write(obj, "sourceAmount", v.source_amount);
    common::detail::json::write(obj, "fiatCurrency", v.fiat_currency);
    common::detail::json::write(obj, "obtainAmount", v.obtain_amount);
    common::detail::json::write(obj, "cryptoCurrency", v.crypto_currency);
    common::detail::json::write(obj, "totalFee", v.total_fee);
    common::detail::json::write(obj, "price", v.price);
    common::detail::json::write(obj, "status", v.status);
    common::detail::json::write(obj, "paymentMethod", v.payment_method);
    common::detail::json::write(obj, "createTime", v.create_time);
    common::detail::json::write(obj, "updateTime", v.update_time);
}

} // namespace binance::fiat::rest_api
