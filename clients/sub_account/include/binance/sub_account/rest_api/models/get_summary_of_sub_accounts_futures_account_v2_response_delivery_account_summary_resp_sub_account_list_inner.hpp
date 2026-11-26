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

struct
    GetSummaryOfSubAccountsFuturesAccountV2ResponseDeliveryAccountSummaryRespSubAccountListInner {
    std::optional<std::string> email;
    std::optional<std::string> total_margin_balance;
    std::optional<std::string> total_unrealized_profit;
    std::optional<std::string> total_wallet_balance;
    std::optional<std::string> asset;

    bool operator==(
        const GetSummaryOfSubAccountsFuturesAccountV2ResponseDeliveryAccountSummaryRespSubAccountListInner& /*other*/)
        const = default;
};

BINANCE_SUB_ACCOUNT_EXPORT
GetSummaryOfSubAccountsFuturesAccountV2ResponseDeliveryAccountSummaryRespSubAccountListInner
tag_invoke(
    boost::json::value_to_tag<
        GetSummaryOfSubAccountsFuturesAccountV2ResponseDeliveryAccountSummaryRespSubAccountListInner> /*tag*/
    ,
    const boost::json::value& jv);
BINANCE_SUB_ACCOUNT_EXPORT void tag_invoke(
    boost::json::value_from_tag /*tag*/, boost::json::value& jv,
    const GetSummaryOfSubAccountsFuturesAccountV2ResponseDeliveryAccountSummaryRespSubAccountListInner&
        v);

} // namespace binance::sub_account::rest_api
