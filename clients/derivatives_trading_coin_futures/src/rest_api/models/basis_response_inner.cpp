//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/basis_response_inner.hpp>

namespace binance::derivatives_trading_coin_futures::rest_api {

BasisResponseInner tag_invoke(boost::json::value_to_tag<BasisResponseInner> /*tag*/,
                              const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "BasisResponseInner");
    BasisResponseInner out;
    common::detail::json::read(obj, "indexPrice", out.index_price);
    common::detail::json::read(obj, "contractType", out.contract_type);
    common::detail::json::read(obj, "basisRate", out.basis_rate);
    common::detail::json::read(obj, "futuresPrice", out.futures_price);
    common::detail::json::read(obj, "annualizedBasisRate", out.annualized_basis_rate);
    common::detail::json::read(obj, "basis", out.basis);
    common::detail::json::read(obj, "pair", out.pair);
    common::detail::json::read(obj, "timestamp", out.timestamp);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const BasisResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "indexPrice", v.index_price);
    common::detail::json::write(obj, "contractType", v.contract_type);
    common::detail::json::write(obj, "basisRate", v.basis_rate);
    common::detail::json::write(obj, "futuresPrice", v.futures_price);
    common::detail::json::write(obj, "annualizedBasisRate", v.annualized_basis_rate);
    common::detail::json::write(obj, "basis", v.basis);
    common::detail::json::write(obj, "pair", v.pair);
    common::detail::json::write(obj, "timestamp", v.timestamp);
}

} // namespace binance::derivatives_trading_coin_futures::rest_api
