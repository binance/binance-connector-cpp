//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/websocket_api/models/session_subscriptions_response_result_inner.hpp>

namespace binance::spot::websocket_api {

SessionSubscriptionsResponseResultInner
tag_invoke(boost::json::value_to_tag<SessionSubscriptionsResponseResultInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "SessionSubscriptionsResponseResultInner");
    SessionSubscriptionsResponseResultInner out;
    common::detail::json::read(obj, "subscriptionId", out.subscription_id);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const SessionSubscriptionsResponseResultInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "subscriptionId", v.subscription_id);
}

} // namespace binance::spot::websocket_api
