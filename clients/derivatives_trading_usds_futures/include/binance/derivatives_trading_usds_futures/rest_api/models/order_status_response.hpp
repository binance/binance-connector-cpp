//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <cstdint>
#include <optional>
#include <string>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/derivatives_trading_usds_futures/export.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

struct OrderStatusResponse {
    std::optional<std::int64_t> order_id;
    std::optional<std::string> order_status;
    std::optional<std::string> from_asset;
    std::optional<std::string> from_amount;
    std::optional<std::string> to_asset;
    std::optional<std::string> to_amount;
    std::optional<std::string> ratio;
    std::optional<std::string> inverse_ratio;
    std::optional<std::int64_t> create_time;

    bool operator==(const OrderStatusResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT OrderStatusResponse
tag_invoke(boost::json::value_to_tag<OrderStatusResponse> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                                boost::json::value& jv,
                                                                const OrderStatusResponse& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
