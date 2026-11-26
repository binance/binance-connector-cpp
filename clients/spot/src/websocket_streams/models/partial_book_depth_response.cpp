//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/websocket_streams/models/partial_book_depth_response.hpp>

namespace binance::spot::websocket_streams {

PartialBookDepthResponse tag_invoke(boost::json::value_to_tag<PartialBookDepthResponse> /*tag*/,
                                    const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "PartialBookDepthResponse");
    PartialBookDepthResponse out;
    common::detail::json::read(obj, "lastUpdateId", out.last_update_id);
    common::detail::json::read(obj, "bids", out.bids);
    common::detail::json::read(obj, "asks", out.asks);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const PartialBookDepthResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "lastUpdateId", v.last_update_id);
    common::detail::json::write(obj, "bids", v.bids);
    common::detail::json::write(obj, "asks", v.asks);
}

} // namespace binance::spot::websocket_streams
