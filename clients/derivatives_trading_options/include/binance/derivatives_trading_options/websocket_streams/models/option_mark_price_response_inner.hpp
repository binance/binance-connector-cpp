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

struct OptionMarkPriceResponseInner {
    /// Symbol
    std::optional<std::string> s;
    /// Mark price
    std::optional<std::string> mp;
    /// Event time
    std::optional<std::int64_t> e_uppercase;
    /// Event type
    std::optional<std::string> e;
    /// Index price
    std::optional<std::string> i;
    /// Estimated Settle Price, only useful in the 0.5 hour before the settlement starts
    std::optional<std::string> p_uppercase;
    /// The best buy price
    std::optional<std::string> bo;
    /// The best sell price
    std::optional<std::string> ao;
    /// The best buy quantity
    std::optional<std::string> bq;
    /// The best sell quantity
    std::optional<std::string> aq;
    /// BuyImplied volatility
    std::optional<std::string> b;
    /// SellImplied volatility
    std::optional<std::string> a;
    /// Buy Maximum price
    std::optional<std::string> hl;
    /// Sell Minimum price
    std::optional<std::string> ll;
    /// volatility
    std::optional<std::string> vo;
    /// risk free rate
    std::optional<std::string> rf;
    /// delta
    std::optional<std::string> d;
    /// theta
    std::optional<std::string> t;
    /// gamma
    std::optional<std::string> g;
    /// vega
    std::optional<std::string> v;

    bool operator==(const OptionMarkPriceResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT OptionMarkPriceResponseInner tag_invoke(
    boost::json::value_to_tag<OptionMarkPriceResponseInner> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                           boost::json::value& jv,
                                                           const OptionMarkPriceResponseInner& v);

} // namespace binance::derivatives_trading_options::websocket_streams
