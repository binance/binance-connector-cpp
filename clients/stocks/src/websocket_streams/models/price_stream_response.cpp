//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/stocks/websocket_streams/models/price_stream_response.hpp>

namespace binance::stocks::websocket_streams {

PriceStreamResponse tag_invoke(boost::json::value_to_tag<PriceStreamResponse> /*tag*/,
                               const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "PriceStreamResponse");
    PriceStreamResponse out;
    common::detail::json::read(obj, "e", out.e);
    common::detail::json::read(obj, "rates", out.rates);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const PriceStreamResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "e", v.e);
    common::detail::json::write(obj, "rates", v.rates);
}

} // namespace binance::stocks::websocket_streams
