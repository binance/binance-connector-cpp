//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <optional>
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/sub_account/export.hpp>
#include <binance/sub_account/rest_api/models/move_position_for_sub_account_response_move_position_orders_inner.hpp>

namespace binance::sub_account::rest_api {

struct MovePositionForSubAccountResponse {
    std::optional<std::vector<MovePositionForSubAccountResponseMovePositionOrdersInner>>
        move_position_orders;

    bool operator==(const MovePositionForSubAccountResponse& /*other*/) const = default;
};

BINANCE_SUB_ACCOUNT_EXPORT MovePositionForSubAccountResponse
tag_invoke(boost::json::value_to_tag<MovePositionForSubAccountResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_SUB_ACCOUNT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           const MovePositionForSubAccountResponse& v);

} // namespace binance::sub_account::rest_api
