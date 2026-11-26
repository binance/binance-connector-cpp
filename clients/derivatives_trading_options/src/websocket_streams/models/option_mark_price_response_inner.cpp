//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_options/websocket_streams/models/option_mark_price_response_inner.hpp>

namespace binance::derivatives_trading_options::websocket_streams {

OptionMarkPriceResponseInner
tag_invoke(boost::json::value_to_tag<OptionMarkPriceResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "OptionMarkPriceResponseInner");
    OptionMarkPriceResponseInner out;
    common::detail::json::read(obj, "s", out.s);
    common::detail::json::read(obj, "mp", out.mp);
    common::detail::json::read(obj, "E", out.e_uppercase);
    common::detail::json::read(obj, "e", out.e);
    common::detail::json::read(obj, "i", out.i);
    common::detail::json::read(obj, "P", out.p_uppercase);
    common::detail::json::read(obj, "bo", out.bo);
    common::detail::json::read(obj, "ao", out.ao);
    common::detail::json::read(obj, "bq", out.bq);
    common::detail::json::read(obj, "aq", out.aq);
    common::detail::json::read(obj, "b", out.b);
    common::detail::json::read(obj, "a", out.a);
    common::detail::json::read(obj, "hl", out.hl);
    common::detail::json::read(obj, "ll", out.ll);
    common::detail::json::read(obj, "vo", out.vo);
    common::detail::json::read(obj, "rf", out.rf);
    common::detail::json::read(obj, "d", out.d);
    common::detail::json::read(obj, "t", out.t);
    common::detail::json::read(obj, "g", out.g);
    common::detail::json::read(obj, "v", out.v);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const OptionMarkPriceResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "s", v.s);
    common::detail::json::write(obj, "mp", v.mp);
    common::detail::json::write(obj, "E", v.e_uppercase);
    common::detail::json::write(obj, "e", v.e);
    common::detail::json::write(obj, "i", v.i);
    common::detail::json::write(obj, "P", v.p_uppercase);
    common::detail::json::write(obj, "bo", v.bo);
    common::detail::json::write(obj, "ao", v.ao);
    common::detail::json::write(obj, "bq", v.bq);
    common::detail::json::write(obj, "aq", v.aq);
    common::detail::json::write(obj, "b", v.b);
    common::detail::json::write(obj, "a", v.a);
    common::detail::json::write(obj, "hl", v.hl);
    common::detail::json::write(obj, "ll", v.ll);
    common::detail::json::write(obj, "vo", v.vo);
    common::detail::json::write(obj, "rf", v.rf);
    common::detail::json::write(obj, "d", v.d);
    common::detail::json::write(obj, "t", v.t);
    common::detail::json::write(obj, "g", v.g);
    common::detail::json::write(obj, "v", v.v);
}

} // namespace binance::derivatives_trading_options::websocket_streams
