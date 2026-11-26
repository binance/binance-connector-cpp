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

struct SubAccountTransferHistoryResponseInner {
    std::optional<std::string> counter_party;
    std::optional<std::string> email;
    /// 1 for transfer in, 2 for transfer out
    std::optional<std::int64_t> type;
    std::optional<std::string> asset;
    std::optional<std::string> qty;
    std::optional<std::string> from_account_type;
    std::optional<std::string> to_account_type;
    /// status: PROCESS / SUCCESS / FAILURE
    std::optional<std::string> status;
    std::optional<std::int64_t> tran_id;
    std::optional<std::int64_t> time;

    bool operator==(const SubAccountTransferHistoryResponseInner& /*other*/) const = default;
};

BINANCE_SUB_ACCOUNT_EXPORT SubAccountTransferHistoryResponseInner
tag_invoke(boost::json::value_to_tag<SubAccountTransferHistoryResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_SUB_ACCOUNT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           const SubAccountTransferHistoryResponseInner& v);

} // namespace binance::sub_account::rest_api
