//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/w3w_prediction/websocket_streams/models/reward_claim_failed_response.hpp>

namespace binance::w3w_prediction::websocket_streams {

RewardClaimFailedResponse tag_invoke(boost::json::value_to_tag<RewardClaimFailedResponse> /*tag*/,
                                     const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "RewardClaimFailedResponse");
    RewardClaimFailedResponse out;
    common::detail::json::read(obj, "pushId", out.push_id);
    common::detail::json::read(obj, "amount", out.amount);
    common::detail::json::read(obj, "outcome", out.outcome);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const RewardClaimFailedResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "pushId", v.push_id);
    common::detail::json::write(obj, "amount", v.amount);
    common::detail::json::write(obj, "outcome", v.outcome);
}

} // namespace binance::w3w_prediction::websocket_streams
