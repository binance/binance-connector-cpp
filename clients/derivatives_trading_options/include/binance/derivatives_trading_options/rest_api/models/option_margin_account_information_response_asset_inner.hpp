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

#include <binance/derivatives_trading_options/export.hpp>

namespace binance::derivatives_trading_options::rest_api {

struct OptionMarginAccountInformationResponseAssetInner {
    /// asset
    std::optional<std::string> asset;
    /// margin Balance
    std::optional<std::string> margin_balance;
    /// equity
    std::optional<std::string> equity;
    /// available
    std::optional<std::string> available;
    /// initial Margin
    std::optional<std::string> initial_margin;
    /// maint Margin
    std::optional<std::string> maint_margin;
    /// unrealized PNL
    std::optional<std::string> unrealized_pnl;
    /// adjusted Equity
    std::optional<std::string> adjusted_equity;

    bool
    operator==(const OptionMarginAccountInformationResponseAssetInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT OptionMarginAccountInformationResponseAssetInner
tag_invoke(boost::json::value_to_tag<OptionMarginAccountInformationResponseAssetInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const OptionMarginAccountInformationResponseAssetInner& v);

} // namespace binance::derivatives_trading_options::rest_api
