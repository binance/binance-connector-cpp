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

#include <binance/wallet/export.hpp>

namespace binance::wallet::rest_api {

struct DustConvertibleAssetsResponseDetailsInner {
    std::optional<std::string> asset;
    std::optional<std::string> asset_full_name;
    std::optional<std::string> amount_free;
    std::optional<std::string> exchange;
    std::optional<std::string> to_quota_asset_amount;
    std::optional<std::string> to_target_asset_amount;
    std::optional<std::string> to_target_asset_off_exchange;

    bool operator==(const DustConvertibleAssetsResponseDetailsInner& /*other*/) const = default;
};

BINANCE_WALLET_EXPORT DustConvertibleAssetsResponseDetailsInner
tag_invoke(boost::json::value_to_tag<DustConvertibleAssetsResponseDetailsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const DustConvertibleAssetsResponseDetailsInner& v);

} // namespace binance::wallet::rest_api
