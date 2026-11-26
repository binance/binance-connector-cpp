//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/websocket_streams/models/reference_price_response.hpp>

namespace binance::spot::websocket_streams {

ReferencePriceResponse tag_invoke(boost::json::value_to_tag<ReferencePriceResponse> /*tag*/,
                                  const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "ReferencePriceResponse");
    ReferencePriceResponse out;
    common::detail::json::read(obj, "e", out.e);
    common::detail::json::read(obj, "s", out.s);
    common::detail::json::read(obj, "r", out.r);
    common::detail::json::read(obj, "t", out.t);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const ReferencePriceResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "e", v.e);
    common::detail::json::write(obj, "s", v.s);
    common::detail::json::write(obj, "r", v.r);
    common::detail::json::write(obj, "t", v.t);
}

} // namespace binance::spot::websocket_streams
