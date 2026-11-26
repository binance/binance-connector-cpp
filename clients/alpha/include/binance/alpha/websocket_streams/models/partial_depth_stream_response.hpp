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

#include <binance/alpha/export.hpp>

namespace binance::alpha::websocket_streams {

struct PartialDepthStreamResponse {
    /// eventType
    std::optional<std::string> e;
    /// eventTime
    std::optional<std::int64_t> e_uppercase;
    /// transactionTime
    std::optional<std::int64_t> t_uppercase;
    /// firstUpdateId
    std::optional<std::int64_t> u_uppercase;
    /// lastUpdateId
    std::optional<std::int64_t> u;
    /// previousUpdateId
    std::optional<std::int64_t> pu;
    /// symbol
    std::optional<std::string> s;
    /// bids to be updated
    std::optional<std::vector<std::vector<std::string>>> b;
    /// asks to be updated
    std::optional<std::vector<std::vector<std::string>>> a;

    bool operator==(const PartialDepthStreamResponse& /*other*/) const = default;
};

BINANCE_ALPHA_EXPORT PartialDepthStreamResponse tag_invoke(
    boost::json::value_to_tag<PartialDepthStreamResponse> /*tag*/, const boost::json::value& jv);
BINANCE_ALPHA_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                     const PartialDepthStreamResponse& v);

} // namespace binance::alpha::websocket_streams
