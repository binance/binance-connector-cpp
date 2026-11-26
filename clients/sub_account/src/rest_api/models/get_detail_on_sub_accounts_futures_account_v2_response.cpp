//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/sub_account/rest_api/models/get_detail_on_sub_accounts_futures_account_v2_response.hpp>

namespace binance::sub_account::rest_api {

GetDetailOnSubAccountsFuturesAccountV2Response
tag_invoke(boost::json::value_to_tag<GetDetailOnSubAccountsFuturesAccountV2Response> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetDetailOnSubAccountsFuturesAccountV2Response");
    GetDetailOnSubAccountsFuturesAccountV2Response out;
    common::detail::json::read(obj, "futureAccountResp", out.future_account_resp);
    common::detail::json::read(obj, "deliveryAccountResp", out.delivery_account_resp);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetDetailOnSubAccountsFuturesAccountV2Response& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "futureAccountResp", v.future_account_resp);
    common::detail::json::write(obj, "deliveryAccountResp", v.delivery_account_resp);
}

} // namespace binance::sub_account::rest_api
