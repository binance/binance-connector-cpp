//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/websocket_api/models/account_commission_response_result_discount.hpp>

namespace binance::spot::websocket_api {

AccountCommissionResponseResultDiscount
tag_invoke(boost::json::value_to_tag<AccountCommissionResponseResultDiscount> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "AccountCommissionResponseResultDiscount");
    AccountCommissionResponseResultDiscount out;
    common::detail::json::read(obj, "enabledForAccount", out.enabled_for_account);
    common::detail::json::read(obj, "enabledForSymbol", out.enabled_for_symbol);
    common::detail::json::read(obj, "discountAsset", out.discount_asset);
    common::detail::json::read(obj, "discount", out.discount);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const AccountCommissionResponseResultDiscount& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "enabledForAccount", v.enabled_for_account);
    common::detail::json::write(obj, "enabledForSymbol", v.enabled_for_symbol);
    common::detail::json::write(obj, "discountAsset", v.discount_asset);
    common::detail::json::write(obj, "discount", v.discount);
}

} // namespace binance::spot::websocket_api
