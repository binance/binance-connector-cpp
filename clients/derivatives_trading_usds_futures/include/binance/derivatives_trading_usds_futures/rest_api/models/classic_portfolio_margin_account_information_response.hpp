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

#include <binance/derivatives_trading_usds_futures/export.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

struct ClassicPortfolioMarginAccountInformationResponse {
    /// Classic Portfolio margin maximum virtual amount for transfer out in USD
    std::optional<std::string> max_withdraw_amount_usd;
    /// asset name
    std::optional<std::string> asset;
    /// maximum amount for transfer out
    std::optional<std::string> max_withdraw_amount;

    bool
    operator==(const ClassicPortfolioMarginAccountInformationResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT ClassicPortfolioMarginAccountInformationResponse
tag_invoke(boost::json::value_to_tag<ClassicPortfolioMarginAccountInformationResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const ClassicPortfolioMarginAccountInformationResponse& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
