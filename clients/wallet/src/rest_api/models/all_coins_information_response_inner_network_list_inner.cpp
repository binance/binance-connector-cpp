//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/wallet/rest_api/models/all_coins_information_response_inner_network_list_inner.hpp>

namespace binance::wallet::rest_api {

AllCoinsInformationResponseInnerNetworkListInner
tag_invoke(boost::json::value_to_tag<AllCoinsInformationResponseInnerNetworkListInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "AllCoinsInformationResponseInnerNetworkListInner");
    AllCoinsInformationResponseInnerNetworkListInner out;
    common::detail::json::read(obj, "network", out.network);
    common::detail::json::read(obj, "coin", out.coin);
    common::detail::json::read(obj, "withdrawIntegerMultiple", out.withdraw_integer_multiple);
    common::detail::json::read(obj, "isDefault", out.is_default);
    common::detail::json::read(obj, "depositEnable", out.deposit_enable);
    common::detail::json::read(obj, "withdrawEnable", out.withdraw_enable);
    common::detail::json::read(obj, "depositDesc", out.deposit_desc);
    common::detail::json::read(obj, "withdrawDesc", out.withdraw_desc);
    common::detail::json::read(obj, "specialTips", out.special_tips);
    common::detail::json::read(obj, "specialWithdrawTips", out.special_withdraw_tips);
    common::detail::json::read(obj, "name", out.name);
    common::detail::json::read(obj, "resetAddressStatus", out.reset_address_status);
    common::detail::json::read(obj, "addressRegex", out.address_regex);
    common::detail::json::read(obj, "memoRegex", out.memo_regex);
    common::detail::json::read(obj, "withdrawFee", out.withdraw_fee);
    common::detail::json::read(obj, "withdrawMin", out.withdraw_min);
    common::detail::json::read(obj, "withdrawMax", out.withdraw_max);
    common::detail::json::read(obj, "withdrawInternalMin", out.withdraw_internal_min);
    common::detail::json::read(obj, "depositDust", out.deposit_dust);
    common::detail::json::read(obj, "minConfirm", out.min_confirm);
    common::detail::json::read(obj, "unLockConfirm", out.un_lock_confirm);
    common::detail::json::read(obj, "sameAddress", out.same_address);
    common::detail::json::read(obj, "withdrawTag", out.withdraw_tag);
    common::detail::json::read(obj, "estimatedArrivalTime", out.estimated_arrival_time);
    common::detail::json::read(obj, "busy", out.busy);
    common::detail::json::read(obj, "contractAddressUrl", out.contract_address_url);
    common::detail::json::read(obj, "contractAddress", out.contract_address);
    common::detail::json::read(obj, "denomination", out.denomination);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const AllCoinsInformationResponseInnerNetworkListInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "network", v.network);
    common::detail::json::write(obj, "coin", v.coin);
    common::detail::json::write(obj, "withdrawIntegerMultiple", v.withdraw_integer_multiple);
    common::detail::json::write(obj, "isDefault", v.is_default);
    common::detail::json::write(obj, "depositEnable", v.deposit_enable);
    common::detail::json::write(obj, "withdrawEnable", v.withdraw_enable);
    common::detail::json::write(obj, "depositDesc", v.deposit_desc);
    common::detail::json::write(obj, "withdrawDesc", v.withdraw_desc);
    common::detail::json::write(obj, "specialTips", v.special_tips);
    common::detail::json::write(obj, "specialWithdrawTips", v.special_withdraw_tips);
    common::detail::json::write(obj, "name", v.name);
    common::detail::json::write(obj, "resetAddressStatus", v.reset_address_status);
    common::detail::json::write(obj, "addressRegex", v.address_regex);
    common::detail::json::write(obj, "memoRegex", v.memo_regex);
    common::detail::json::write(obj, "withdrawFee", v.withdraw_fee);
    common::detail::json::write(obj, "withdrawMin", v.withdraw_min);
    common::detail::json::write(obj, "withdrawMax", v.withdraw_max);
    common::detail::json::write(obj, "withdrawInternalMin", v.withdraw_internal_min);
    common::detail::json::write(obj, "depositDust", v.deposit_dust);
    common::detail::json::write(obj, "minConfirm", v.min_confirm);
    common::detail::json::write(obj, "unLockConfirm", v.un_lock_confirm);
    common::detail::json::write(obj, "sameAddress", v.same_address);
    common::detail::json::write(obj, "withdrawTag", v.withdraw_tag);
    common::detail::json::write(obj, "estimatedArrivalTime", v.estimated_arrival_time);
    common::detail::json::write(obj, "busy", v.busy);
    common::detail::json::write(obj, "contractAddressUrl", v.contract_address_url);
    common::detail::json::write(obj, "contractAddress", v.contract_address);
    common::detail::json::write(obj, "denomination", v.denomination);
}

} // namespace binance::wallet::rest_api
