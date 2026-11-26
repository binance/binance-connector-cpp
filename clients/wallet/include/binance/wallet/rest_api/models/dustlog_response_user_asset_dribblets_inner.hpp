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
#include <string>
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/wallet/export.hpp>
#include <binance/wallet/rest_api/models/dustlog_response_user_asset_dribblets_inner_user_asset_dribblet_details_inner.hpp>

namespace binance::wallet::rest_api {

struct DustlogResponseUserAssetDribbletsInner {
    std::optional<std::int64_t> operate_time;
    /// Total transfered BNB amount for this exchange.
    std::optional<std::string> total_transfered_amount;
    /// Total service charge amount for this exchange.
    std::optional<std::string> total_service_charge_amount;
    std::optional<std::int64_t> trans_id;
    std::optional<std::vector<DustlogResponseUserAssetDribbletsInnerUserAssetDribbletDetailsInner>>
        user_asset_dribblet_details;

    bool operator==(const DustlogResponseUserAssetDribbletsInner& /*other*/) const = default;
};

BINANCE_WALLET_EXPORT DustlogResponseUserAssetDribbletsInner
tag_invoke(boost::json::value_to_tag<DustlogResponseUserAssetDribbletsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const DustlogResponseUserAssetDribbletsInner& v);

} // namespace binance::wallet::rest_api
