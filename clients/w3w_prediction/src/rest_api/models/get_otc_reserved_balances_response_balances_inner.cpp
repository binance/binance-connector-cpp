//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/w3w_prediction/rest_api/models/get_otc_reserved_balances_response_balances_inner.hpp>

namespace binance::w3w_prediction::rest_api {

GetOtcReservedBalancesResponseBalancesInner
tag_invoke(boost::json::value_to_tag<GetOtcReservedBalancesResponseBalancesInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetOtcReservedBalancesResponseBalancesInner");
    GetOtcReservedBalancesResponseBalancesInner out;
    common::detail::json::read(obj, "type", out.type);
    common::detail::json::read(obj, "tokenId", out.token_id);
    common::detail::json::read(obj, "amount", out.amount);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetOtcReservedBalancesResponseBalancesInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "type", v.type);
    common::detail::json::write(obj, "tokenId", v.token_id);
    common::detail::json::write(obj, "amount", v.amount);
}

} // namespace binance::w3w_prediction::rest_api
