//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/sub_account/rest_api/models/get_detail_on_sub_accounts_futures_account_v2_response_delivery_account_resp.hpp>

namespace binance::sub_account::rest_api {

GetDetailOnSubAccountsFuturesAccountV2ResponseDeliveryAccountResp
tag_invoke(boost::json::value_to_tag<
               GetDetailOnSubAccountsFuturesAccountV2ResponseDeliveryAccountResp> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "GetDetailOnSubAccountsFuturesAccountV2ResponseDeliveryAccountResp");
    GetDetailOnSubAccountsFuturesAccountV2ResponseDeliveryAccountResp out;
    common::detail::json::read(obj, "email", out.email);
    common::detail::json::read(obj, "assets", out.assets);
    common::detail::json::read(obj, "canDeposit", out.can_deposit);
    common::detail::json::read(obj, "canTrade", out.can_trade);
    common::detail::json::read(obj, "canWithdraw", out.can_withdraw);
    common::detail::json::read(obj, "feeTier", out.fee_tier);
    common::detail::json::read(obj, "updateTime", out.update_time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetDetailOnSubAccountsFuturesAccountV2ResponseDeliveryAccountResp& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "email", v.email);
    common::detail::json::write(obj, "assets", v.assets);
    common::detail::json::write(obj, "canDeposit", v.can_deposit);
    common::detail::json::write(obj, "canTrade", v.can_trade);
    common::detail::json::write(obj, "canWithdraw", v.can_withdraw);
    common::detail::json::write(obj, "feeTier", v.fee_tier);
    common::detail::json::write(obj, "updateTime", v.update_time);
}

} // namespace binance::sub_account::rest_api
