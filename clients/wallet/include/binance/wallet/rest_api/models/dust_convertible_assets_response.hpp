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

#include <binance/wallet/export.hpp>
#include <binance/wallet/rest_api/models/dust_convertible_assets_response_details_inner.hpp>

namespace binance::wallet::rest_api {

struct DustConvertibleAssetsResponse {
    std::optional<std::string> dribblet_percentage;
    std::optional<std::string> total_transfer_quota_asset_amount;
    std::optional<std::string> total_transfer_target_asset_amount;
    std::optional<std::string> dribblet_base;
    std::optional<std::vector<DustConvertibleAssetsResponseDetailsInner>> details;

    bool operator==(const DustConvertibleAssetsResponse& /*other*/) const = default;
};

BINANCE_WALLET_EXPORT DustConvertibleAssetsResponse tag_invoke(
    boost::json::value_to_tag<DustConvertibleAssetsResponse> /*tag*/, const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const DustConvertibleAssetsResponse& v);

} // namespace binance::wallet::rest_api
