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

struct GetSummaryOfSubAccountsFuturesAccountResponseSubAccountListInner {
    std::optional<std::string> email;
    std::optional<std::string> total_initial_margin;
    std::optional<std::string> total_maintenance_margin;
    std::optional<std::string> total_margin_balance;
    std::optional<std::string> total_open_order_initial_margin;
    std::optional<std::string> total_position_initial_margin;
    std::optional<std::string> total_unrealized_profit;
    std::optional<std::string> total_wallet_balance;
    /// The sum of BUSD and USDT
    std::optional<std::string> asset;

    bool
    operator==(const GetSummaryOfSubAccountsFuturesAccountResponseSubAccountListInner& /*other*/)
        const = default;
};

BINANCE_SUB_ACCOUNT_EXPORT GetSummaryOfSubAccountsFuturesAccountResponseSubAccountListInner
tag_invoke(boost::json::value_to_tag<
               GetSummaryOfSubAccountsFuturesAccountResponseSubAccountListInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_SUB_ACCOUNT_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetSummaryOfSubAccountsFuturesAccountResponseSubAccountListInner& v);

} // namespace binance::sub_account::rest_api
