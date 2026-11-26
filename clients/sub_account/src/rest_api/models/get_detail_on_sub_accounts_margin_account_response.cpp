//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/sub_account/rest_api/models/get_detail_on_sub_accounts_margin_account_response.hpp>

namespace binance::sub_account::rest_api {

GetDetailOnSubAccountsMarginAccountResponse
tag_invoke(boost::json::value_to_tag<GetDetailOnSubAccountsMarginAccountResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetDetailOnSubAccountsMarginAccountResponse");
    GetDetailOnSubAccountsMarginAccountResponse out;
    common::detail::json::read(obj, "email", out.email);
    common::detail::json::read(obj, "marginLevel", out.margin_level);
    common::detail::json::read(obj, "totalAssetOfBtc", out.total_asset_of_btc);
    common::detail::json::read(obj, "totalLiabilityOfBtc", out.total_liability_of_btc);
    common::detail::json::read(obj, "totalNetAssetOfBtc", out.total_net_asset_of_btc);
    common::detail::json::read(obj, "marginTradeCoeffVo", out.margin_trade_coeff_vo);
    common::detail::json::read(obj, "marginUserAssetVoList", out.margin_user_asset_vo_list);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetDetailOnSubAccountsMarginAccountResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "email", v.email);
    common::detail::json::write(obj, "marginLevel", v.margin_level);
    common::detail::json::write(obj, "totalAssetOfBtc", v.total_asset_of_btc);
    common::detail::json::write(obj, "totalLiabilityOfBtc", v.total_liability_of_btc);
    common::detail::json::write(obj, "totalNetAssetOfBtc", v.total_net_asset_of_btc);
    common::detail::json::write(obj, "marginTradeCoeffVo", v.margin_trade_coeff_vo);
    common::detail::json::write(obj, "marginUserAssetVoList", v.margin_user_asset_vo_list);
}

} // namespace binance::sub_account::rest_api
