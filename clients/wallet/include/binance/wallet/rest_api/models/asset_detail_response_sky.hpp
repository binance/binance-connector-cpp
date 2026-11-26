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

#include <binance/common/decimal.hpp>
#include <binance/wallet/export.hpp>

namespace binance::wallet::rest_api {

struct AssetDetailResponseSKY {
    /// min withdraw amount
    std::optional<std::string> min_withdraw_amount;
    /// deposit status (false if ALL of networks' are false)
    std::optional<bool> deposit_status;
    /// withdraw fee
    std::optional<common::Decimal> withdraw_fee;
    /// withdraw status (false if ALL of networks' are false)
    std::optional<bool> withdraw_status;

    bool operator==(const AssetDetailResponseSKY& /*other*/) const = default;
};

BINANCE_WALLET_EXPORT AssetDetailResponseSKY
tag_invoke(boost::json::value_to_tag<AssetDetailResponseSKY> /*tag*/, const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const AssetDetailResponseSKY& v);

} // namespace binance::wallet::rest_api
