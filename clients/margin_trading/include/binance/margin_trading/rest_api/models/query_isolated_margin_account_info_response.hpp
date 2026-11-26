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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/margin_trading/export.hpp>
#include <binance/margin_trading/rest_api/models/query_isolated_margin_account_info_response_assets_inner.hpp>

namespace binance::margin_trading::rest_api {

struct QueryIsolatedMarginAccountInfoResponse {
    /// assets list.
    std::optional<std::vector<QueryIsolatedMarginAccountInfoResponseAssetsInner>> assets;
    /// total Asset Of Btc.
    std::optional<std::string> total_asset_of_btc;
    /// total Liability Of Btc.
    std::optional<std::string> total_liability_of_btc;
    /// total Net Asset Of Btc.
    std::optional<std::string> total_net_asset_of_btc;

    bool operator==(const QueryIsolatedMarginAccountInfoResponse& /*other*/) const = default;
};

BINANCE_MARGIN_TRADING_EXPORT QueryIsolatedMarginAccountInfoResponse
tag_invoke(boost::json::value_to_tag<QueryIsolatedMarginAccountInfoResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const QueryIsolatedMarginAccountInfoResponse& v);

} // namespace binance::margin_trading::rest_api
