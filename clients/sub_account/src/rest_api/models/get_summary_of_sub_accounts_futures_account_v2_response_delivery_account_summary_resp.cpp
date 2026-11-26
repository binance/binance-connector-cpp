//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/sub_account/rest_api/models/get_summary_of_sub_accounts_futures_account_v2_response_delivery_account_summary_resp.hpp>

namespace binance::sub_account::rest_api {

GetSummaryOfSubAccountsFuturesAccountV2ResponseDeliveryAccountSummaryResp
tag_invoke(boost::json::value_to_tag<
               GetSummaryOfSubAccountsFuturesAccountV2ResponseDeliveryAccountSummaryResp> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "GetSummaryOfSubAccountsFuturesAccountV2ResponseDeliveryAccountSummaryResp");
    GetSummaryOfSubAccountsFuturesAccountV2ResponseDeliveryAccountSummaryResp out;
    common::detail::json::read(obj, "totalMarginBalanceOfBTC", out.total_margin_balance_of_btc);
    common::detail::json::read(obj, "totalUnrealizedProfitOfBTC",
                               out.total_unrealized_profit_of_btc);
    common::detail::json::read(obj, "totalWalletBalanceOfBTC", out.total_wallet_balance_of_btc);
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "subAccountList", out.sub_account_list);
    return out;
}

void tag_invoke(
    boost::json::value_from_tag /*tag*/, boost::json::value& jv,
    const GetSummaryOfSubAccountsFuturesAccountV2ResponseDeliveryAccountSummaryResp& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "totalMarginBalanceOfBTC", v.total_margin_balance_of_btc);
    common::detail::json::write(obj, "totalUnrealizedProfitOfBTC",
                                v.total_unrealized_profit_of_btc);
    common::detail::json::write(obj, "totalWalletBalanceOfBTC", v.total_wallet_balance_of_btc);
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "subAccountList", v.sub_account_list);
}

} // namespace binance::sub_account::rest_api
