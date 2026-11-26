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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/simple_earn/export.hpp>
#include <binance/simple_earn/rest_api/models/get_rwusd_subscription_history_response_rows_inner.hpp>

namespace binance::simple_earn::rest_api {

struct GetRwusdSubscriptionHistoryResponse {
    std::optional<std::vector<GetRwusdSubscriptionHistoryResponseRowsInner>> rows;
    std::optional<std::int64_t> total;

    bool operator==(const GetRwusdSubscriptionHistoryResponse& /*other*/) const = default;
};

BINANCE_SIMPLE_EARN_EXPORT GetRwusdSubscriptionHistoryResponse
tag_invoke(boost::json::value_to_tag<GetRwusdSubscriptionHistoryResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_SIMPLE_EARN_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           const GetRwusdSubscriptionHistoryResponse& v);

} // namespace binance::simple_earn::rest_api
