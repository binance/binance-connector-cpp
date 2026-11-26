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
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/um_position_adl_quantile_estimation_response_inner_adl_quantile.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

struct UmPositionAdlQuantileEstimationResponseInner {
    /// Trade symbol, if existing.
    std::optional<std::string> symbol;
    std::optional<UmPositionAdlQuantileEstimationResponseInnerAdlQuantile> adl_quantile;

    bool operator==(const UmPositionAdlQuantileEstimationResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT UmPositionAdlQuantileEstimationResponseInner
tag_invoke(boost::json::value_to_tag<UmPositionAdlQuantileEstimationResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const UmPositionAdlQuantileEstimationResponseInner& v);

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
