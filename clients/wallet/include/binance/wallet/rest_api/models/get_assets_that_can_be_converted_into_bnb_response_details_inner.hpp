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

struct GetAssetsThatCanBeConvertedIntoBnbResponseDetailsInner {
    std::optional<std::string> asset;
    std::optional<std::string> asset_full_name;
    /// Convertible amount
    std::optional<std::string> amount_free;
    /// BTC amount
    std::optional<std::string> to_btc;
    /// BNB amount（Not deducted commission fee）
    std::optional<std::string> to_bnb;
    /// BNB amount（Deducted commission fee）
    std::optional<std::string> to_bnb_off_exchange;
    /// Commission fee
    std::optional<std::string> exchange;

    bool operator==(const GetAssetsThatCanBeConvertedIntoBnbResponseDetailsInner& /*other*/) const =
        default;
};

BINANCE_WALLET_EXPORT GetAssetsThatCanBeConvertedIntoBnbResponseDetailsInner tag_invoke(
    boost::json::value_to_tag<GetAssetsThatCanBeConvertedIntoBnbResponseDetailsInner> /*tag*/,
    const boost::json::value& jv);
BINANCE_WALLET_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetAssetsThatCanBeConvertedIntoBnbResponseDetailsInner& v);

} // namespace binance::wallet::rest_api
