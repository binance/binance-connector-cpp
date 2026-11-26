//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/alpha/rest_api/models/get_exchange_info_response_data_symbols_inner.hpp>
#include <binance/common/detail/json.hpp>

namespace binance::alpha::rest_api {

GetExchangeInfoResponseDataSymbolsInner
tag_invoke(boost::json::value_to_tag<GetExchangeInfoResponseDataSymbolsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetExchangeInfoResponseDataSymbolsInner");
    GetExchangeInfoResponseDataSymbolsInner out;
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "status", out.status);
    common::detail::json::read(obj, "baseAsset", out.base_asset);
    common::detail::json::read(obj, "quoteAsset", out.quote_asset);
    common::detail::json::read(obj, "pricePrecision", out.price_precision);
    common::detail::json::read(obj, "quantityPrecision", out.quantity_precision);
    common::detail::json::read(obj, "baseAssetPrecision", out.base_asset_precision);
    common::detail::json::read(obj, "quotePrecision", out.quote_precision);
    common::detail::json::read(obj, "filters", out.filters);
    common::detail::json::read(obj, "orderTypes", out.order_types);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetExchangeInfoResponseDataSymbolsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "status", v.status);
    common::detail::json::write(obj, "baseAsset", v.base_asset);
    common::detail::json::write(obj, "quoteAsset", v.quote_asset);
    common::detail::json::write(obj, "pricePrecision", v.price_precision);
    common::detail::json::write(obj, "quantityPrecision", v.quantity_precision);
    common::detail::json::write(obj, "baseAssetPrecision", v.base_asset_precision);
    common::detail::json::write(obj, "quotePrecision", v.quote_precision);
    common::detail::json::write(obj, "filters", v.filters);
    common::detail::json::write(obj, "orderTypes", v.order_types);
}

} // namespace binance::alpha::rest_api
