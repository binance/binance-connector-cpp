//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_options/rest_api/models/exchange_information_response_option_symbols_inner.hpp>

namespace binance::derivatives_trading_options::rest_api {

ExchangeInformationResponseOptionSymbolsInner
tag_invoke(boost::json::value_to_tag<ExchangeInformationResponseOptionSymbolsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "ExchangeInformationResponseOptionSymbolsInner");
    ExchangeInformationResponseOptionSymbolsInner out;
    common::detail::json::read(obj, "expiryDate", out.expiry_date);
    common::detail::json::read(obj, "filters", out.filters);
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "side", out.side);
    common::detail::json::read(obj, "strikePrice", out.strike_price);
    common::detail::json::read(obj, "underlying", out.underlying);
    common::detail::json::read(obj, "unit", out.unit);
    common::detail::json::read(obj, "liquidationFeeRate", out.liquidation_fee_rate);
    common::detail::json::read(obj, "minQty", out.min_qty);
    common::detail::json::read(obj, "maxQty", out.max_qty);
    common::detail::json::read(obj, "initialMargin", out.initial_margin);
    common::detail::json::read(obj, "maintenanceMargin", out.maintenance_margin);
    common::detail::json::read(obj, "minInitialMargin", out.min_initial_margin);
    common::detail::json::read(obj, "minMaintenanceMargin", out.min_maintenance_margin);
    common::detail::json::read(obj, "priceScale", out.price_scale);
    common::detail::json::read(obj, "quantityScale", out.quantity_scale);
    common::detail::json::read(obj, "quoteAsset", out.quote_asset);
    common::detail::json::read(obj, "contractType", out.contract_type);
    common::detail::json::read(obj, "underlyingType", out.underlying_type);
    common::detail::json::read(obj, "nakedSell", out.naked_sell);
    common::detail::json::read(obj, "status", out.status);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const ExchangeInformationResponseOptionSymbolsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "expiryDate", v.expiry_date);
    common::detail::json::write(obj, "filters", v.filters);
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "side", v.side);
    common::detail::json::write(obj, "strikePrice", v.strike_price);
    common::detail::json::write(obj, "underlying", v.underlying);
    common::detail::json::write(obj, "unit", v.unit);
    common::detail::json::write(obj, "liquidationFeeRate", v.liquidation_fee_rate);
    common::detail::json::write(obj, "minQty", v.min_qty);
    common::detail::json::write(obj, "maxQty", v.max_qty);
    common::detail::json::write(obj, "initialMargin", v.initial_margin);
    common::detail::json::write(obj, "maintenanceMargin", v.maintenance_margin);
    common::detail::json::write(obj, "minInitialMargin", v.min_initial_margin);
    common::detail::json::write(obj, "minMaintenanceMargin", v.min_maintenance_margin);
    common::detail::json::write(obj, "priceScale", v.price_scale);
    common::detail::json::write(obj, "quantityScale", v.quantity_scale);
    common::detail::json::write(obj, "quoteAsset", v.quote_asset);
    common::detail::json::write(obj, "contractType", v.contract_type);
    common::detail::json::write(obj, "underlyingType", v.underlying_type);
    common::detail::json::write(obj, "nakedSell", v.naked_sell);
    common::detail::json::write(obj, "status", v.status);
}

} // namespace binance::derivatives_trading_options::rest_api
