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

/// Kline payload
struct ContractKlineStreamResponseK {
    /// Open price
    std::optional<std::string> o;
    /// Close price
    std::optional<std::string> c;
    /// High price
    std::optional<std::string> h;
    /// Low price
    std::optional<std::string> l;
    /// Volume
    std::optional<std::string> v;
    /// Kline open time
    std::optional<std::int64_t> ot;
    /// Kline close time
    std::optional<std::int64_t> ct;
    /// Interval
    std::optional<std::string> i;

    bool operator==(const ContractKlineStreamResponseK& /*other*/) const = default;
};

BINANCE_ALPHA_EXPORT ContractKlineStreamResponseK tag_invoke(
    boost::json::value_to_tag<ContractKlineStreamResponseK> /*tag*/, const boost::json::value& jv);
BINANCE_ALPHA_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                     const ContractKlineStreamResponseK& v);

} // namespace binance::alpha::websocket_streams
