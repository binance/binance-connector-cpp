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

struct DepositHistoryResponseInner {
    std::optional<std::string> id;
    std::optional<std::string> amount;
    std::optional<std::string> coin;
    std::optional<std::string> network;
    std::optional<std::int64_t> status;
    std::optional<std::string> address;
    std::optional<std::string> address_tag;
    std::optional<std::string> tx_id;
    std::optional<std::int64_t> insert_time;
    /// represents deposit completion datetime, available for deposits after 6-Mar-2025.
    std::optional<std::int64_t> complete_time;
    std::optional<std::int64_t> transfer_type;
    std::optional<std::string> confirm_times;
    std::optional<std::int64_t> unlock_confirm;
    std::optional<std::int64_t> wallet_type;
    /// 0: travel rule not required OR info already provided and funds ready to use, 1: travel rule
    /// required to provide deposit info
    std::optional<std::int64_t> travel_rule_status;

    bool operator==(const DepositHistoryResponseInner& /*other*/) const = default;
};

BINANCE_WALLET_EXPORT DepositHistoryResponseInner tag_invoke(
    boost::json::value_to_tag<DepositHistoryResponseInner> /*tag*/, const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const DepositHistoryResponseInner& v);

} // namespace binance::wallet::rest_api
