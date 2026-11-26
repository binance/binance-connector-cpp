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

struct
    QueryManagedSubAccountTransferLogMasterAccountInvestorResponseManagerSubTransferHistoryVosInner {
    std::optional<std::string> from_email;
    std::optional<std::string> from_account_type;
    std::optional<std::string> to_email;
    std::optional<std::string> to_account_type;
    std::optional<std::string> asset;
    std::optional<std::string> amount;
    std::optional<std::int64_t> scheduled_data;
    std::optional<std::int64_t> create_time;
    std::optional<std::string> status;
    std::optional<std::int64_t> tran_id;

    bool operator==(
        const QueryManagedSubAccountTransferLogMasterAccountInvestorResponseManagerSubTransferHistoryVosInner& /*other*/)
        const = default;
};

BINANCE_SUB_ACCOUNT_EXPORT
QueryManagedSubAccountTransferLogMasterAccountInvestorResponseManagerSubTransferHistoryVosInner
tag_invoke(
    boost::json::value_to_tag<
        QueryManagedSubAccountTransferLogMasterAccountInvestorResponseManagerSubTransferHistoryVosInner> /*tag*/
    ,
    const boost::json::value& jv);
BINANCE_SUB_ACCOUNT_EXPORT void tag_invoke(
    boost::json::value_from_tag /*tag*/, boost::json::value& jv,
    const QueryManagedSubAccountTransferLogMasterAccountInvestorResponseManagerSubTransferHistoryVosInner&
        v);

} // namespace binance::sub_account::rest_api
