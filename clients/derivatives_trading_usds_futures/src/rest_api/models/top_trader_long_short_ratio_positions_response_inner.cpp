//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/top_trader_long_short_ratio_positions_response_inner.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

TopTraderLongShortRatioPositionsResponseInner
tag_invoke(boost::json::value_to_tag<TopTraderLongShortRatioPositionsResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "TopTraderLongShortRatioPositionsResponseInner");
    TopTraderLongShortRatioPositionsResponseInner out;
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "longShortRatio", out.long_short_ratio);
    common::detail::json::read(obj, "longAccount", out.long_account);
    common::detail::json::read(obj, "shortAccount", out.short_account);
    common::detail::json::read(obj, "timestamp", out.timestamp);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const TopTraderLongShortRatioPositionsResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "longShortRatio", v.long_short_ratio);
    common::detail::json::write(obj, "longAccount", v.long_account);
    common::detail::json::write(obj, "shortAccount", v.short_account);
    common::detail::json::write(obj, "timestamp", v.timestamp);
}

} // namespace binance::derivatives_trading_usds_futures::rest_api
