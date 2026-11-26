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

struct CancelEquityOrderResponse {
    /// Echoes the requested order id.
    std::optional<std::string> order_id;
    /// Acknowledgement code: `S` = cancel accepted by upstream, `F` = cancel failed. Not an order
    /// lifecycle status — use `/order/detail` for lifecycle poll.
    std::optional<std::string> status;

    bool operator==(const CancelEquityOrderResponse& /*other*/) const = default;
};

BINANCE_STOCKS_EXPORT CancelEquityOrderResponse tag_invoke(
    boost::json::value_to_tag<CancelEquityOrderResponse> /*tag*/, const boost::json::value& jv);
BINANCE_STOCKS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const CancelEquityOrderResponse& v);

} // namespace binance::stocks::rest_api
