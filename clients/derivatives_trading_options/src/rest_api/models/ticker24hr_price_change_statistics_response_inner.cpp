//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_options/rest_api/models/ticker24hr_price_change_statistics_response_inner.hpp>

namespace binance::derivatives_trading_options::rest_api {

Ticker24hrPriceChangeStatisticsResponseInner
tag_invoke(boost::json::value_to_tag<Ticker24hrPriceChangeStatisticsResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "Ticker24hrPriceChangeStatisticsResponseInner");
    Ticker24hrPriceChangeStatisticsResponseInner out;
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "priceChange", out.price_change);
    common::detail::json::read(obj, "priceChangePercent", out.price_change_percent);
    common::detail::json::read(obj, "lastPrice", out.last_price);
    common::detail::json::read(obj, "lastQty", out.last_qty);
    common::detail::json::read(obj, "open", out.open);
    common::detail::json::read(obj, "high", out.high);
    common::detail::json::read(obj, "low", out.low);
    common::detail::json::read(obj, "volume", out.volume);
    common::detail::json::read(obj, "amount", out.amount);
    common::detail::json::read(obj, "bidPrice", out.bid_price);
    common::detail::json::read(obj, "askPrice", out.ask_price);
    common::detail::json::read(obj, "openTime", out.open_time);
    common::detail::json::read(obj, "closeTime", out.close_time);
    common::detail::json::read(obj, "firstTradeId", out.first_trade_id);
    common::detail::json::read(obj, "tradeCount", out.trade_count);
    common::detail::json::read(obj, "strikePrice", out.strike_price);
    common::detail::json::read(obj, "exercisePrice", out.exercise_price);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const Ticker24hrPriceChangeStatisticsResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "priceChange", v.price_change);
    common::detail::json::write(obj, "priceChangePercent", v.price_change_percent);
    common::detail::json::write(obj, "lastPrice", v.last_price);
    common::detail::json::write(obj, "lastQty", v.last_qty);
    common::detail::json::write(obj, "open", v.open);
    common::detail::json::write(obj, "high", v.high);
    common::detail::json::write(obj, "low", v.low);
    common::detail::json::write(obj, "volume", v.volume);
    common::detail::json::write(obj, "amount", v.amount);
    common::detail::json::write(obj, "bidPrice", v.bid_price);
    common::detail::json::write(obj, "askPrice", v.ask_price);
    common::detail::json::write(obj, "openTime", v.open_time);
    common::detail::json::write(obj, "closeTime", v.close_time);
    common::detail::json::write(obj, "firstTradeId", v.first_trade_id);
    common::detail::json::write(obj, "tradeCount", v.trade_count);
    common::detail::json::write(obj, "strikePrice", v.strike_price);
    common::detail::json::write(obj, "exercisePrice", v.exercise_price);
}

} // namespace binance::derivatives_trading_options::rest_api
