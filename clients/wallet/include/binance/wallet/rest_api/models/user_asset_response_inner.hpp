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

struct UserAssetResponseInner {
    std::optional<std::string> asset;
    std::optional<std::string> free;
    std::optional<std::string> locked;
    std::optional<std::string> freeze;
    std::optional<std::string> withdrawing;
    std::optional<std::string> ipoable;
    std::optional<std::string> btc_valuation;

    bool operator==(const UserAssetResponseInner& /*other*/) const = default;
};

BINANCE_WALLET_EXPORT UserAssetResponseInner
tag_invoke(boost::json::value_to_tag<UserAssetResponseInner> /*tag*/, const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const UserAssetResponseInner& v);

} // namespace binance::wallet::rest_api
