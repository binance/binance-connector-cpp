//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/exchange_information_response_assets_inner.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

ExchangeInformationResponseAssetsInner
tag_invoke(boost::json::value_to_tag<ExchangeInformationResponseAssetsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "ExchangeInformationResponseAssetsInner");
    ExchangeInformationResponseAssetsInner out;
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "marginAvailable", out.margin_available);
    common::detail::json::read(obj, "autoAssetExchange", out.auto_asset_exchange);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const ExchangeInformationResponseAssetsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "marginAvailable", v.margin_available);
    common::detail::json::write(obj, "autoAssetExchange", v.auto_asset_exchange);
}

} // namespace binance::derivatives_trading_usds_futures::rest_api
