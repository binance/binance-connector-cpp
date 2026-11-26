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

namespace binance::spot::websocket_api {

struct OrderAmendKeepPriorityResponseResultListStatusOrdersInner {
    std::optional<std::string> symbol;
    std::optional<std::int64_t> order_id;
    std::optional<std::string> client_order_id;

    bool operator==(
        const OrderAmendKeepPriorityResponseResultListStatusOrdersInner& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT OrderAmendKeepPriorityResponseResultListStatusOrdersInner tag_invoke(
    boost::json::value_to_tag<OrderAmendKeepPriorityResponseResultListStatusOrdersInner> /*tag*/,
    const boost::json::value& jv);
BINANCE_SPOT_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const OrderAmendKeepPriorityResponseResultListStatusOrdersInner& v);

} // namespace binance::spot::websocket_api
