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

#include <binance/stock_options/export.hpp>

namespace binance::stock_options::rest_api {

struct CancelOptionOrderResponse {
    /// Echoes the order ID in the request.
    std::optional<std::string> order_id;
    /// Always `S`, meaning the cancel request was accepted upstream. A failed cancellation (e.g.
    /// order not found or already filled) is returned as an error code (`486xxx`).
    std::optional<std::string> status;

    bool operator==(const CancelOptionOrderResponse& /*other*/) const = default;
};

BINANCE_STOCK_OPTIONS_EXPORT CancelOptionOrderResponse tag_invoke(
    boost::json::value_to_tag<CancelOptionOrderResponse> /*tag*/, const boost::json::value& jv);
BINANCE_STOCK_OPTIONS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                             boost::json::value& jv,
                                             const CancelOptionOrderResponse& v);

} // namespace binance::stock_options::rest_api
