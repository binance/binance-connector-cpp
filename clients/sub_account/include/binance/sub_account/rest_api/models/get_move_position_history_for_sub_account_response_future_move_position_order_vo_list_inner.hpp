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

#include <binance/sub_account/export.hpp>

namespace binance::sub_account::rest_api {

struct GetMovePositionHistoryForSubAccountResponseFutureMovePositionOrderVoListInner {
    std::optional<std::string> from_user_email;
    std::optional<std::string> to_user_email;
    std::optional<std::string> product_type;
    std::optional<std::string> symbol;
    std::optional<std::string> price;
    std::optional<std::string> quantity;
    std::optional<std::string> position_side;
    std::optional<std::string> side;
    std::optional<std::int64_t> time_stamp;

    bool operator==(
        const GetMovePositionHistoryForSubAccountResponseFutureMovePositionOrderVoListInner& /*other*/)
        const = default;
};

BINANCE_SUB_ACCOUNT_EXPORT
GetMovePositionHistoryForSubAccountResponseFutureMovePositionOrderVoListInner tag_invoke(
    boost::json::value_to_tag<
        GetMovePositionHistoryForSubAccountResponseFutureMovePositionOrderVoListInner> /*tag*/,
    const boost::json::value& jv);
BINANCE_SUB_ACCOUNT_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetMovePositionHistoryForSubAccountResponseFutureMovePositionOrderVoListInner& v);

} // namespace binance::sub_account::rest_api
