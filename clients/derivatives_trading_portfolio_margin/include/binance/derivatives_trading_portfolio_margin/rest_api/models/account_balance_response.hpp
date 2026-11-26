//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <variant>
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/derivatives_trading_portfolio_margin/export.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/account_balance_response1_inner.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/account_balance_response2.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

struct AccountBalanceResponse {
    /// One of the alternatives, or the raw JSON when none matches.
    std::variant<std::vector<AccountBalanceResponse1Inner>, AccountBalanceResponse2,
                 boost::json::value>
        value;

    bool operator==(const AccountBalanceResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT AccountBalanceResponse
tag_invoke(boost::json::value_to_tag<AccountBalanceResponse> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const AccountBalanceResponse& v);

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
