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

#include <binance/margin_trading/export.hpp>
#include <binance/margin_trading/rest_api/models/query_isolated_margin_account_info_response_assets_inner_base_asset.hpp>
#include <binance/margin_trading/rest_api/models/query_isolated_margin_account_info_response_assets_inner_quote_asset.hpp>

namespace binance::margin_trading::rest_api {

struct QueryIsolatedMarginAccountInfoResponseAssetsInner {
    std::optional<QueryIsolatedMarginAccountInfoResponseAssetsInnerBaseAsset> base_asset;
    std::optional<QueryIsolatedMarginAccountInfoResponseAssetsInnerQuoteAsset> quote_asset;
    /// symbol.
    std::optional<std::string> symbol;
    /// isolated Created.
    std::optional<bool> isolated_created;
    /// true-enabled, false-disabled
    std::optional<bool> enabled;
    /// margin Level.
    std::optional<std::string> margin_level;
    /// "EXCESSIVE", "NORMAL", "MARGIN_CALL", "PRE_LIQUIDATION", "FORCE_LIQUIDATION"
    std::optional<std::string> margin_level_status;
    /// margin Ratio.
    std::optional<std::string> margin_ratio;
    /// index Price.
    std::optional<std::string> index_price;
    /// liquidate Price.
    std::optional<std::string> liquidate_price;
    /// liquidate Rate.
    std::optional<std::string> liquidate_rate;
    /// trade Enabled.
    std::optional<bool> trade_enabled;

    bool
    operator==(const QueryIsolatedMarginAccountInfoResponseAssetsInner& /*other*/) const = default;
};

BINANCE_MARGIN_TRADING_EXPORT QueryIsolatedMarginAccountInfoResponseAssetsInner
tag_invoke(boost::json::value_to_tag<QueryIsolatedMarginAccountInfoResponseAssetsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const QueryIsolatedMarginAccountInfoResponseAssetsInner& v);

} // namespace binance::margin_trading::rest_api
