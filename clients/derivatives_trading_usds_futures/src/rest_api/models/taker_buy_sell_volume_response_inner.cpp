//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/taker_buy_sell_volume_response_inner.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

TakerBuySellVolumeResponseInner
tag_invoke(boost::json::value_to_tag<TakerBuySellVolumeResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "TakerBuySellVolumeResponseInner");
    TakerBuySellVolumeResponseInner out;
    common::detail::json::read(obj, "buySellRatio", out.buy_sell_ratio);
    common::detail::json::read(obj, "buyVol", out.buy_vol);
    common::detail::json::read(obj, "sellVol", out.sell_vol);
    common::detail::json::read(obj, "timestamp", out.timestamp);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const TakerBuySellVolumeResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "buySellRatio", v.buy_sell_ratio);
    common::detail::json::write(obj, "buyVol", v.buy_vol);
    common::detail::json::write(obj, "sellVol", v.sell_vol);
    common::detail::json::write(obj, "timestamp", v.timestamp);
}

} // namespace binance::derivatives_trading_usds_futures::rest_api
