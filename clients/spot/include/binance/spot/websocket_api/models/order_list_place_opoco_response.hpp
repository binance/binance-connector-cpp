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
#include <binance/spot/websocket_api/models/order_list_place_opoco_response_result.hpp>

namespace binance::spot::websocket_api {

struct OrderListPlaceOpocoResponse {
    std::optional<std::string> id;
    std::optional<std::int64_t> status;
    std::optional<OrderListPlaceOpocoResponseResult> result;

    bool operator==(const OrderListPlaceOpocoResponse& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT OrderListPlaceOpocoResponse tag_invoke(
    boost::json::value_to_tag<OrderListPlaceOpocoResponse> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const OrderListPlaceOpocoResponse& v);

} // namespace binance::spot::websocket_api
