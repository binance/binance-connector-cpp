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

#include <binance/derivatives_trading_portfolio_margin_pro/export.hpp>

namespace binance::derivatives_trading_portfolio_margin_pro::rest_api {

struct GetMarginCallLevelResponse {
    /// The margin call level value. Empty object returned if not set.
    std::optional<std::string> margin_call_level;

    bool operator==(const GetMarginCallLevelResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_PRO_EXPORT GetMarginCallLevelResponse tag_invoke(
    boost::json::value_to_tag<GetMarginCallLevelResponse> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_PRO_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetMarginCallLevelResponse& v);

} // namespace binance::derivatives_trading_portfolio_margin_pro::rest_api
