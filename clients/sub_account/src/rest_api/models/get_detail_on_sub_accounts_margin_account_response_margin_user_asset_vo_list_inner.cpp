//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/sub_account/rest_api/models/get_detail_on_sub_accounts_margin_account_response_margin_user_asset_vo_list_inner.hpp>

namespace binance::sub_account::rest_api {

GetDetailOnSubAccountsMarginAccountResponseMarginUserAssetVoListInner
tag_invoke(boost::json::value_to_tag<
               GetDetailOnSubAccountsMarginAccountResponseMarginUserAssetVoListInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "GetDetailOnSubAccountsMarginAccountResponseMarginUserAssetVoListInner");
    GetDetailOnSubAccountsMarginAccountResponseMarginUserAssetVoListInner out;
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "borrowed", out.borrowed);
    common::detail::json::read(obj, "free", out.free);
    common::detail::json::read(obj, "interest", out.interest);
    common::detail::json::read(obj, "locked", out.locked);
    common::detail::json::read(obj, "netAsset", out.net_asset);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetDetailOnSubAccountsMarginAccountResponseMarginUserAssetVoListInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "borrowed", v.borrowed);
    common::detail::json::write(obj, "free", v.free);
    common::detail::json::write(obj, "interest", v.interest);
    common::detail::json::write(obj, "locked", v.locked);
    common::detail::json::write(obj, "netAsset", v.net_asset);
}

} // namespace binance::sub_account::rest_api
