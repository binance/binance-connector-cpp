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

struct NewMarginOrderResponseFillsInner {
    /// Price.
    std::optional<std::string> price;
    /// Qty.
    std::optional<std::string> qty;
    /// Commission.
    std::optional<std::string> commission;
    /// Commission Asset.
    std::optional<std::string> commission_asset;

    bool operator==(const NewMarginOrderResponseFillsInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT NewMarginOrderResponseFillsInner
tag_invoke(boost::json::value_to_tag<NewMarginOrderResponseFillsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const NewMarginOrderResponseFillsInner& v);

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
