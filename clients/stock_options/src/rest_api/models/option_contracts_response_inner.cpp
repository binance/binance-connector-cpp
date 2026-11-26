//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/stock_options/rest_api/models/option_contracts_response_inner.hpp>

namespace binance::stock_options::rest_api {

OptionContractsResponseInner
tag_invoke(boost::json::value_to_tag<OptionContractsResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "OptionContractsResponseInner");
    OptionContractsResponseInner out;
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "contractType", out.contract_type);
    common::detail::json::read(obj, "strikePrice", out.strike_price);
    common::detail::json::read(obj, "multiplier", out.multiplier);
    common::detail::json::read(obj, "contractSize", out.contract_size);
    common::detail::json::read(obj, "expirationDate", out.expiration_date);
    common::detail::json::read(obj, "status", out.status);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const OptionContractsResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "contractType", v.contract_type);
    common::detail::json::write(obj, "strikePrice", v.strike_price);
    common::detail::json::write(obj, "multiplier", v.multiplier);
    common::detail::json::write(obj, "contractSize", v.contract_size);
    common::detail::json::write(obj, "expirationDate", v.expiration_date);
    common::detail::json::write(obj, "status", v.status);
}

} // namespace binance::stock_options::rest_api
