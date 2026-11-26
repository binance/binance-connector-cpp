//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/notional_bracket_for_pair_response_inner.hpp>

namespace binance::derivatives_trading_coin_futures::rest_api {

NotionalBracketForPairResponseInner
tag_invoke(boost::json::value_to_tag<NotionalBracketForPairResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "NotionalBracketForPairResponseInner");
    NotionalBracketForPairResponseInner out;
    common::detail::json::read(obj, "pair", out.pair);
    common::detail::json::read(obj, "brackets", out.brackets);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const NotionalBracketForPairResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "pair", v.pair);
    common::detail::json::write(obj, "brackets", v.brackets);
}

} // namespace binance::derivatives_trading_coin_futures::rest_api
