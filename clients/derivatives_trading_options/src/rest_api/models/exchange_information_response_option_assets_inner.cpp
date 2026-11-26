//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_options/rest_api/models/exchange_information_response_option_assets_inner.hpp>

namespace binance::derivatives_trading_options::rest_api {

ExchangeInformationResponseOptionAssetsInner
tag_invoke(boost::json::value_to_tag<ExchangeInformationResponseOptionAssetsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "ExchangeInformationResponseOptionAssetsInner");
    ExchangeInformationResponseOptionAssetsInner out;
    common::detail::json::read(obj, "name", out.name);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const ExchangeInformationResponseOptionAssetsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "name", v.name);
}

} // namespace binance::derivatives_trading_options::rest_api
