//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/alpha/websocket_streams/models/all_tokens24h_ticker_stream_response_d_inner.hpp>
#include <binance/common/detail/json.hpp>

namespace binance::alpha::websocket_streams {

AllTokens24hTickerStreamResponseDInner
tag_invoke(boost::json::value_to_tag<AllTokens24hTickerStreamResponseDInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "AllTokens24hTickerStreamResponseDInner");
    AllTokens24hTickerStreamResponseDInner out;
    common::detail::json::read(obj, "ca", out.ca);
    common::detail::json::read(obj, "cnt24", out.cnt24);
    common::detail::json::read(obj, "fdv", out.fdv);
    common::detail::json::read(obj, "hc", out.hc);
    common::detail::json::read(obj, "liq", out.liq);
    common::detail::json::read(obj, "mc", out.mc);
    common::detail::json::read(obj, "p", out.p);
    common::detail::json::read(obj, "pc24", out.pc24);
    common::detail::json::read(obj, "s", out.s);
    common::detail::json::read(obj, "t", out.t);
    common::detail::json::read(obj, "vol24", out.vol24);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const AllTokens24hTickerStreamResponseDInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "ca", v.ca);
    common::detail::json::write(obj, "cnt24", v.cnt24);
    common::detail::json::write(obj, "fdv", v.fdv);
    common::detail::json::write(obj, "hc", v.hc);
    common::detail::json::write(obj, "liq", v.liq);
    common::detail::json::write(obj, "mc", v.mc);
    common::detail::json::write(obj, "p", v.p);
    common::detail::json::write(obj, "pc24", v.pc24);
    common::detail::json::write(obj, "s", v.s);
    common::detail::json::write(obj, "t", v.t);
    common::detail::json::write(obj, "vol24", v.vol24);
}

} // namespace binance::alpha::websocket_streams
