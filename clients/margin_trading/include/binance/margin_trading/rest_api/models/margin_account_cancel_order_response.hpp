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

#include <binance/margin_trading/export.hpp>

namespace binance::margin_trading::rest_api {

struct MarginAccountCancelOrderResponse {
    /// symbol.
    std::optional<std::string> symbol;
    /// order Id.
    std::optional<std::string> order_id;
    /// orig Client Order Id.
    std::optional<std::string> orig_client_order_id;
    /// client Order Id.
    std::optional<std::string> client_order_id;
    /// price.
    std::optional<std::string> price;
    /// orig Qty.
    std::optional<std::string> orig_qty;
    /// executed Qty.
    std::optional<std::string> executed_qty;
    /// cummulative Quote Qty.
    std::optional<std::string> cummulative_quote_qty;
    /// status.
    std::optional<std::string> status;
    /// time In Force.
    std::optional<std::string> time_in_force;
    /// type.
    std::optional<std::string> type;
    /// side.
    std::optional<std::string> side;
    /// if isolated margin
    std::optional<bool> is_isolated;

    bool operator==(const MarginAccountCancelOrderResponse& /*other*/) const = default;
};

BINANCE_MARGIN_TRADING_EXPORT MarginAccountCancelOrderResponse
tag_invoke(boost::json::value_to_tag<MarginAccountCancelOrderResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const MarginAccountCancelOrderResponse& v);

} // namespace binance::margin_trading::rest_api
