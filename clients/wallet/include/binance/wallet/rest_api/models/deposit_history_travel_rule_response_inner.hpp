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

struct DepositHistoryTravelRuleResponseInner {
    std::optional<std::int64_t> tr_id;
    std::optional<std::int64_t> tran_id;
    std::optional<std::string> amount;
    std::optional<std::string> coin;
    std::optional<std::string> network;
    std::optional<std::int64_t> deposit_status;
    std::optional<std::int64_t> travel_rule_status;
    /// Overall travel rule verification status (GTR + sanctions screening combined). "PASSED":
    /// verification complete, deposit released. "PENDING": verification in progress, deposit
    /// frozen. "REJECTED": verification failed.
    std::optional<std::string> travel_rule_status_v2;
    std::optional<std::string> address;
    std::optional<std::string> address_tag;
    std::optional<std::string> tx_id;
    std::optional<std::int64_t> insert_time;
    /// Timestamp when the deposit was fully completed/credited (epoch ms).
    std::optional<std::int64_t> complete_time;
    std::optional<std::int64_t> transfer_type;
    std::optional<std::string> confirm_times;
    /// true: This deposit require user to answer questionnaire to get it credited, false: This
    /// deposit doesn't require user to answer questionnaire as it's already completed or
    /// information has been verified
    std::optional<bool> require_questionnaire;
    std::optional<std::string> questionnaire;

    bool operator==(const DepositHistoryTravelRuleResponseInner& /*other*/) const = default;
};

BINANCE_WALLET_EXPORT DepositHistoryTravelRuleResponseInner
tag_invoke(boost::json::value_to_tag<DepositHistoryTravelRuleResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const DepositHistoryTravelRuleResponseInner& v);

} // namespace binance::wallet::rest_api
