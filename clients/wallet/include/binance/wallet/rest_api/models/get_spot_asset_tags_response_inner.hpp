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

namespace binance::wallet::rest_api {

struct GetSpotAssetTagsResponseInner {
    /// Asset code.
    std::optional<std::string> asset_code;
    /// Asset name.
    std::optional<std::string> asset_name;
    /// Asset trading status. This endpoint only returns `true`.
    std::optional<bool> trading;
    /// Tags configured for the asset. Returns an empty array when the asset has no tags.
    std::optional<std::vector<std::string>> tags;

    bool operator==(const GetSpotAssetTagsResponseInner& /*other*/) const = default;
};

BINANCE_WALLET_EXPORT GetSpotAssetTagsResponseInner tag_invoke(
    boost::json::value_to_tag<GetSpotAssetTagsResponseInner> /*tag*/, const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const GetSpotAssetTagsResponseInner& v);

} // namespace binance::wallet::rest_api
