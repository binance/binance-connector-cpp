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

struct WithdrawHistoryResponseInner {
    /// Withdrawal id in Binance
    std::optional<std::string> id;
    /// withdrawal amount
    std::optional<std::string> amount;
    /// transaction fee
    std::optional<std::string> transaction_fee;
    std::optional<std::string> coin;
    std::optional<std::int64_t> status;
    std::optional<std::string> address;
    /// withdrawal transaction id
    std::optional<std::string> tx_id;
    /// UTC time
    std::optional<std::string> apply_time;
    std::optional<std::string> network;
    /// 1 for internal transfer, 0 for external transfer
    std::optional<std::int64_t> transfer_type;
    /// will not be returned if there's no withdrawOrderId for this withdraw.
    std::optional<std::string> withdraw_order_id;
    /// reason for withdrawal failure
    std::optional<std::string> info;
    /// confirm times for withdraw
    std::optional<std::int64_t> confirm_no;
    /// 1: Funding Wallet 0:Spot Wallet
    std::optional<std::int64_t> wallet_type;
    std::optional<std::string> tx_key;
    /// complete UTC time when user's asset is deduct from withdrawing, only if status =  6(success)
    std::optional<std::string> complete_time;

    bool operator==(const WithdrawHistoryResponseInner& /*other*/) const = default;
};

BINANCE_WALLET_EXPORT WithdrawHistoryResponseInner tag_invoke(
    boost::json::value_to_tag<WithdrawHistoryResponseInner> /*tag*/, const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const WithdrawHistoryResponseInner& v);

} // namespace binance::wallet::rest_api
