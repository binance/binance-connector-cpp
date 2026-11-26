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

struct AcceptBlockTradeOrderResponseLegsInner {
    /// symbol
    std::optional<std::string> symbol;
    /// side
    std::optional<std::string> side;
    /// quantity
    std::optional<std::string> quantity;
    /// price
    std::optional<std::string> price;

    bool operator==(const AcceptBlockTradeOrderResponseLegsInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT AcceptBlockTradeOrderResponseLegsInner
tag_invoke(boost::json::value_to_tag<AcceptBlockTradeOrderResponseLegsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const AcceptBlockTradeOrderResponseLegsInner& v);

} // namespace binance::derivatives_trading_options::rest_api
