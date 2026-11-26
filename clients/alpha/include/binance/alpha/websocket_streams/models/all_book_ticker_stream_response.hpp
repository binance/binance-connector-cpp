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

#include <binance/alpha/export.hpp>

namespace binance::alpha::websocket_streams {

struct AllBookTickerStreamResponse {
    /// eventType
    std::optional<std::string> e;
    /// eventTime
    std::optional<std::int64_t> e_uppercase;
    /// transactionTime
    std::optional<std::int64_t> t_uppercase;
    /// updateId
    std::optional<std::int64_t> u;
    /// symbol
    std::optional<std::string> s;
    /// bid1Price
    std::optional<std::string> b;
    /// bid1Quantity
    std::optional<std::string> b_uppercase;
    /// ask1Price
    std::optional<std::string> a;
    /// ask1Quantity
    std::optional<std::string> a_uppercase;

    bool operator==(const AllBookTickerStreamResponse& /*other*/) const = default;
};

BINANCE_ALPHA_EXPORT AllBookTickerStreamResponse tag_invoke(
    boost::json::value_to_tag<AllBookTickerStreamResponse> /*tag*/, const boost::json::value& jv);
BINANCE_ALPHA_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                     const AllBookTickerStreamResponse& v);

} // namespace binance::alpha::websocket_streams
