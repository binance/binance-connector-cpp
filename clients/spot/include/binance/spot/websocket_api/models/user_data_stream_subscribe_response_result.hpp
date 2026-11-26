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

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/spot/export.hpp>

namespace binance::spot::websocket_api {

struct UserDataStreamSubscribeResponseResult {
    std::optional<std::int64_t> subscription_id;

    bool operator==(const UserDataStreamSubscribeResponseResult& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT UserDataStreamSubscribeResponseResult
tag_invoke(boost::json::value_to_tag<UserDataStreamSubscribeResponseResult> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const UserDataStreamSubscribeResponseResult& v);

} // namespace binance::spot::websocket_api
