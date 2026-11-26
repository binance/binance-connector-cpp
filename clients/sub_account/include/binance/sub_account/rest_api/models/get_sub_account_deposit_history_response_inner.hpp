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

#include <binance/sub_account/export.hpp>

namespace binance::sub_account::rest_api {

struct GetSubAccountDepositHistoryResponseInner {
    std::optional<std::string> id;
    std::optional<std::string> amount;
    std::optional<std::string> coin;
    std::optional<std::string> network;
    /// Deposit status: 0=pending, 6=credited but cannot withdraw, 7=wrong deposit, 8=waiting user
    /// confirmation, 1=success.
    std::optional<std::int64_t> status;
    std::optional<std::string> address;
    std::optional<std::string> address_tag;
    std::optional<std::string> tx_id;
    std::optional<std::int64_t> insert_time;
    std::optional<std::int64_t> transfer_type;
    std::optional<std::string> confirm_times;
    std::optional<std::int64_t> unlock_confirm;
    std::optional<std::int64_t> wallet_type;

    bool operator==(const GetSubAccountDepositHistoryResponseInner& /*other*/) const = default;
};

BINANCE_SUB_ACCOUNT_EXPORT GetSubAccountDepositHistoryResponseInner
tag_invoke(boost::json::value_to_tag<GetSubAccountDepositHistoryResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_SUB_ACCOUNT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           const GetSubAccountDepositHistoryResponseInner& v);

} // namespace binance::sub_account::rest_api
