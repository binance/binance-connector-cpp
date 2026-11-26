//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/sub_account/rest_api/models/get_summary_of_sub_accounts_futures_account_v2_response.hpp>

namespace binance::sub_account::rest_api {

GetSummaryOfSubAccountsFuturesAccountV2Response
tag_invoke(boost::json::value_to_tag<GetSummaryOfSubAccountsFuturesAccountV2Response> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetSummaryOfSubAccountsFuturesAccountV2Response");
    GetSummaryOfSubAccountsFuturesAccountV2Response out;
    common::detail::json::read(obj, "futureAccountSummaryResp", out.future_account_summary_resp);
    common::detail::json::read(obj, "deliveryAccountSummaryResp",
                               out.delivery_account_summary_resp);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetSummaryOfSubAccountsFuturesAccountV2Response& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "futureAccountSummaryResp", v.future_account_summary_resp);
    common::detail::json::write(obj, "deliveryAccountSummaryResp", v.delivery_account_summary_resp);
}

} // namespace binance::sub_account::rest_api
