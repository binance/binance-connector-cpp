//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/staking/rest_api/models/wrap_beth_response.hpp>

namespace binance::staking::rest_api {

WrapBethResponse tag_invoke(boost::json::value_to_tag<WrapBethResponse> /*tag*/,
                            const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "WrapBethResponse");
    WrapBethResponse out;
    common::detail::json::read(obj, "success", out.success);
    common::detail::json::read(obj, "wbethAmount", out.wbeth_amount);
    common::detail::json::read(obj, "exchangeRate", out.exchange_rate);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const WrapBethResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "success", v.success);
    common::detail::json::write(obj, "wbethAmount", v.wbeth_amount);
    common::detail::json::write(obj, "exchangeRate", v.exchange_rate);
}

} // namespace binance::staking::rest_api
