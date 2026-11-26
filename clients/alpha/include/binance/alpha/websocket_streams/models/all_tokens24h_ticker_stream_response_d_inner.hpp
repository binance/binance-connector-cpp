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

struct AllTokens24hTickerStreamResponseDInner {
    /// Contract address@chain ID
    std::optional<std::string> ca;
    /// Number of trades in the last 24 hours
    std::optional<std::int64_t> cnt24;
    /// Fully diluted valuation
    std::optional<std::string> fdv;
    /// Number of holders
    std::optional<std::string> hc;
    /// Liquidity
    std::optional<std::string> liq;
    /// Market cap
    std::optional<std::string> mc;
    /// Current price
    std::optional<std::string> p;
    /// 24-hour price change percent
    std::optional<std::string> pc24;
    /// Token short identifier
    std::optional<std::string> s;
    /// Event timestamp in milliseconds
    std::optional<std::int64_t> t;
    /// 24-hour volume
    std::optional<std::string> vol24;

    bool operator==(const AllTokens24hTickerStreamResponseDInner& /*other*/) const = default;
};

BINANCE_ALPHA_EXPORT AllTokens24hTickerStreamResponseDInner
tag_invoke(boost::json::value_to_tag<AllTokens24hTickerStreamResponseDInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_ALPHA_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                     const AllTokens24hTickerStreamResponseDInner& v);

} // namespace binance::alpha::websocket_streams
