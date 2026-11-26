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

#include <binance/wallet/export.hpp>
#include <binance/wallet/rest_api/models/query_user_delegation_history_response_rows_inner.hpp>

namespace binance::wallet::rest_api {

struct QueryUserDelegationHistoryResponse {
    std::optional<std::int64_t> total;
    std::optional<std::vector<QueryUserDelegationHistoryResponseRowsInner>> rows;

    bool operator==(const QueryUserDelegationHistoryResponse& /*other*/) const = default;
};

BINANCE_WALLET_EXPORT QueryUserDelegationHistoryResponse
tag_invoke(boost::json::value_to_tag<QueryUserDelegationHistoryResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const QueryUserDelegationHistoryResponse& v);

} // namespace binance::wallet::rest_api
