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

#include <binance/derivatives_trading_portfolio_margin/export.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

struct QueryMarginMaxWithdrawResponse {
    /// account's currently max withdrawable amount with sufficient system availability
    std::optional<std::string> amount;

    bool operator==(const QueryMarginMaxWithdrawResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT QueryMarginMaxWithdrawResponse
tag_invoke(boost::json::value_to_tag<QueryMarginMaxWithdrawResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const QueryMarginMaxWithdrawResponse& v);

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
