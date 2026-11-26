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

#include <binance/spot/export.hpp>

namespace binance::spot::rest_api {

struct TickerBookTickerResponse2Inner {
    std::optional<std::string> symbol;
    /// best bid price.
    std::optional<std::string> bid_price;
    /// bid/ask qty.
    std::optional<std::string> bid_qty;
    /// best ask price.
    std::optional<std::string> ask_price;
    /// bid/ask qty.
    std::optional<std::string> ask_qty;

    bool operator==(const TickerBookTickerResponse2Inner& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT TickerBookTickerResponse2Inner
tag_invoke(boost::json::value_to_tag<TickerBookTickerResponse2Inner> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const TickerBookTickerResponse2Inner& v);

} // namespace binance::spot::rest_api
