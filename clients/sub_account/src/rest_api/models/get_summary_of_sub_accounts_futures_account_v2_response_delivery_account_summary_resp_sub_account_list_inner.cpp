//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/sub_account/rest_api/models/get_summary_of_sub_accounts_futures_account_v2_response_delivery_account_summary_resp_sub_account_list_inner.hpp>

namespace binance::sub_account::rest_api {

GetSummaryOfSubAccountsFuturesAccountV2ResponseDeliveryAccountSummaryRespSubAccountListInner
tag_invoke(
    boost::json::value_to_tag<
        GetSummaryOfSubAccountsFuturesAccountV2ResponseDeliveryAccountSummaryRespSubAccountListInner> /*tag*/
    ,
    const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetSummaryOfSubAccountsFuturesAccountV2ResponseDeliver"
                                            "yAccountSummaryRespSubAccountListInner");
    GetSummaryOfSubAccountsFuturesAccountV2ResponseDeliveryAccountSummaryRespSubAccountListInner
        out;
    common::detail::json::read(obj, "email", out.email);
    common::detail::json::read(obj, "totalMarginBalance", out.total_margin_balance);
    common::detail::json::read(obj, "totalUnrealizedProfit", out.total_unrealized_profit);
    common::detail::json::read(obj, "totalWalletBalance", out.total_wallet_balance);
    common::detail::json::read(obj, "asset", out.asset);
    return out;
}

void tag_invoke(
    boost::json::value_from_tag /*tag*/, boost::json::value& jv,
    const GetSummaryOfSubAccountsFuturesAccountV2ResponseDeliveryAccountSummaryRespSubAccountListInner&
        v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "email", v.email);
    common::detail::json::write(obj, "totalMarginBalance", v.total_margin_balance);
    common::detail::json::write(obj, "totalUnrealizedProfit", v.total_unrealized_profit);
    common::detail::json::write(obj, "totalWalletBalance", v.total_wallet_balance);
    common::detail::json::write(obj, "asset", v.asset);
}

} // namespace binance::sub_account::rest_api
