//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/stocks/websocket_streams/models/price_stream_response_rates_inner.hpp>

namespace binance::stocks::websocket_streams {

PriceStreamResponseRatesInner
tag_invoke(boost::json::value_to_tag<PriceStreamResponseRatesInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "PriceStreamResponseRatesInner");
    PriceStreamResponseRatesInner out;
    common::detail::json::read(obj, "s", out.s);
    common::detail::json::read(obj, "ac", out.ac);
    common::detail::json::read(obj, "p", out.p);
    common::detail::json::read(obj, "t", out.t);
    common::detail::json::read(obj, "pc", out.pc);
    common::detail::json::read(obj, "tc", out.tc);
    common::detail::json::read(obj, "lrc", out.lrc);
    common::detail::json::read(obj, "prc", out.prc);
    common::detail::json::read(obj, "mp", out.mp);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const PriceStreamResponseRatesInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "s", v.s);
    common::detail::json::write(obj, "ac", v.ac);
    common::detail::json::write(obj, "p", v.p);
    common::detail::json::write(obj, "t", v.t);
    common::detail::json::write(obj, "pc", v.pc);
    common::detail::json::write(obj, "tc", v.tc);
    common::detail::json::write(obj, "lrc", v.lrc);
    common::detail::json::write(obj, "prc", v.prc);
    common::detail::json::write(obj, "mp", v.mp);
}

} // namespace binance::stocks::websocket_streams
