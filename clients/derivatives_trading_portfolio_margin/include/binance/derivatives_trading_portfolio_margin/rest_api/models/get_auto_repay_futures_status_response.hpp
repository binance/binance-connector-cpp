//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <optional>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/derivatives_trading_portfolio_margin/export.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

struct GetAutoRepayFuturesStatusResponse {
    /// "true" for turn on the auto-repay futures; "false" for turn off the auto-repay futures
    std::optional<bool> auto_repay;

    bool operator==(const GetAutoRepayFuturesStatusResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT GetAutoRepayFuturesStatusResponse
tag_invoke(boost::json::value_to_tag<GetAutoRepayFuturesStatusResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetAutoRepayFuturesStatusResponse& v);

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
