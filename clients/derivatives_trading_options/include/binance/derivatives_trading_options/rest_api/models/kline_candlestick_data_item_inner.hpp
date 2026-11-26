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

#include <binance/derivatives_trading_options/export.hpp>

namespace binance::derivatives_trading_options::rest_api {

struct KlineCandlestickDataItemInner {
    /// One of the alternatives, or the raw JSON when none matches.
    std::variant<std::int64_t, std::string, boost::json::value> value;

    bool operator==(const KlineCandlestickDataItemInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT KlineCandlestickDataItemInner tag_invoke(
    boost::json::value_to_tag<KlineCandlestickDataItemInner> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                           boost::json::value& jv,
                                                           const KlineCandlestickDataItemInner& v);

} // namespace binance::derivatives_trading_options::rest_api
