//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/wallet/rest_api/models/asset_detail_response_sky.hpp>

namespace binance::wallet::rest_api {

AssetDetailResponseSKY tag_invoke(boost::json::value_to_tag<AssetDetailResponseSKY> /*tag*/,
                                  const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "AssetDetailResponseSKY");
    AssetDetailResponseSKY out;
    common::detail::json::read(obj, "minWithdrawAmount", out.min_withdraw_amount);
    common::detail::json::read(obj, "depositStatus", out.deposit_status);
    common::detail::json::read(obj, "withdrawFee", out.withdraw_fee);
    common::detail::json::read(obj, "withdrawStatus", out.withdraw_status);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const AssetDetailResponseSKY& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "minWithdrawAmount", v.min_withdraw_amount);
    common::detail::json::write(obj, "depositStatus", v.deposit_status);
    common::detail::json::write(obj, "withdrawFee", v.withdraw_fee);
    common::detail::json::write(obj, "withdrawStatus", v.withdraw_status);
}

} // namespace binance::wallet::rest_api
