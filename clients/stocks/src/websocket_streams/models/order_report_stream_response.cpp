//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/stocks/websocket_streams/models/order_report_stream_response.hpp>

namespace binance::stocks::websocket_streams {

OrderReportStreamResponse tag_invoke(boost::json::value_to_tag<OrderReportStreamResponse> /*tag*/,
                                     const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "OrderReportStreamResponse");
    OrderReportStreamResponse out;
    common::detail::json::read(obj, "e", out.e);
    common::detail::json::read(obj, "E", out.e_uppercase);
    common::detail::json::read(obj, "x", out.x);
    common::detail::json::read(obj, "i", out.i);
    common::detail::json::read(obj, "ai", out.ai);
    common::detail::json::read(obj, "b", out.b);
    common::detail::json::read(obj, "q", out.q);
    common::detail::json::read(obj, "S", out.s_uppercase);
    common::detail::json::read(obj, "o", out.o);
    common::detail::json::read(obj, "p", out.p);
    common::detail::json::read(obj, "Q", out.q_uppercase);
    common::detail::json::read(obj, "N", out.n_uppercase);
    common::detail::json::read(obj, "fq", out.fq);
    common::detail::json::read(obj, "FN", out.fn_uppercase);
    common::detail::json::read(obj, "tc", out.tc);
    common::detail::json::read(obj, "Z", out.z_uppercase);
    common::detail::json::read(obj, "n", out.n);
    common::detail::json::read(obj, "s", out.s);
    common::detail::json::read(obj, "T", out.t_uppercase);
    common::detail::json::read(obj, "U", out.u_uppercase);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const OrderReportStreamResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "e", v.e);
    common::detail::json::write(obj, "E", v.e_uppercase);
    common::detail::json::write(obj, "x", v.x);
    common::detail::json::write(obj, "i", v.i);
    common::detail::json::write(obj, "ai", v.ai);
    common::detail::json::write(obj, "b", v.b);
    common::detail::json::write(obj, "q", v.q);
    common::detail::json::write(obj, "S", v.s_uppercase);
    common::detail::json::write(obj, "o", v.o);
    common::detail::json::write(obj, "p", v.p);
    common::detail::json::write(obj, "Q", v.q_uppercase);
    common::detail::json::write(obj, "N", v.n_uppercase);
    common::detail::json::write(obj, "fq", v.fq);
    common::detail::json::write(obj, "FN", v.fn_uppercase);
    common::detail::json::write(obj, "tc", v.tc);
    common::detail::json::write(obj, "Z", v.z_uppercase);
    common::detail::json::write(obj, "n", v.n);
    common::detail::json::write(obj, "s", v.s);
    common::detail::json::write(obj, "T", v.t_uppercase);
    common::detail::json::write(obj, "U", v.u_uppercase);
}

} // namespace binance::stocks::websocket_streams
