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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/sub_account/export.hpp>
#include <binance/sub_account/rest_api/models/get_detail_on_sub_accounts_futures_account_response_assets_inner.hpp>

namespace binance::sub_account::rest_api {

struct GetDetailOnSubAccountsFuturesAccountResponse {
    std::optional<std::string> email;
    std::optional<std::string> asset;
    std::optional<std::vector<GetDetailOnSubAccountsFuturesAccountResponseAssetsInner>> assets;
    std::optional<bool> can_deposit;
    std::optional<bool> can_trade;
    std::optional<bool> can_withdraw;
    std::optional<std::int64_t> fee_tier;
    std::optional<std::string> max_withdraw_amount;
    std::optional<std::string> total_initial_margin;
    std::optional<std::string> total_maintenance_margin;
    std::optional<std::string> total_margin_balance;
    std::optional<std::string> total_open_order_initial_margin;
    std::optional<std::string> total_position_initial_margin;
    std::optional<std::string> total_unrealized_profit;
    std::optional<std::string> total_wallet_balance;
    std::optional<std::int64_t> update_time;

    bool operator==(const GetDetailOnSubAccountsFuturesAccountResponse& /*other*/) const = default;
};

BINANCE_SUB_ACCOUNT_EXPORT GetDetailOnSubAccountsFuturesAccountResponse
tag_invoke(boost::json::value_to_tag<GetDetailOnSubAccountsFuturesAccountResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_SUB_ACCOUNT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           const GetDetailOnSubAccountsFuturesAccountResponse& v);

} // namespace binance::sub_account::rest_api
