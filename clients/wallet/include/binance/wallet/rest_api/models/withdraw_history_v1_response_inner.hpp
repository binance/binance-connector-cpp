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

struct WithdrawHistoryV1ResponseInner {
    /// Withdrawal id in Binance
    std::optional<std::string> id;
    /// Travel rule record id
    std::optional<std::int64_t> tr_id;
    /// withdrawal amount
    std::optional<std::string> amount;
    /// only available for sAPI requests
    std::optional<std::string> transaction_fee;
    std::optional<std::string> coin;
    /// Capital withdrawal status, only available for sAPI requests
    std::optional<std::int64_t> withdrawal_status;
    /// Travel rule status.
    std::optional<std::int64_t> travel_rule_status;
    std::optional<std::string> address;
    /// withdrawal transaction id
    std::optional<std::string> tx_id;
    /// UTC time
    std::optional<std::string> apply_time;
    std::optional<std::string> network;
    /// 1 for internal transfer, 0 for external transfer, only available for sAPI requests
    std::optional<std::int64_t> transfer_type;
    /// will not be returned if there's no withdrawOrderId for this withdraw, only available for
    /// sAPI requests
    std::optional<std::string> withdraw_order_id;
    /// reason for withdrawal failure, only available for sAPI requests
    std::optional<std::string> info;
    /// confirm times for withdraw, only available for sAPI requests
    std::optional<std::int64_t> confirm_no;
    /// 1: Funding Wallet 0:Spot Wallet, only available for sAPI requests
    std::optional<std::int64_t> wallet_type;
    /// only available for sAPI requests
    std::optional<std::string> tx_key;
    /// The answers of the questionnaire
    std::optional<std::string> questionnaire;
    /// complete UTC time when user's asset is deduct from withdrawing, only if status =  6(success)
    std::optional<std::string> complete_time;

    bool operator==(const WithdrawHistoryV1ResponseInner& /*other*/) const = default;
};

BINANCE_WALLET_EXPORT WithdrawHistoryV1ResponseInner
tag_invoke(boost::json::value_to_tag<WithdrawHistoryV1ResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const WithdrawHistoryV1ResponseInner& v);

} // namespace binance::wallet::rest_api
