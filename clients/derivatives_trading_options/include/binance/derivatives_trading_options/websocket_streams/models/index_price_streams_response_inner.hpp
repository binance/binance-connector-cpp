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

#include <binance/derivatives_trading_options/export.hpp>

namespace binance::derivatives_trading_options::websocket_streams {

struct IndexPriceStreamsResponseInner {
    /// event type
    std::optional<std::string> e;
    /// time
    std::optional<std::int64_t> e_uppercase;
    /// underlying symbol
    std::optional<std::string> s;
    /// index price
    std::optional<std::string> p;

    bool operator==(const IndexPriceStreamsResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT IndexPriceStreamsResponseInner
tag_invoke(boost::json::value_to_tag<IndexPriceStreamsResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                           boost::json::value& jv,
                                                           const IndexPriceStreamsResponseInner& v);

} // namespace binance::derivatives_trading_options::websocket_streams
