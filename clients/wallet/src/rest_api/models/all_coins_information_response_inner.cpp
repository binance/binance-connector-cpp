//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/wallet/rest_api/models/all_coins_information_response_inner.hpp>

namespace binance::wallet::rest_api {

AllCoinsInformationResponseInner
tag_invoke(boost::json::value_to_tag<AllCoinsInformationResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "AllCoinsInformationResponseInner");
    AllCoinsInformationResponseInner out;
    common::detail::json::read(obj, "coin", out.coin);
    common::detail::json::read(obj, "depositAllEnable", out.deposit_all_enable);
    common::detail::json::read(obj, "withdrawAllEnable", out.withdraw_all_enable);
    common::detail::json::read(obj, "name", out.name);
    common::detail::json::read(obj, "free", out.free);
    common::detail::json::read(obj, "locked", out.locked);
    common::detail::json::read(obj, "freeze", out.freeze);
    common::detail::json::read(obj, "withdrawing", out.withdrawing);
    common::detail::json::read(obj, "ipoing", out.ipoing);
    common::detail::json::read(obj, "ipoable", out.ipoable);
    common::detail::json::read(obj, "storage", out.storage);
    common::detail::json::read(obj, "isLegalMoney", out.is_legal_money);
    common::detail::json::read(obj, "trading", out.trading);
    common::detail::json::read(obj, "networkList", out.network_list);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const AllCoinsInformationResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "coin", v.coin);
    common::detail::json::write(obj, "depositAllEnable", v.deposit_all_enable);
    common::detail::json::write(obj, "withdrawAllEnable", v.withdraw_all_enable);
    common::detail::json::write(obj, "name", v.name);
    common::detail::json::write(obj, "free", v.free);
    common::detail::json::write(obj, "locked", v.locked);
    common::detail::json::write(obj, "freeze", v.freeze);
    common::detail::json::write(obj, "withdrawing", v.withdrawing);
    common::detail::json::write(obj, "ipoing", v.ipoing);
    common::detail::json::write(obj, "ipoable", v.ipoable);
    common::detail::json::write(obj, "storage", v.storage);
    common::detail::json::write(obj, "isLegalMoney", v.is_legal_money);
    common::detail::json::write(obj, "trading", v.trading);
    common::detail::json::write(obj, "networkList", v.network_list);
}

} // namespace binance::wallet::rest_api
