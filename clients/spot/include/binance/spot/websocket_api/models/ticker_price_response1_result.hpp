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

namespace binance::spot::websocket_api {

struct TickerPriceResponse1Result {
    std::optional<std::string> symbol;
    std::optional<std::string> price;

    bool operator==(const TickerPriceResponse1Result& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT TickerPriceResponse1Result tag_invoke(
    boost::json::value_to_tag<TickerPriceResponse1Result> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const TickerPriceResponse1Result& v);

} // namespace binance::spot::websocket_api
