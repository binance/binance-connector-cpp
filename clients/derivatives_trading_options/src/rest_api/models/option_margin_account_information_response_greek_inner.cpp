//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_options/rest_api/models/option_margin_account_information_response_greek_inner.hpp>

namespace binance::derivatives_trading_options::rest_api {

OptionMarginAccountInformationResponseGreekInner
tag_invoke(boost::json::value_to_tag<OptionMarginAccountInformationResponseGreekInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "OptionMarginAccountInformationResponseGreekInner");
    OptionMarginAccountInformationResponseGreekInner out;
    common::detail::json::read(obj, "underlying", out.underlying);
    common::detail::json::read(obj, "delta", out.delta);
    common::detail::json::read(obj, "gamma", out.gamma);
    common::detail::json::read(obj, "theta", out.theta);
    common::detail::json::read(obj, "vega", out.vega);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const OptionMarginAccountInformationResponseGreekInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "underlying", v.underlying);
    common::detail::json::write(obj, "delta", v.delta);
    common::detail::json::write(obj, "gamma", v.gamma);
    common::detail::json::write(obj, "theta", v.theta);
    common::detail::json::write(obj, "vega", v.vega);
}

} // namespace binance::derivatives_trading_options::rest_api
