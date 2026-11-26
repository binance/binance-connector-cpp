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

namespace binance::spot::websocket_api {

struct UserDataStreamUnsubscribeResponse {
    std::optional<std::string> id;
    std::optional<std::int64_t> status;
    std::optional<boost::json::value> result;

    bool operator==(const UserDataStreamUnsubscribeResponse& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT UserDataStreamUnsubscribeResponse
tag_invoke(boost::json::value_to_tag<UserDataStreamUnsubscribeResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const UserDataStreamUnsubscribeResponse& v);

} // namespace binance::spot::websocket_api
