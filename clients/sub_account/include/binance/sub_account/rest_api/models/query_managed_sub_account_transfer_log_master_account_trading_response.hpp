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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/sub_account/export.hpp>
#include <binance/sub_account/rest_api/models/query_managed_sub_account_transfer_log_master_account_investor_response_manager_sub_transfer_history_vos_inner.hpp>

namespace binance::sub_account::rest_api {

struct QueryManagedSubAccountTransferLogMasterAccountTradingResponse {
    std::optional<std::vector<
        QueryManagedSubAccountTransferLogMasterAccountInvestorResponseManagerSubTransferHistoryVosInner>>
        manager_sub_transfer_history_vos;
    std::optional<std::int64_t> count;

    bool operator==(const QueryManagedSubAccountTransferLogMasterAccountTradingResponse& /*other*/)
        const = default;
};

BINANCE_SUB_ACCOUNT_EXPORT QueryManagedSubAccountTransferLogMasterAccountTradingResponse
tag_invoke(boost::json::value_to_tag<
               QueryManagedSubAccountTransferLogMasterAccountTradingResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_SUB_ACCOUNT_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const QueryManagedSubAccountTransferLogMasterAccountTradingResponse& v);

} // namespace binance::sub_account::rest_api
