//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/websocket_streams/models/all_market_rolling_window_ticker_response_inner.hpp>

namespace binance::spot::websocket_streams {

AllMarketRollingWindowTickerResponseInner
tag_invoke(boost::json::value_to_tag<AllMarketRollingWindowTickerResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "AllMarketRollingWindowTickerResponseInner");
    AllMarketRollingWindowTickerResponseInner out;
    common::detail::json::read(obj, "e", out.e);
    common::detail::json::read(obj, "E", out.e_uppercase);
    common::detail::json::read(obj, "s", out.s);
    common::detail::json::read(obj, "p", out.p);
    common::detail::json::read(obj, "P", out.p_uppercase);
    common::detail::json::read(obj, "o", out.o);
    common::detail::json::read(obj, "h", out.h);
    common::detail::json::read(obj, "l", out.l);
    common::detail::json::read(obj, "c", out.c);
    common::detail::json::read(obj, "w", out.w);
    common::detail::json::read(obj, "v", out.v);
    common::detail::json::read(obj, "q", out.q);
    common::detail::json::read(obj, "O", out.o_uppercase);
    common::detail::json::read(obj, "C", out.c_uppercase);
    common::detail::json::read(obj, "F", out.f_uppercase);
    common::detail::json::read(obj, "L", out.l_uppercase);
    common::detail::json::read(obj, "n", out.n);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const AllMarketRollingWindowTickerResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "e", v.e);
    common::detail::json::write(obj, "E", v.e_uppercase);
    common::detail::json::write(obj, "s", v.s);
    common::detail::json::write(obj, "p", v.p);
    common::detail::json::write(obj, "P", v.p_uppercase);
    common::detail::json::write(obj, "o", v.o);
    common::detail::json::write(obj, "h", v.h);
    common::detail::json::write(obj, "l", v.l);
    common::detail::json::write(obj, "c", v.c);
    common::detail::json::write(obj, "w", v.w);
    common::detail::json::write(obj, "v", v.v);
    common::detail::json::write(obj, "q", v.q);
    common::detail::json::write(obj, "O", v.o_uppercase);
    common::detail::json::write(obj, "C", v.c_uppercase);
    common::detail::json::write(obj, "F", v.f_uppercase);
    common::detail::json::write(obj, "L", v.l_uppercase);
    common::detail::json::write(obj, "n", v.n);
}

} // namespace binance::spot::websocket_streams
