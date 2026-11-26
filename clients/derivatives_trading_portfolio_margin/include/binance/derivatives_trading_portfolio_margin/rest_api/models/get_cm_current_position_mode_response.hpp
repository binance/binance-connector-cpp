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

struct GetCmCurrentPositionModeResponse {
    /// "true": Hedge Mode; "false": One-way Mode
    std::optional<bool> dual_side_position;

    bool operator==(const GetCmCurrentPositionModeResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT GetCmCurrentPositionModeResponse
tag_invoke(boost::json::value_to_tag<GetCmCurrentPositionModeResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetCmCurrentPositionModeResponse& v);

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
