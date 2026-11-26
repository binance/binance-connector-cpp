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
#include <binance/sub_account/rest_api/models/query_sub_account_futures_asset_transfer_history_response_transfers_inner.hpp>

namespace binance::sub_account::rest_api {

struct QuerySubAccountFuturesAssetTransferHistoryResponse {
    std::optional<bool> success;
    std::optional<std::int64_t> futures_type;
    std::optional<std::vector<QuerySubAccountFuturesAssetTransferHistoryResponseTransfersInner>>
        transfers;

    bool
    operator==(const QuerySubAccountFuturesAssetTransferHistoryResponse& /*other*/) const = default;
};

BINANCE_SUB_ACCOUNT_EXPORT QuerySubAccountFuturesAssetTransferHistoryResponse
tag_invoke(boost::json::value_to_tag<QuerySubAccountFuturesAssetTransferHistoryResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_SUB_ACCOUNT_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const QuerySubAccountFuturesAssetTransferHistoryResponse& v);

} // namespace binance::sub_account::rest_api
