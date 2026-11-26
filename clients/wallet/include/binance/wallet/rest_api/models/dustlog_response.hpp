//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <cstdint>
#include <optional>
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/wallet/export.hpp>
#include <binance/wallet/rest_api/models/dustlog_response_user_asset_dribblets_inner.hpp>

namespace binance::wallet::rest_api {

struct DustlogResponse {
    /// Total counts of exchange
    std::optional<std::int64_t> total;
    std::optional<std::vector<DustlogResponseUserAssetDribbletsInner>> user_asset_dribblets;

    bool operator==(const DustlogResponse& /*other*/) const = default;
};

BINANCE_WALLET_EXPORT DustlogResponse tag_invoke(boost::json::value_to_tag<DustlogResponse> /*tag*/,
                                                 const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const DustlogResponse& v);

} // namespace binance::wallet::rest_api
