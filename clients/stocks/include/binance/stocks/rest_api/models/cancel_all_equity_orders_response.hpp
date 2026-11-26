//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <optional>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/stocks/export.hpp>

namespace binance::stocks::rest_api {

struct CancelAllEquityOrdersResponse {
    /// `true` when the cancel-all request was accepted by upstream. Per-order outcomes live in
    /// `/order/history`.
    std::optional<bool> success;

    bool operator==(const CancelAllEquityOrdersResponse& /*other*/) const = default;
};

BINANCE_STOCKS_EXPORT CancelAllEquityOrdersResponse tag_invoke(
    boost::json::value_to_tag<CancelAllEquityOrdersResponse> /*tag*/, const boost::json::value& jv);
BINANCE_STOCKS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const CancelAllEquityOrdersResponse& v);

} // namespace binance::stocks::rest_api
