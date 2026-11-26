//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/stocks/websocket_streams/models/quote_stream_response.hpp>

namespace binance::stocks::websocket_streams {

QuoteStreamResponse tag_invoke(boost::json::value_to_tag<QuoteStreamResponse> /*tag*/,
                               const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "QuoteStreamResponse");
    QuoteStreamResponse out;
    common::detail::json::read(obj, "e", out.e);
    common::detail::json::read(obj, "E", out.e_uppercase);
    common::detail::json::read(obj, "s", out.s);
    common::detail::json::read(obj, "bp", out.bp);
    common::detail::json::read(obj, "ap", out.ap);
    common::detail::json::read(obj, "bs", out.bs);
    common::detail::json::read(obj, "as", out.as);
    common::detail::json::read(obj, "T", out.t_uppercase);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QuoteStreamResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "e", v.e);
    common::detail::json::write(obj, "E", v.e_uppercase);
    common::detail::json::write(obj, "s", v.s);
    common::detail::json::write(obj, "bp", v.bp);
    common::detail::json::write(obj, "ap", v.ap);
    common::detail::json::write(obj, "bs", v.bs);
    common::detail::json::write(obj, "as", v.as);
    common::detail::json::write(obj, "T", v.t_uppercase);
}

} // namespace binance::stocks::websocket_streams
