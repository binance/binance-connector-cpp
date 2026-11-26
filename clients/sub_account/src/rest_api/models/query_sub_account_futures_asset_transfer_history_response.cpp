//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/sub_account/rest_api/models/query_sub_account_futures_asset_transfer_history_response.hpp>

namespace binance::sub_account::rest_api {

QuerySubAccountFuturesAssetTransferHistoryResponse
tag_invoke(boost::json::value_to_tag<QuerySubAccountFuturesAssetTransferHistoryResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "QuerySubAccountFuturesAssetTransferHistoryResponse");
    QuerySubAccountFuturesAssetTransferHistoryResponse out;
    common::detail::json::read(obj, "success", out.success);
    common::detail::json::read(obj, "futuresType", out.futures_type);
    common::detail::json::read(obj, "transfers", out.transfers);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QuerySubAccountFuturesAssetTransferHistoryResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "success", v.success);
    common::detail::json::write(obj, "futuresType", v.futures_type);
    common::detail::json::write(obj, "transfers", v.transfers);
}

} // namespace binance::sub_account::rest_api
