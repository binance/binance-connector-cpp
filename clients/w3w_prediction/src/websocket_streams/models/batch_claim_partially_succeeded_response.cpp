//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/w3w_prediction/websocket_streams/models/batch_claim_partially_succeeded_response.hpp>

namespace binance::w3w_prediction::websocket_streams {

BatchClaimPartiallySucceededResponse
tag_invoke(boost::json::value_to_tag<BatchClaimPartiallySucceededResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "BatchClaimPartiallySucceededResponse");
    BatchClaimPartiallySucceededResponse out;
    common::detail::json::read(obj, "pushId", out.push_id);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const BatchClaimPartiallySucceededResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "pushId", v.push_id);
}

} // namespace binance::w3w_prediction::websocket_streams
