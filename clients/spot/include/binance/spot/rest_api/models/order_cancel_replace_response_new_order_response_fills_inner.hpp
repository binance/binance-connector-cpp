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

struct OrderCancelReplaceResponseNewOrderResponseFillsInner {
    std::optional<std::string> price;
    std::optional<std::string> qty;
    std::optional<std::string> commission;
    std::optional<std::string> commission_asset;
    std::optional<std::int64_t> trade_id;

    bool operator==(const OrderCancelReplaceResponseNewOrderResponseFillsInner& /*other*/) const =
        default;
};

BINANCE_SPOT_EXPORT OrderCancelReplaceResponseNewOrderResponseFillsInner
tag_invoke(boost::json::value_to_tag<OrderCancelReplaceResponseNewOrderResponseFillsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const OrderCancelReplaceResponseNewOrderResponseFillsInner& v);

} // namespace binance::spot::rest_api
