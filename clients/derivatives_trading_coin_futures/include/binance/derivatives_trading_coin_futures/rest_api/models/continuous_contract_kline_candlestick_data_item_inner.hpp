//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <cstdint>
#include <string>
#include <variant>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/derivatives_trading_coin_futures/export.hpp>

namespace binance::derivatives_trading_coin_futures::rest_api {

struct ContinuousContractKlineCandlestickDataItemInner {
    /// One of the alternatives, or the raw JSON when none matches.
    std::variant<std::int64_t, std::string, boost::json::value> value;

    bool
    operator==(const ContinuousContractKlineCandlestickDataItemInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT ContinuousContractKlineCandlestickDataItemInner
tag_invoke(boost::json::value_to_tag<ContinuousContractKlineCandlestickDataItemInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const ContinuousContractKlineCandlestickDataItemInner& v);

} // namespace binance::derivatives_trading_coin_futures::rest_api
