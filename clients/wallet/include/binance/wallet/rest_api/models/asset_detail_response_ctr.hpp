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

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/wallet/export.hpp>

namespace binance::wallet::rest_api {

struct AssetDetailResponseCTR {
    /// min withdraw amount
    std::optional<std::string> min_withdraw_amount;
    /// deposit status (false if ALL of networks' are false)
    std::optional<bool> deposit_status;
    /// withdraw fee
    std::optional<std::int64_t> withdraw_fee;
    /// withdraw status (false if ALL of networks' are false)
    std::optional<bool> withdraw_status;
    /// reason
    std::optional<std::string> deposit_tip;

    bool operator==(const AssetDetailResponseCTR& /*other*/) const = default;
};

BINANCE_WALLET_EXPORT AssetDetailResponseCTR
tag_invoke(boost::json::value_to_tag<AssetDetailResponseCTR> /*tag*/, const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const AssetDetailResponseCTR& v);

} // namespace binance::wallet::rest_api
