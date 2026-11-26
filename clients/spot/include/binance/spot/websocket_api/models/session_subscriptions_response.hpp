//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/spot/export.hpp>
#include <binance/spot/websocket_api/models/session_subscriptions_response_result_inner.hpp>

namespace binance::spot::websocket_api {

struct SessionSubscriptionsResponse {
    std::optional<std::string> id;
    std::optional<std::int64_t> status;
    std::optional<std::vector<SessionSubscriptionsResponseResultInner>> result;

    bool operator==(const SessionSubscriptionsResponse& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT SessionSubscriptionsResponse tag_invoke(
    boost::json::value_to_tag<SessionSubscriptionsResponse> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const SessionSubscriptionsResponse& v);

} // namespace binance::spot::websocket_api
