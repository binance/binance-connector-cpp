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

#include <binance/spot/export.hpp>

namespace binance::spot::rest_api {

struct OrderOcoResponseOrdersInner {
    std::optional<std::string> symbol;
    std::optional<std::int64_t> order_id;
    std::optional<std::string> client_order_id;

    bool operator==(const OrderOcoResponseOrdersInner& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT OrderOcoResponseOrdersInner tag_invoke(
    boost::json::value_to_tag<OrderOcoResponseOrdersInner> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const OrderOcoResponseOrdersInner& v);

} // namespace binance::spot::rest_api
