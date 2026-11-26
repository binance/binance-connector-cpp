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

struct GetDetailOnSubAccountsFuturesAccountResponseAssetsInner {
    std::optional<std::string> asset;
    std::optional<std::string> initial_margin;
    std::optional<std::string> maintenance_margin;
    std::optional<std::string> margin_balance;
    std::optional<std::string> max_withdraw_amount;
    std::optional<std::string> open_order_initial_margin;
    std::optional<std::string> position_initial_margin;
    std::optional<std::string> unrealized_profit;
    std::optional<std::string> wallet_balance;

    bool operator==(
        const GetDetailOnSubAccountsFuturesAccountResponseAssetsInner& /*other*/) const = default;
};

BINANCE_SUB_ACCOUNT_EXPORT GetDetailOnSubAccountsFuturesAccountResponseAssetsInner tag_invoke(
    boost::json::value_to_tag<GetDetailOnSubAccountsFuturesAccountResponseAssetsInner> /*tag*/,
    const boost::json::value& jv);
BINANCE_SUB_ACCOUNT_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetDetailOnSubAccountsFuturesAccountResponseAssetsInner& v);

} // namespace binance::sub_account::rest_api
