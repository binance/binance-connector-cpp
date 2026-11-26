//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/alpha/websocket_streams/models/all_tokens24h_ticker_stream_response.hpp>
#include <binance/common/detail/json.hpp>

namespace binance::alpha::websocket_streams {

AllTokens24hTickerStreamResponse
tag_invoke(boost::json::value_to_tag<AllTokens24hTickerStreamResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "AllTokens24hTickerStreamResponse");
    AllTokens24hTickerStreamResponse out;
    common::detail::json::read(obj, "e", out.e);
    common::detail::json::read(obj, "d", out.d);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const AllTokens24hTickerStreamResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "e", v.e);
    common::detail::json::write(obj, "d", v.d);
}

} // namespace binance::alpha::websocket_streams
