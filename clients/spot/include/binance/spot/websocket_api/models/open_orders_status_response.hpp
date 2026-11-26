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
#include <binance/spot/websocket_api/models/open_order_lists_status_response_rate_limits_inner.hpp>
#include <binance/spot/websocket_api/models/open_orders_status_response_result_inner.hpp>

namespace binance::spot::websocket_api {

struct OpenOrdersStatusResponse {
    std::optional<std::string> id;
    std::optional<std::int64_t> status;
    std::optional<std::vector<OpenOrdersStatusResponseResultInner>> result;
    std::optional<std::vector<OpenOrderListsStatusResponseRateLimitsInner>> rate_limits;

    bool operator==(const OpenOrdersStatusResponse& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT OpenOrdersStatusResponse tag_invoke(
    boost::json::value_to_tag<OpenOrdersStatusResponse> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const OpenOrdersStatusResponse& v);

} // namespace binance::spot::websocket_api
