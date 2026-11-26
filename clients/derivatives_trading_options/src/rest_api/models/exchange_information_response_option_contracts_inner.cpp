//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_options/rest_api/models/exchange_information_response_option_contracts_inner.hpp>

namespace binance::derivatives_trading_options::rest_api {

ExchangeInformationResponseOptionContractsInner
tag_invoke(boost::json::value_to_tag<ExchangeInformationResponseOptionContractsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "ExchangeInformationResponseOptionContractsInner");
    ExchangeInformationResponseOptionContractsInner out;
    common::detail::json::read(obj, "baseAsset", out.base_asset);
    common::detail::json::read(obj, "quoteAsset", out.quote_asset);
    common::detail::json::read(obj, "underlying", out.underlying);
    common::detail::json::read(obj, "settleAsset", out.settle_asset);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const ExchangeInformationResponseOptionContractsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "baseAsset", v.base_asset);
    common::detail::json::write(obj, "quoteAsset", v.quote_asset);
    common::detail::json::write(obj, "underlying", v.underlying);
    common::detail::json::write(obj, "settleAsset", v.settle_asset);
}

} // namespace binance::derivatives_trading_options::rest_api
