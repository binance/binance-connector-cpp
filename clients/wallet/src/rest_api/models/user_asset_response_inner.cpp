//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/wallet/rest_api/models/user_asset_response_inner.hpp>

namespace binance::wallet::rest_api {

UserAssetResponseInner tag_invoke(boost::json::value_to_tag<UserAssetResponseInner> /*tag*/,
                                  const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "UserAssetResponseInner");
    UserAssetResponseInner out;
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "free", out.free);
    common::detail::json::read(obj, "locked", out.locked);
    common::detail::json::read(obj, "freeze", out.freeze);
    common::detail::json::read(obj, "withdrawing", out.withdrawing);
    common::detail::json::read(obj, "ipoable", out.ipoable);
    common::detail::json::read(obj, "btcValuation", out.btc_valuation);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const UserAssetResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "free", v.free);
    common::detail::json::write(obj, "locked", v.locked);
    common::detail::json::write(obj, "freeze", v.freeze);
    common::detail::json::write(obj, "withdrawing", v.withdrawing);
    common::detail::json::write(obj, "ipoable", v.ipoable);
    common::detail::json::write(obj, "btcValuation", v.btc_valuation);
}

} // namespace binance::wallet::rest_api
