//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/top_trader_long_short_ratio_positions_response_inner.hpp>

namespace binance::derivatives_trading_coin_futures::rest_api {

TopTraderLongShortRatioPositionsResponseInner
tag_invoke(boost::json::value_to_tag<TopTraderLongShortRatioPositionsResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "TopTraderLongShortRatioPositionsResponseInner");
    TopTraderLongShortRatioPositionsResponseInner out;
    common::detail::json::read(obj, "pair", out.pair);
    common::detail::json::read(obj, "longShortRatio", out.long_short_ratio);
    common::detail::json::read(obj, "longPosition", out.long_position);
    common::detail::json::read(obj, "shortPosition", out.short_position);
    common::detail::json::read(obj, "timestamp", out.timestamp);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const TopTraderLongShortRatioPositionsResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "pair", v.pair);
    common::detail::json::write(obj, "longShortRatio", v.long_short_ratio);
    common::detail::json::write(obj, "longPosition", v.long_position);
    common::detail::json::write(obj, "shortPosition", v.short_position);
    common::detail::json::write(obj, "timestamp", v.timestamp);
}

} // namespace binance::derivatives_trading_coin_futures::rest_api
