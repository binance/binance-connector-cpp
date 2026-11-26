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

struct GetUserCommissionRateForUmResponse {
    /// Trade symbol, if existing.
    std::optional<std::string> symbol;
    /// 0.02%
    std::optional<std::string> maker_commission_rate;
    /// 0.04%
    std::optional<std::string> taker_commission_rate;

    bool operator==(const GetUserCommissionRateForUmResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT GetUserCommissionRateForUmResponse
tag_invoke(boost::json::value_to_tag<GetUserCommissionRateForUmResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetUserCommissionRateForUmResponse& v);

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
