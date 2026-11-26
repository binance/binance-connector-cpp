//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/sub_account/rest_api/models/get_summary_of_sub_accounts_margin_account_response.hpp>

namespace binance::sub_account::rest_api {

GetSummaryOfSubAccountsMarginAccountResponse
tag_invoke(boost::json::value_to_tag<GetSummaryOfSubAccountsMarginAccountResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetSummaryOfSubAccountsMarginAccountResponse");
    GetSummaryOfSubAccountsMarginAccountResponse out;
    common::detail::json::read(obj, "totalAssetOfBtc", out.total_asset_of_btc);
    common::detail::json::read(obj, "totalLiabilityOfBtc", out.total_liability_of_btc);
    common::detail::json::read(obj, "totalNetAssetOfBtc", out.total_net_asset_of_btc);
    common::detail::json::read(obj, "subAccountList", out.sub_account_list);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetSummaryOfSubAccountsMarginAccountResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "totalAssetOfBtc", v.total_asset_of_btc);
    common::detail::json::write(obj, "totalLiabilityOfBtc", v.total_liability_of_btc);
    common::detail::json::write(obj, "totalNetAssetOfBtc", v.total_net_asset_of_btc);
    common::detail::json::write(obj, "subAccountList", v.sub_account_list);
}

} // namespace binance::sub_account::rest_api
