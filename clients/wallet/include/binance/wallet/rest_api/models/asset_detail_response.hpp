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

#include <binance/wallet/export.hpp>
#include <binance/wallet/rest_api/models/asset_detail_response_ctr.hpp>
#include <binance/wallet/rest_api/models/asset_detail_response_sky.hpp>

namespace binance::wallet::rest_api {

struct AssetDetailResponse {
    std::optional<AssetDetailResponseCTR> ctr;
    std::optional<AssetDetailResponseSKY> sky;

    bool operator==(const AssetDetailResponse& /*other*/) const = default;
};

BINANCE_WALLET_EXPORT AssetDetailResponse
tag_invoke(boost::json::value_to_tag<AssetDetailResponse> /*tag*/, const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const AssetDetailResponse& v);

} // namespace binance::wallet::rest_api
