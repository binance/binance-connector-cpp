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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/sub_account/export.hpp>
#include <binance/sub_account/rest_api/models/get_summary_of_sub_accounts_futures_account_v2_response_delivery_account_summary_resp_sub_account_list_inner.hpp>

namespace binance::sub_account::rest_api {

struct GetSummaryOfSubAccountsFuturesAccountV2ResponseDeliveryAccountSummaryResp {
    std::optional<std::string> total_margin_balance_of_btc;
    std::optional<std::string> total_unrealized_profit_of_btc;
    std::optional<std::string> total_wallet_balance_of_btc;
    std::optional<std::string> asset;
    std::optional<std::vector<
        GetSummaryOfSubAccountsFuturesAccountV2ResponseDeliveryAccountSummaryRespSubAccountListInner>>
        sub_account_list;

    bool operator==(
        const GetSummaryOfSubAccountsFuturesAccountV2ResponseDeliveryAccountSummaryResp& /*other*/)
        const = default;
};

BINANCE_SUB_ACCOUNT_EXPORT GetSummaryOfSubAccountsFuturesAccountV2ResponseDeliveryAccountSummaryResp
tag_invoke(boost::json::value_to_tag<
               GetSummaryOfSubAccountsFuturesAccountV2ResponseDeliveryAccountSummaryResp> /*tag*/,
           const boost::json::value& jv);
BINANCE_SUB_ACCOUNT_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetSummaryOfSubAccountsFuturesAccountV2ResponseDeliveryAccountSummaryResp& v);

} // namespace binance::sub_account::rest_api
