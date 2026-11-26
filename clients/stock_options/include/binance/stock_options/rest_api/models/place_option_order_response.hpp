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

struct PlaceOptionOrderResponse {
    /// `S` = accepted; `P` = processing. A failed order is always returned as an error code (see
    /// Error Code); a successful response never carries a failed status.
    std::optional<std::string> status;
    /// Option order ID. Omitted when `status` = `P`; query Option Order Detail by `clientOrderId`
    /// instead.
    std::optional<std::string> order_id;
    /// Echoes the supplied or server-generated client order ID.
    std::optional<std::string> client_order_id;

    bool operator==(const PlaceOptionOrderResponse& /*other*/) const = default;
};

BINANCE_STOCK_OPTIONS_EXPORT PlaceOptionOrderResponse tag_invoke(
    boost::json::value_to_tag<PlaceOptionOrderResponse> /*tag*/, const boost::json::value& jv);
BINANCE_STOCK_OPTIONS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                             boost::json::value& jv,
                                             const PlaceOptionOrderResponse& v);

} // namespace binance::stock_options::rest_api
