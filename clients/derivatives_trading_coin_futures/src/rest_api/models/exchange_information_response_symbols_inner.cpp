//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/exchange_information_response_symbols_inner.hpp>

namespace binance::derivatives_trading_coin_futures::rest_api {

ExchangeInformationResponseSymbolsInner
tag_invoke(boost::json::value_to_tag<ExchangeInformationResponseSymbolsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "ExchangeInformationResponseSymbolsInner");
    ExchangeInformationResponseSymbolsInner out;
    common::detail::json::read(obj, "filters", out.filters);
    common::detail::json::read(obj, "orderTypes", out.order_types);
    common::detail::json::read(obj, "timeInForce", out.time_in_force);
    common::detail::json::read(obj, "liquidationFee", out.liquidation_fee);
    common::detail::json::read(obj, "marketTakeBound", out.market_take_bound);
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "pair", out.pair);
    common::detail::json::read(obj, "contractType", out.contract_type);
    common::detail::json::read(obj, "deliveryDate", out.delivery_date);
    common::detail::json::read(obj, "onboardDate", out.onboard_date);
    common::detail::json::read(obj, "contractStatus", out.contract_status);
    common::detail::json::read(obj, "contractSize", out.contract_size);
    common::detail::json::read(obj, "quoteAsset", out.quote_asset);
    common::detail::json::read(obj, "baseAsset", out.base_asset);
    common::detail::json::read(obj, "marginAsset", out.margin_asset);
    common::detail::json::read(obj, "pricePrecision", out.price_precision);
    common::detail::json::read(obj, "quantityPrecision", out.quantity_precision);
    common::detail::json::read(obj, "baseAssetPrecision", out.base_asset_precision);
    common::detail::json::read(obj, "quotePrecision", out.quote_precision);
    common::detail::json::read(obj, "equalQtyPrecision", out.equal_qty_precision);
    common::detail::json::read(obj, "triggerProtect", out.trigger_protect);
    common::detail::json::read(obj, "maintMarginPercent", out.maint_margin_percent);
    common::detail::json::read(obj, "requiredMarginPercent", out.required_margin_percent);
    common::detail::json::read(obj, "underlyingType", out.underlying_type);
    common::detail::json::read(obj, "underlyingSubType", out.underlying_sub_type);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const ExchangeInformationResponseSymbolsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "filters", v.filters);
    common::detail::json::write(obj, "orderTypes", v.order_types);
    common::detail::json::write(obj, "timeInForce", v.time_in_force);
    common::detail::json::write(obj, "liquidationFee", v.liquidation_fee);
    common::detail::json::write(obj, "marketTakeBound", v.market_take_bound);
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "pair", v.pair);
    common::detail::json::write(obj, "contractType", v.contract_type);
    common::detail::json::write(obj, "deliveryDate", v.delivery_date);
    common::detail::json::write(obj, "onboardDate", v.onboard_date);
    common::detail::json::write(obj, "contractStatus", v.contract_status);
    common::detail::json::write(obj, "contractSize", v.contract_size);
    common::detail::json::write(obj, "quoteAsset", v.quote_asset);
    common::detail::json::write(obj, "baseAsset", v.base_asset);
    common::detail::json::write(obj, "marginAsset", v.margin_asset);
    common::detail::json::write(obj, "pricePrecision", v.price_precision);
    common::detail::json::write(obj, "quantityPrecision", v.quantity_precision);
    common::detail::json::write(obj, "baseAssetPrecision", v.base_asset_precision);
    common::detail::json::write(obj, "quotePrecision", v.quote_precision);
    common::detail::json::write(obj, "equalQtyPrecision", v.equal_qty_precision);
    common::detail::json::write(obj, "triggerProtect", v.trigger_protect);
    common::detail::json::write(obj, "maintMarginPercent", v.maint_margin_percent);
    common::detail::json::write(obj, "requiredMarginPercent", v.required_margin_percent);
    common::detail::json::write(obj, "underlyingType", v.underlying_type);
    common::detail::json::write(obj, "underlyingSubType", v.underlying_sub_type);
}

} // namespace binance::derivatives_trading_coin_futures::rest_api
