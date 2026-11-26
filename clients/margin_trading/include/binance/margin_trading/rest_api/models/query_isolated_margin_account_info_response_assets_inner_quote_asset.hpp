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

namespace binance::margin_trading::rest_api {

/// quote Asset object.
struct QueryIsolatedMarginAccountInfoResponseAssetsInnerQuoteAsset {
    /// asset.
    std::optional<std::string> asset;
    /// borrow Enabled.
    std::optional<bool> borrow_enabled;
    /// borrowed.
    std::optional<std::string> borrowed;
    /// free.
    std::optional<std::string> free;
    /// interest.
    std::optional<std::string> interest;
    /// locked.
    std::optional<std::string> locked;
    /// net Asset.
    std::optional<std::string> net_asset;
    /// net Asset Of Btc.
    std::optional<std::string> net_asset_of_btc;
    /// repay Enabled.
    std::optional<bool> repay_enabled;
    /// total Asset.
    std::optional<std::string> total_asset;

    bool operator==(const QueryIsolatedMarginAccountInfoResponseAssetsInnerQuoteAsset& /*other*/)
        const = default;
};

BINANCE_MARGIN_TRADING_EXPORT QueryIsolatedMarginAccountInfoResponseAssetsInnerQuoteAsset
tag_invoke(
    boost::json::value_to_tag<QueryIsolatedMarginAccountInfoResponseAssetsInnerQuoteAsset> /*tag*/,
    const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const QueryIsolatedMarginAccountInfoResponseAssetsInnerQuoteAsset& v);

} // namespace binance::margin_trading::rest_api
