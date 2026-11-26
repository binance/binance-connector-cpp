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

/// Standard commission rates on trades from the order.
struct OrderTestResponseStandardCommissionForOrder {
    std::optional<std::string> maker;
    std::optional<std::string> taker;

    bool operator==(const OrderTestResponseStandardCommissionForOrder& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT OrderTestResponseStandardCommissionForOrder
tag_invoke(boost::json::value_to_tag<OrderTestResponseStandardCommissionForOrder> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const OrderTestResponseStandardCommissionForOrder& v);

} // namespace binance::spot::rest_api
