//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/rest_api/models/exchange_info_response_symbols_inner.hpp>

namespace binance::spot::rest_api {

ExchangeInfoResponseSymbolsInner
tag_invoke(boost::json::value_to_tag<ExchangeInfoResponseSymbolsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "ExchangeInfoResponseSymbolsInner");
    ExchangeInfoResponseSymbolsInner out;
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "status", out.status);
    common::detail::json::read(obj, "baseAsset", out.base_asset);
    common::detail::json::read(obj, "baseAssetPrecision", out.base_asset_precision);
    common::detail::json::read(obj, "quoteAsset", out.quote_asset);
    common::detail::json::read(obj, "quotePrecision", out.quote_precision);
    common::detail::json::read(obj, "quoteAssetPrecision", out.quote_asset_precision);
    common::detail::json::read(obj, "baseCommissionPrecision", out.base_commission_precision);
    common::detail::json::read(obj, "quoteCommissionPrecision", out.quote_commission_precision);
    common::detail::json::read(obj, "orderTypes", out.order_types);
    common::detail::json::read(obj, "icebergAllowed", out.iceberg_allowed);
    common::detail::json::read(obj, "ocoAllowed", out.oco_allowed);
    common::detail::json::read(obj, "otoAllowed", out.oto_allowed);
    common::detail::json::read(obj, "opoAllowed", out.opo_allowed);
    common::detail::json::read(obj, "quoteOrderQtyMarketAllowed",
                               out.quote_order_qty_market_allowed);
    common::detail::json::read(obj, "allowTrailingStop", out.allow_trailing_stop);
    common::detail::json::read(obj, "cancelReplaceAllowed", out.cancel_replace_allowed);
    common::detail::json::read(obj, "amendAllowed", out.amend_allowed);
    common::detail::json::read(obj, "pegInstructionsAllowed", out.peg_instructions_allowed);
    common::detail::json::read(obj, "marketQuoteNotionalLimitAllowed",
                               out.market_quote_notional_limit_allowed);
    common::detail::json::read(obj, "limitQuoteNotionalLimitAllowed",
                               out.limit_quote_notional_limit_allowed);
    common::detail::json::read(obj, "isSpotTradingAllowed", out.is_spot_trading_allowed);
    common::detail::json::read(obj, "isMarginTradingAllowed", out.is_margin_trading_allowed);
    common::detail::json::read(obj, "filters", out.filters);
    common::detail::json::read(obj, "permissions", out.permissions);
    common::detail::json::read(obj, "permissionSets", out.permission_sets);
    common::detail::json::read(obj, "defaultSelfTradePreventionMode",
                               out.default_self_trade_prevention_mode);
    common::detail::json::read(obj, "allowedSelfTradePreventionModes",
                               out.allowed_self_trade_prevention_modes);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const ExchangeInfoResponseSymbolsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "status", v.status);
    common::detail::json::write(obj, "baseAsset", v.base_asset);
    common::detail::json::write(obj, "baseAssetPrecision", v.base_asset_precision);
    common::detail::json::write(obj, "quoteAsset", v.quote_asset);
    common::detail::json::write(obj, "quotePrecision", v.quote_precision);
    common::detail::json::write(obj, "quoteAssetPrecision", v.quote_asset_precision);
    common::detail::json::write(obj, "baseCommissionPrecision", v.base_commission_precision);
    common::detail::json::write(obj, "quoteCommissionPrecision", v.quote_commission_precision);
    common::detail::json::write(obj, "orderTypes", v.order_types);
    common::detail::json::write(obj, "icebergAllowed", v.iceberg_allowed);
    common::detail::json::write(obj, "ocoAllowed", v.oco_allowed);
    common::detail::json::write(obj, "otoAllowed", v.oto_allowed);
    common::detail::json::write(obj, "opoAllowed", v.opo_allowed);
    common::detail::json::write(obj, "quoteOrderQtyMarketAllowed",
                                v.quote_order_qty_market_allowed);
    common::detail::json::write(obj, "allowTrailingStop", v.allow_trailing_stop);
    common::detail::json::write(obj, "cancelReplaceAllowed", v.cancel_replace_allowed);
    common::detail::json::write(obj, "amendAllowed", v.amend_allowed);
    common::detail::json::write(obj, "pegInstructionsAllowed", v.peg_instructions_allowed);
    common::detail::json::write(obj, "marketQuoteNotionalLimitAllowed",
                                v.market_quote_notional_limit_allowed);
    common::detail::json::write(obj, "limitQuoteNotionalLimitAllowed",
                                v.limit_quote_notional_limit_allowed);
    common::detail::json::write(obj, "isSpotTradingAllowed", v.is_spot_trading_allowed);
    common::detail::json::write(obj, "isMarginTradingAllowed", v.is_margin_trading_allowed);
    common::detail::json::write(obj, "filters", v.filters);
    common::detail::json::write(obj, "permissions", v.permissions);
    common::detail::json::write(obj, "permissionSets", v.permission_sets);
    common::detail::json::write(obj, "defaultSelfTradePreventionMode",
                                v.default_self_trade_prevention_mode);
    common::detail::json::write(obj, "allowedSelfTradePreventionModes",
                                v.allowed_self_trade_prevention_modes);
}

} // namespace binance::spot::rest_api
