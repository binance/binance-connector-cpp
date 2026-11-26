//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/pay/rest_api/models/get_pay_trade_history_response_data_inner_payer_info.hpp>

namespace binance::pay::rest_api {

GetPayTradeHistoryResponseDataInnerPayerInfo
tag_invoke(boost::json::value_to_tag<GetPayTradeHistoryResponseDataInnerPayerInfo> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetPayTradeHistoryResponseDataInnerPayerInfo");
    GetPayTradeHistoryResponseDataInnerPayerInfo out;
    common::detail::json::read(obj, "name", out.name);
    common::detail::json::read(obj, "type", out.type);
    common::detail::json::read(obj, "binanceId", out.binance_id);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetPayTradeHistoryResponseDataInnerPayerInfo& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "name", v.name);
    common::detail::json::write(obj, "type", v.type);
    common::detail::json::write(obj, "binanceId", v.binance_id);
}

} // namespace binance::pay::rest_api
