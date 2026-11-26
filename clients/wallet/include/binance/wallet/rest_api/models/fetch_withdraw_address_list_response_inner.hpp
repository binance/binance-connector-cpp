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

struct FetchWithdrawAddressListResponseInner {
    std::optional<std::string> address;
    std::optional<std::string> address_tag;
    std::optional<std::string> coin;
    /// is a user-defined name
    std::optional<std::string> name;
    std::optional<std::string> network;
    /// if originType != 'others', this value is blank, otherwise the origin is manually filled in
    /// by the user
    std::optional<std::string> origin;
    /// Address source type, including but not limited to: type Exchange Address: Binance, CoinBase,
    /// HTX, Bitfinex, OKX, Bithumb, Kraken, Kucoin, Gemini, Bitget, Bybit, Upbit, Gate.io;  type
    /// Wallet Address: Binance Web3 Wallet, Trust Wallet, MetaMask, Rabby Wallet, Phantom, OKX Web
    /// 3 Wallet, Coinbase Wallet, Bitget Wallet; type Others: others(multilanguage support)
    std::optional<std::string> origin_type;
    /// Is it whitelisted
    std::optional<bool> white_status;

    bool operator==(const FetchWithdrawAddressListResponseInner& /*other*/) const = default;
};

BINANCE_WALLET_EXPORT FetchWithdrawAddressListResponseInner
tag_invoke(boost::json::value_to_tag<FetchWithdrawAddressListResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const FetchWithdrawAddressListResponseInner& v);

} // namespace binance::wallet::rest_api
