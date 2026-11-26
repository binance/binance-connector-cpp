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
#include <binance/sub_account/rest_api/models/get_summary_of_sub_accounts_margin_account_response_sub_account_list_inner.hpp>

namespace binance::sub_account::rest_api {

struct GetSummaryOfSubAccountsMarginAccountResponse {
    std::optional<std::string> total_asset_of_btc;
    std::optional<std::string> total_liability_of_btc;
    std::optional<std::string> total_net_asset_of_btc;
    std::optional<std::vector<GetSummaryOfSubAccountsMarginAccountResponseSubAccountListInner>>
        sub_account_list;

    bool operator==(const GetSummaryOfSubAccountsMarginAccountResponse& /*other*/) const = default;
};

BINANCE_SUB_ACCOUNT_EXPORT GetSummaryOfSubAccountsMarginAccountResponse
tag_invoke(boost::json::value_to_tag<GetSummaryOfSubAccountsMarginAccountResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_SUB_ACCOUNT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           const GetSummaryOfSubAccountsMarginAccountResponse& v);

} // namespace binance::sub_account::rest_api
