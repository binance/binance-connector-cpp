//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <optional>
#include <string>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/derivatives_trading_options/export.hpp>

namespace binance::derivatives_trading_options::rest_api {

struct OptionMarkPriceResponseInner {
    /// symbol
    std::optional<std::string> symbol;
    /// Mark price
    std::optional<std::string> mark_price;
    /// Implied volatility Buy
    std::optional<std::string> bid_iv;
    /// Implied volatility Sell
    std::optional<std::string> ask_iv;
    /// Implied volatility mark
    std::optional<std::string> mark_iv;
    /// delta
    std::optional<std::string> delta;
    /// theta
    std::optional<std::string> theta;
    /// gamma
    std::optional<std::string> gamma;
    /// vega
    std::optional<std::string> vega;
    /// Current highest buy price
    std::optional<std::string> high_price_limit;
    /// Current lowest sell price
    std::optional<std::string> low_price_limit;
    /// risk free rate
    std::optional<std::string> risk_free_interest;

    bool operator==(const OptionMarkPriceResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT OptionMarkPriceResponseInner tag_invoke(
    boost::json::value_to_tag<OptionMarkPriceResponseInner> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                           boost::json::value& jv,
                                                           const OptionMarkPriceResponseInner& v);

} // namespace binance::derivatives_trading_options::rest_api
