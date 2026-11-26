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

#include <binance/derivatives_trading_usds_futures/export.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

struct SymbolPriceTickerResponse1 {
    /// Symbol.
    std::optional<std::string> symbol;
    /// Price.
    std::optional<std::string> price;
    /// Transaction time
    std::optional<std::int64_t> time;

    bool operator==(const SymbolPriceTickerResponse1& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT SymbolPriceTickerResponse1 tag_invoke(
    boost::json::value_to_tag<SymbolPriceTickerResponse1> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const SymbolPriceTickerResponse1& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
