//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/websocket_api/models/ticker24hr_response1_result.hpp>

namespace binance::spot::websocket_api {

Ticker24hrResponse1Result tag_invoke(boost::json::value_to_tag<Ticker24hrResponse1Result> /*tag*/,
                                     const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "Ticker24hrResponse1Result");
    Ticker24hrResponse1Result out;
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "priceChange", out.price_change);
    common::detail::json::read(obj, "priceChangePercent", out.price_change_percent);
    common::detail::json::read(obj, "weightedAvgPrice", out.weighted_avg_price);
    common::detail::json::read(obj, "prevClosePrice", out.prev_close_price);
    common::detail::json::read(obj, "lastPrice", out.last_price);
    common::detail::json::read(obj, "lastQty", out.last_qty);
    common::detail::json::read(obj, "bidPrice", out.bid_price);
    common::detail::json::read(obj, "bidQty", out.bid_qty);
    common::detail::json::read(obj, "askPrice", out.ask_price);
    common::detail::json::read(obj, "askQty", out.ask_qty);
    common::detail::json::read(obj, "openPrice", out.open_price);
    common::detail::json::read(obj, "highPrice", out.high_price);
    common::detail::json::read(obj, "lowPrice", out.low_price);
    common::detail::json::read(obj, "volume", out.volume);
    common::detail::json::read(obj, "quoteVolume", out.quote_volume);
    common::detail::json::read(obj, "openTime", out.open_time);
    common::detail::json::read(obj, "closeTime", out.close_time);
    common::detail::json::read(obj, "firstId", out.first_id);
    common::detail::json::read(obj, "lastId", out.last_id);
    common::detail::json::read(obj, "count", out.count);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const Ticker24hrResponse1Result& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "priceChange", v.price_change);
    common::detail::json::write(obj, "priceChangePercent", v.price_change_percent);
    common::detail::json::write(obj, "weightedAvgPrice", v.weighted_avg_price);
    common::detail::json::write(obj, "prevClosePrice", v.prev_close_price);
    common::detail::json::write(obj, "lastPrice", v.last_price);
    common::detail::json::write(obj, "lastQty", v.last_qty);
    common::detail::json::write(obj, "bidPrice", v.bid_price);
    common::detail::json::write(obj, "bidQty", v.bid_qty);
    common::detail::json::write(obj, "askPrice", v.ask_price);
    common::detail::json::write(obj, "askQty", v.ask_qty);
    common::detail::json::write(obj, "openPrice", v.open_price);
    common::detail::json::write(obj, "highPrice", v.high_price);
    common::detail::json::write(obj, "lowPrice", v.low_price);
    common::detail::json::write(obj, "volume", v.volume);
    common::detail::json::write(obj, "quoteVolume", v.quote_volume);
    common::detail::json::write(obj, "openTime", v.open_time);
    common::detail::json::write(obj, "closeTime", v.close_time);
    common::detail::json::write(obj, "firstId", v.first_id);
    common::detail::json::write(obj, "lastId", v.last_id);
    common::detail::json::write(obj, "count", v.count);
}

} // namespace binance::spot::websocket_api
