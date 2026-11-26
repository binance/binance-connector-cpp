//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_options/websocket_streams/models/index_price_streams_response_inner.hpp>

namespace binance::derivatives_trading_options::websocket_streams {

IndexPriceStreamsResponseInner
tag_invoke(boost::json::value_to_tag<IndexPriceStreamsResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "IndexPriceStreamsResponseInner");
    IndexPriceStreamsResponseInner out;
    common::detail::json::read(obj, "e", out.e);
    common::detail::json::read(obj, "E", out.e_uppercase);
    common::detail::json::read(obj, "s", out.s);
    common::detail::json::read(obj, "p", out.p);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const IndexPriceStreamsResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "e", v.e);
    common::detail::json::write(obj, "E", v.e_uppercase);
    common::detail::json::write(obj, "s", v.s);
    common::detail::json::write(obj, "p", v.p);
}

} // namespace binance::derivatives_trading_options::websocket_streams
