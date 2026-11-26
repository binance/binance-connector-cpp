//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_options/rest_api/models/user_commission_response_commissions_inner.hpp>

namespace binance::derivatives_trading_options::rest_api {

UserCommissionResponseCommissionsInner
tag_invoke(boost::json::value_to_tag<UserCommissionResponseCommissionsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "UserCommissionResponseCommissionsInner");
    UserCommissionResponseCommissionsInner out;
    common::detail::json::read(obj, "underlying", out.underlying);
    common::detail::json::read(obj, "makerFee", out.maker_fee);
    common::detail::json::read(obj, "takerFee", out.taker_fee);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const UserCommissionResponseCommissionsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "underlying", v.underlying);
    common::detail::json::write(obj, "makerFee", v.maker_fee);
    common::detail::json::write(obj, "takerFee", v.taker_fee);
}

} // namespace binance::derivatives_trading_options::rest_api
