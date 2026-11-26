//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/taker_buy_sell_volume_response_inner.hpp>

namespace binance::derivatives_trading_coin_futures::rest_api {

TakerBuySellVolumeResponseInner
tag_invoke(boost::json::value_to_tag<TakerBuySellVolumeResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "TakerBuySellVolumeResponseInner");
    TakerBuySellVolumeResponseInner out;
    common::detail::json::read(obj, "pair", out.pair);
    common::detail::json::read(obj, "contractType", out.contract_type);
    common::detail::json::read(obj, "takerBuyVol", out.taker_buy_vol);
    common::detail::json::read(obj, "takerSellVol", out.taker_sell_vol);
    common::detail::json::read(obj, "takerBuyVolValue", out.taker_buy_vol_value);
    common::detail::json::read(obj, "takerSellVolValue", out.taker_sell_vol_value);
    common::detail::json::read(obj, "timestamp", out.timestamp);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const TakerBuySellVolumeResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "pair", v.pair);
    common::detail::json::write(obj, "contractType", v.contract_type);
    common::detail::json::write(obj, "takerBuyVol", v.taker_buy_vol);
    common::detail::json::write(obj, "takerSellVol", v.taker_sell_vol);
    common::detail::json::write(obj, "takerBuyVolValue", v.taker_buy_vol_value);
    common::detail::json::write(obj, "takerSellVolValue", v.taker_sell_vol_value);
    common::detail::json::write(obj, "timestamp", v.timestamp);
}

} // namespace binance::derivatives_trading_coin_futures::rest_api
