//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <optional>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/derivatives_trading_usds_futures/export.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

struct GetCurrentMultiAssetsModeResponse {
    /// "true": Multi-Assets Mode; "false": Single-Asset Mode
    std::optional<bool> multi_assets_margin;

    bool operator==(const GetCurrentMultiAssetsModeResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT GetCurrentMultiAssetsModeResponse
tag_invoke(boost::json::value_to_tag<GetCurrentMultiAssetsModeResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetCurrentMultiAssetsModeResponse& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
