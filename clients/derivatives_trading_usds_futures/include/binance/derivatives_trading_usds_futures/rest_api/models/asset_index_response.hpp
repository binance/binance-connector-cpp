//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <variant>
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/derivatives_trading_usds_futures/export.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/asset_index_response1.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/asset_index_response2_inner.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

struct AssetIndexResponse {
    /// One of the alternatives, or the raw JSON when none matches.
    std::variant<AssetIndexResponse1, std::vector<AssetIndexResponse2Inner>, boost::json::value>
        value;

    bool operator==(const AssetIndexResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT AssetIndexResponse
tag_invoke(boost::json::value_to_tag<AssetIndexResponse> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                                boost::json::value& jv,
                                                                const AssetIndexResponse& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
