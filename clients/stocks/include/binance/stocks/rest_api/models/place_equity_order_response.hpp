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

#include <binance/stocks/export.hpp>

namespace binance::stocks::rest_api {

struct PlaceEquityOrderResponse {
    /// Acknowledgement code: `S` = accepted, `F` = failed. Not an order lifecycle status — to poll
    /// lifecycle, call `/order/detail` or `/order/history`.
    std::optional<std::string> status;
    /// Order id (UUID).
    std::optional<std::string> order_id;
    /// Echoes the supplied or server-generated client order id.
    std::optional<std::string> client_order_id;

    bool operator==(const PlaceEquityOrderResponse& /*other*/) const = default;
};

BINANCE_STOCKS_EXPORT PlaceEquityOrderResponse tag_invoke(
    boost::json::value_to_tag<PlaceEquityOrderResponse> /*tag*/, const boost::json::value& jv);
BINANCE_STOCKS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const PlaceEquityOrderResponse& v);

} // namespace binance::stocks::rest_api
