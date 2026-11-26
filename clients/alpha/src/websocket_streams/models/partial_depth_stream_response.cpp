//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/alpha/websocket_streams/models/partial_depth_stream_response.hpp>
#include <binance/common/detail/json.hpp>

namespace binance::alpha::websocket_streams {

PartialDepthStreamResponse tag_invoke(boost::json::value_to_tag<PartialDepthStreamResponse> /*tag*/,
                                      const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "PartialDepthStreamResponse");
    PartialDepthStreamResponse out;
    common::detail::json::read(obj, "e", out.e);
    common::detail::json::read(obj, "E", out.e_uppercase);
    common::detail::json::read(obj, "T", out.t_uppercase);
    common::detail::json::read(obj, "U", out.u_uppercase);
    common::detail::json::read(obj, "u", out.u);
    common::detail::json::read(obj, "pu", out.pu);
    common::detail::json::read(obj, "s", out.s);
    common::detail::json::read(obj, "b", out.b);
    common::detail::json::read(obj, "a", out.a);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const PartialDepthStreamResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "e", v.e);
    common::detail::json::write(obj, "E", v.e_uppercase);
    common::detail::json::write(obj, "T", v.t_uppercase);
    common::detail::json::write(obj, "U", v.u_uppercase);
    common::detail::json::write(obj, "u", v.u);
    common::detail::json::write(obj, "pu", v.pu);
    common::detail::json::write(obj, "s", v.s);
    common::detail::json::write(obj, "b", v.b);
    common::detail::json::write(obj, "a", v.a);
}

} // namespace binance::alpha::websocket_streams
