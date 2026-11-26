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

#include <binance/dual_investment/export.hpp>

namespace binance::dual_investment::rest_api {

struct CheckDualInvestmentAccountsResponse {
    /// Total BTC amount in Dual Investment
    std::optional<std::string> total_amount_in_btc;
    /// Total USDT equivalent amount in Dual Investment
    std::optional<std::string> total_amount_in_usdt;

    bool operator==(const CheckDualInvestmentAccountsResponse& /*other*/) const = default;
};

BINANCE_DUAL_INVESTMENT_EXPORT CheckDualInvestmentAccountsResponse
tag_invoke(boost::json::value_to_tag<CheckDualInvestmentAccountsResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_DUAL_INVESTMENT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                               boost::json::value& jv,
                                               const CheckDualInvestmentAccountsResponse& v);

} // namespace binance::dual_investment::rest_api
