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

struct CompositeIndexSymbolInformationResponseInnerBaseAssetListInner {
    /// Base Asset.
    std::optional<std::string> base_asset;
    /// Quote Asset.
    std::optional<std::string> quote_asset;
    /// Weight In Quantity.
    std::optional<std::string> weight_in_quantity;
    /// Weight In Percentage.
    std::optional<std::string> weight_in_percentage;

    bool operator==(const CompositeIndexSymbolInformationResponseInnerBaseAssetListInner& /*other*/)
        const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT
CompositeIndexSymbolInformationResponseInnerBaseAssetListInner
tag_invoke(boost::json::value_to_tag<
               CompositeIndexSymbolInformationResponseInnerBaseAssetListInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const CompositeIndexSymbolInformationResponseInnerBaseAssetListInner& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
