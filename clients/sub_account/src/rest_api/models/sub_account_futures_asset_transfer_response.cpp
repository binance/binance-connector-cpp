//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/sub_account/rest_api/models/sub_account_futures_asset_transfer_response.hpp>

namespace binance::sub_account::rest_api {

SubAccountFuturesAssetTransferResponse
tag_invoke(boost::json::value_to_tag<SubAccountFuturesAssetTransferResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "SubAccountFuturesAssetTransferResponse");
    SubAccountFuturesAssetTransferResponse out;
    common::detail::json::read(obj, "success", out.success);
    common::detail::json::read(obj, "txnId", out.txn_id);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const SubAccountFuturesAssetTransferResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "success", v.success);
    common::detail::json::write(obj, "txnId", v.txn_id);
}

} // namespace binance::sub_account::rest_api
