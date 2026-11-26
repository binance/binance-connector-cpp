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

#include <binance/sub_account/export.hpp>

namespace binance::sub_account::rest_api {

struct GetFuturesPositionRiskOfSubAccountV2ResponseDeliveryPositionRiskVosInner {
    std::optional<std::string> entry_price;
    std::optional<std::string> mark_price;
    std::optional<std::string> leverage;
    std::optional<std::string> isolated;
    std::optional<std::string> isolated_wallet;
    std::optional<std::string> isolated_margin;
    std::optional<std::string> is_auto_add_margin;
    std::optional<std::string> position_side;
    std::optional<std::string> position_amount;
    std::optional<std::string> symbol;
    std::optional<std::string> unrealized_profit;

    bool operator==(
        const GetFuturesPositionRiskOfSubAccountV2ResponseDeliveryPositionRiskVosInner& /*other*/)
        const = default;
};

BINANCE_SUB_ACCOUNT_EXPORT GetFuturesPositionRiskOfSubAccountV2ResponseDeliveryPositionRiskVosInner
tag_invoke(boost::json::value_to_tag<
               GetFuturesPositionRiskOfSubAccountV2ResponseDeliveryPositionRiskVosInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_SUB_ACCOUNT_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetFuturesPositionRiskOfSubAccountV2ResponseDeliveryPositionRiskVosInner& v);

} // namespace binance::sub_account::rest_api
