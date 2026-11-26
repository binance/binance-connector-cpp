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
#include <binance/spot/websocket_api/models/account_commission_response_rate_limits_inner.hpp>
#include <binance/spot/websocket_api/models/all_order_lists_response_result_inner.hpp>

namespace binance::spot::websocket_api {

struct AllOrderListsResponse {
    std::optional<std::string> id;
    std::optional<std::int64_t> status;
    std::optional<std::vector<AllOrderListsResponseResultInner>> result;
    std::optional<std::vector<AccountCommissionResponseRateLimitsInner>> rate_limits;

    bool operator==(const AllOrderListsResponse& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT AllOrderListsResponse
tag_invoke(boost::json::value_to_tag<AllOrderListsResponse> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const AllOrderListsResponse& v);

} // namespace binance::spot::websocket_api
