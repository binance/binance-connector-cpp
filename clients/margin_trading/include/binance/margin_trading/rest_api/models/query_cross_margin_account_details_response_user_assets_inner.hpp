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

struct QueryCrossMarginAccountDetailsResponseUserAssetsInner {
    /// asset.
    std::optional<std::string> asset;
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

    bool operator==(const QueryCrossMarginAccountDetailsResponseUserAssetsInner& /*other*/) const =
        default;
};

BINANCE_MARGIN_TRADING_EXPORT QueryCrossMarginAccountDetailsResponseUserAssetsInner
tag_invoke(boost::json::value_to_tag<QueryCrossMarginAccountDetailsResponseUserAssetsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const QueryCrossMarginAccountDetailsResponseUserAssetsInner& v);

} // namespace binance::margin_trading::rest_api
