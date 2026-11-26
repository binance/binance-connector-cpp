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

#include <binance/stock_options/export.hpp>

namespace binance::stock_options::rest_api {

struct CancelAllOptionOrdersResponse {
    /// `true` if the cancel-all request was accepted upstream. Individual orders may still fail to
    /// cancel (e.g. already filled); check with Current Open Option Orders.
    std::optional<bool> success;

    bool operator==(const CancelAllOptionOrdersResponse& /*other*/) const = default;
};

BINANCE_STOCK_OPTIONS_EXPORT CancelAllOptionOrdersResponse tag_invoke(
    boost::json::value_to_tag<CancelAllOptionOrdersResponse> /*tag*/, const boost::json::value& jv);
BINANCE_STOCK_OPTIONS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                             boost::json::value& jv,
                                             const CancelAllOptionOrdersResponse& v);

} // namespace binance::stock_options::rest_api
