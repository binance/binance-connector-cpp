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

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/spot/export.hpp>
#include <binance/spot/websocket_api/models/user_data_stream_subscribe_response_result.hpp>

namespace binance::spot::websocket_api {

struct UserDataStreamSubscribeResponse {
    std::optional<std::string> id;
    std::optional<std::int64_t> status;
    std::optional<UserDataStreamSubscribeResponseResult> result;

    bool operator==(const UserDataStreamSubscribeResponse& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT UserDataStreamSubscribeResponse
tag_invoke(boost::json::value_to_tag<UserDataStreamSubscribeResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const UserDataStreamSubscribeResponse& v);

} // namespace binance::spot::websocket_api
