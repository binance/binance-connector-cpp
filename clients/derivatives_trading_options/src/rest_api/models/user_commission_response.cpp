//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_options/rest_api/models/user_commission_response.hpp>

namespace binance::derivatives_trading_options::rest_api {

UserCommissionResponse tag_invoke(boost::json::value_to_tag<UserCommissionResponse> /*tag*/,
                                  const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "UserCommissionResponse");
    UserCommissionResponse out;
    common::detail::json::read(obj, "commissions", out.commissions);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const UserCommissionResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "commissions", v.commissions);
}

} // namespace binance::derivatives_trading_options::rest_api
