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
#include <binance/sub_account/rest_api/models/get_detail_on_sub_accounts_margin_account_response_margin_trade_coeff_vo.hpp>
#include <binance/sub_account/rest_api/models/get_detail_on_sub_accounts_margin_account_response_margin_user_asset_vo_list_inner.hpp>

namespace binance::sub_account::rest_api {

struct GetDetailOnSubAccountsMarginAccountResponse {
    std::optional<std::string> email;
    std::optional<std::string> margin_level;
    std::optional<std::string> total_asset_of_btc;
    std::optional<std::string> total_liability_of_btc;
    std::optional<std::string> total_net_asset_of_btc;
    std::optional<GetDetailOnSubAccountsMarginAccountResponseMarginTradeCoeffVo>
        margin_trade_coeff_vo;
    std::optional<
        std::vector<GetDetailOnSubAccountsMarginAccountResponseMarginUserAssetVoListInner>>
        margin_user_asset_vo_list;

    bool operator==(const GetDetailOnSubAccountsMarginAccountResponse& /*other*/) const = default;
};

BINANCE_SUB_ACCOUNT_EXPORT GetDetailOnSubAccountsMarginAccountResponse
tag_invoke(boost::json::value_to_tag<GetDetailOnSubAccountsMarginAccountResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_SUB_ACCOUNT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           const GetDetailOnSubAccountsMarginAccountResponse& v);

} // namespace binance::sub_account::rest_api
