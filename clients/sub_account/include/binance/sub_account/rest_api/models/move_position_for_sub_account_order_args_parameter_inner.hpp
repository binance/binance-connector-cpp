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

#include <binance/common/decimal.hpp>
#include <binance/sub_account/export.hpp>

namespace binance::sub_account::rest_api {

struct MovePositionForSubAccountOrderArgsParameterInner {
    std::optional<std::string> symbol;
    std::optional<common::Decimal> quantity;
    /// Required when productType=UM. Optional and ignored when productType=OPTION (the response
    /// returns positionSide as null).
    std::optional<std::string> position_side;

    bool
    operator==(const MovePositionForSubAccountOrderArgsParameterInner& /*other*/) const = default;
};

BINANCE_SUB_ACCOUNT_EXPORT MovePositionForSubAccountOrderArgsParameterInner
tag_invoke(boost::json::value_to_tag<MovePositionForSubAccountOrderArgsParameterInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_SUB_ACCOUNT_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const MovePositionForSubAccountOrderArgsParameterInner& v);

} // namespace binance::sub_account::rest_api
