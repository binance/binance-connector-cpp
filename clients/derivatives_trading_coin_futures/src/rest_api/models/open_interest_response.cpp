//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/open_interest_response.hpp>

namespace binance::derivatives_trading_coin_futures::rest_api {

OpenInterestResponse tag_invoke(boost::json::value_to_tag<OpenInterestResponse> /*tag*/,
                                const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "OpenInterestResponse");
    OpenInterestResponse out;
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "pair", out.pair);
    common::detail::json::read(obj, "openInterest", out.open_interest);
    common::detail::json::read(obj, "contractType", out.contract_type);
    common::detail::json::read(obj, "time", out.time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const OpenInterestResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "pair", v.pair);
    common::detail::json::write(obj, "openInterest", v.open_interest);
    common::detail::json::write(obj, "contractType", v.contract_type);
    common::detail::json::write(obj, "time", v.time);
}

} // namespace binance::derivatives_trading_coin_futures::rest_api
