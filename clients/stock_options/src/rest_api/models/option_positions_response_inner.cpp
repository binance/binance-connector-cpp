//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/stock_options/rest_api/models/option_positions_response_inner.hpp>

namespace binance::stock_options::rest_api {

OptionPositionsResponseInner
tag_invoke(boost::json::value_to_tag<OptionPositionsResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "OptionPositionsResponseInner");
    OptionPositionsResponseInner out;
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "underlyingSymbol", out.underlying_symbol);
    common::detail::json::read(obj, "contractType", out.contract_type);
    common::detail::json::read(obj, "side", out.side);
    common::detail::json::read(obj, "free", out.free);
    common::detail::json::read(obj, "locked", out.locked);
    common::detail::json::read(obj, "strikePrice", out.strike_price);
    common::detail::json::read(obj, "expirationDate", out.expiration_date);
    common::detail::json::read(obj, "multiplier", out.multiplier);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const OptionPositionsResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "underlyingSymbol", v.underlying_symbol);
    common::detail::json::write(obj, "contractType", v.contract_type);
    common::detail::json::write(obj, "side", v.side);
    common::detail::json::write(obj, "free", v.free);
    common::detail::json::write(obj, "locked", v.locked);
    common::detail::json::write(obj, "strikePrice", v.strike_price);
    common::detail::json::write(obj, "expirationDate", v.expiration_date);
    common::detail::json::write(obj, "multiplier", v.multiplier);
}

} // namespace binance::stock_options::rest_api
