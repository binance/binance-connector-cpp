//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/stocks/websocket_streams/models/kline_stream_response_k.hpp>

namespace binance::stocks::websocket_streams {

KlineStreamResponseK tag_invoke(boost::json::value_to_tag<KlineStreamResponseK> /*tag*/,
                                const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "KlineStreamResponseK");
    KlineStreamResponseK out;
    common::detail::json::read(obj, "t", out.t);
    common::detail::json::read(obj, "ct", out.ct);
    common::detail::json::read(obj, "s", out.s);
    common::detail::json::read(obj, "i", out.i);
    common::detail::json::read(obj, "o", out.o);
    common::detail::json::read(obj, "c", out.c);
    common::detail::json::read(obj, "h", out.h);
    common::detail::json::read(obj, "l", out.l);
    common::detail::json::read(obj, "v", out.v);
    common::detail::json::read(obj, "n", out.n);
    common::detail::json::read(obj, "x", out.x);
    common::detail::json::read(obj, "vw", out.vw);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const KlineStreamResponseK& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "t", v.t);
    common::detail::json::write(obj, "ct", v.ct);
    common::detail::json::write(obj, "s", v.s);
    common::detail::json::write(obj, "i", v.i);
    common::detail::json::write(obj, "o", v.o);
    common::detail::json::write(obj, "c", v.c);
    common::detail::json::write(obj, "h", v.h);
    common::detail::json::write(obj, "l", v.l);
    common::detail::json::write(obj, "v", v.v);
    common::detail::json::write(obj, "n", v.n);
    common::detail::json::write(obj, "x", v.x);
    common::detail::json::write(obj, "vw", v.vw);
}

} // namespace binance::stocks::websocket_streams
