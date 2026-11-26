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

namespace binance::margin_trading::rest_api {

struct GetMarginRestrictedAssetsResponse {
    /// open Long Restricted Asset list.
    std::optional<std::vector<std::string>> open_long_restricted_asset;
    /// max Collateral Exceeded Asset list.
    std::optional<std::vector<std::string>> max_collateral_exceeded_asset;

    bool operator==(const GetMarginRestrictedAssetsResponse& /*other*/) const = default;
};

BINANCE_MARGIN_TRADING_EXPORT GetMarginRestrictedAssetsResponse
tag_invoke(boost::json::value_to_tag<GetMarginRestrictedAssetsResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const GetMarginRestrictedAssetsResponse& v);

} // namespace binance::margin_trading::rest_api
