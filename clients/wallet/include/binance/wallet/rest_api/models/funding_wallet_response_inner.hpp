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

struct FundingWalletResponseInner {
    std::optional<std::string> asset;
    /// avalible balance
    std::optional<std::string> free;
    /// locked asset
    std::optional<std::string> locked;
    /// freeze asset
    std::optional<std::string> freeze;
    std::optional<std::string> withdrawing;
    std::optional<std::string> btc_valuation;

    bool operator==(const FundingWalletResponseInner& /*other*/) const = default;
};

BINANCE_WALLET_EXPORT FundingWalletResponseInner tag_invoke(
    boost::json::value_to_tag<FundingWalletResponseInner> /*tag*/, const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const FundingWalletResponseInner& v);

} // namespace binance::wallet::rest_api
