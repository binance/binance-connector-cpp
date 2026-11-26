//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/stock_options/rest_api/models/option_exchange_info_response_symbols_inner.hpp>

namespace binance::stock_options::rest_api {

OptionExchangeInfoResponseSymbolsInner
tag_invoke(boost::json::value_to_tag<OptionExchangeInfoResponseSymbolsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "OptionExchangeInfoResponseSymbolsInner");
    OptionExchangeInfoResponseSymbolsInner out;
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "underlyingSymbol", out.underlying_symbol);
    common::detail::json::read(obj, "rootSymbol", out.root_symbol);
    common::detail::json::read(obj, "contractType", out.contract_type);
    common::detail::json::read(obj, "status", out.status);
    common::detail::json::read(obj, "strikePrice", out.strike_price);
    common::detail::json::read(obj, "expirationDate", out.expiration_date);
    common::detail::json::read(obj, "multiplier", out.multiplier);
    common::detail::json::read(obj, "contractSize", out.contract_size);
    common::detail::json::read(obj, "tickSize", out.tick_size);
    common::detail::json::read(obj, "stepSize", out.step_size);
    common::detail::json::read(obj, "minQty", out.min_qty);
    common::detail::json::read(obj, "maxQty", out.max_qty);
    common::detail::json::read(obj, "minNotional", out.min_notional);
    common::detail::json::read(obj, "maxNotional", out.max_notional);
    common::detail::json::read(obj, "optionsLateClose", out.options_late_close);
    common::detail::json::read(obj, "pennyProgram", out.penny_program);
    common::detail::json::read(obj, "deliverables", out.deliverables);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const OptionExchangeInfoResponseSymbolsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "underlyingSymbol", v.underlying_symbol);
    common::detail::json::write(obj, "rootSymbol", v.root_symbol);
    common::detail::json::write(obj, "contractType", v.contract_type);
    common::detail::json::write(obj, "status", v.status);
    common::detail::json::write(obj, "strikePrice", v.strike_price);
    common::detail::json::write(obj, "expirationDate", v.expiration_date);
    common::detail::json::write(obj, "multiplier", v.multiplier);
    common::detail::json::write(obj, "contractSize", v.contract_size);
    common::detail::json::write(obj, "tickSize", v.tick_size);
    common::detail::json::write(obj, "stepSize", v.step_size);
    common::detail::json::write(obj, "minQty", v.min_qty);
    common::detail::json::write(obj, "maxQty", v.max_qty);
    common::detail::json::write(obj, "minNotional", v.min_notional);
    common::detail::json::write(obj, "maxNotional", v.max_notional);
    common::detail::json::write(obj, "optionsLateClose", v.options_late_close);
    common::detail::json::write(obj, "pennyProgram", v.penny_program);
    common::detail::json::write(obj, "deliverables", v.deliverables);
}

} // namespace binance::stock_options::rest_api
