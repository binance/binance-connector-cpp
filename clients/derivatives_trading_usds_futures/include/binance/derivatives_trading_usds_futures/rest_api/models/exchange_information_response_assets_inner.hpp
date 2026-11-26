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

/// assets information
struct ExchangeInformationResponseAssetsInner {
    std::optional<std::string> asset;
    /// whether the asset can be used as margin in Multi-Assets mode
    std::optional<bool> margin_available;
    /// auto-exchange threshold in Multi-Assets margin mode
    std::optional<std::string> auto_asset_exchange;

    bool operator==(const ExchangeInformationResponseAssetsInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT ExchangeInformationResponseAssetsInner
tag_invoke(boost::json::value_to_tag<ExchangeInformationResponseAssetsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const ExchangeInformationResponseAssetsInner& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
