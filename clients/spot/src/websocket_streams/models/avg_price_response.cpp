//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/websocket_streams/models/avg_price_response.hpp>

namespace binance::spot::websocket_streams {

AvgPriceResponse tag_invoke(boost::json::value_to_tag<AvgPriceResponse> /*tag*/,
                            const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "AvgPriceResponse");
    AvgPriceResponse out;
    common::detail::json::read(obj, "e", out.e);
    common::detail::json::read(obj, "E", out.e_uppercase);
    common::detail::json::read(obj, "s", out.s);
    common::detail::json::read(obj, "i", out.i);
    common::detail::json::read(obj, "w", out.w);
    common::detail::json::read(obj, "T", out.t_uppercase);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const AvgPriceResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "e", v.e);
    common::detail::json::write(obj, "E", v.e_uppercase);
    common::detail::json::write(obj, "s", v.s);
    common::detail::json::write(obj, "i", v.i);
    common::detail::json::write(obj, "w", v.w);
    common::detail::json::write(obj, "T", v.t_uppercase);
}

} // namespace binance::spot::websocket_streams
