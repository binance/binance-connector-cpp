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

struct SessionLogonResponseResult {
    std::optional<std::string> api_key;
    std::optional<std::int64_t> authorized_since;
    std::optional<std::int64_t> connected_since;
    std::optional<bool> return_rate_limits;
    std::optional<std::int64_t> server_time;
    /// Is User Data Stream subscription active?
    std::optional<bool> user_data_stream;

    bool operator==(const SessionLogonResponseResult& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT SessionLogonResponseResult tag_invoke(
    boost::json::value_to_tag<SessionLogonResponseResult> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const SessionLogonResponseResult& v);

} // namespace binance::spot::websocket_api
