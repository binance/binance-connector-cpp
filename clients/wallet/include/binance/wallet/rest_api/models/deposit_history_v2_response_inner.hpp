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
#include <binance/wallet/rest_api/models/deposit_history_v2_response_inner_questionnaire.hpp>

namespace binance::wallet::rest_api {

struct DepositHistoryV2ResponseInner {
    std::optional<std::string> deposit_id;
    std::optional<std::string> amount;
    std::optional<std::string> network;
    std::optional<std::string> coin;
    std::optional<std::int64_t> deposit_status;
    /// 0:PASS,2:REJECTED,3:PENDING,-1:FAILED
    std::optional<std::int64_t> travel_rule_req_status;
    std::optional<std::string> address;
    std::optional<std::string> address_tag;
    std::optional<std::string> tx_id;
    std::optional<std::int64_t> transfer_type;
    std::optional<std::string> confirm_times;
    /// true: This deposit require user to answer questionnaire to get it credited, false: This
    /// deposit doesn't require user to answer questionnaire as it's already completed or
    /// information has been verified
    std::optional<bool> require_questionnaire;
    std::optional<DepositHistoryV2ResponseInnerQuestionnaire> questionnaire;
    std::optional<std::int64_t> insert_time;

    bool operator==(const DepositHistoryV2ResponseInner& /*other*/) const = default;
};

BINANCE_WALLET_EXPORT DepositHistoryV2ResponseInner tag_invoke(
    boost::json::value_to_tag<DepositHistoryV2ResponseInner> /*tag*/, const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const DepositHistoryV2ResponseInner& v);

} // namespace binance::wallet::rest_api
