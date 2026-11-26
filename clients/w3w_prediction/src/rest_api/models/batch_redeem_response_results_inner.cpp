//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/w3w_prediction/rest_api/models/batch_redeem_response_results_inner.hpp>

namespace binance::w3w_prediction::rest_api {

BatchRedeemResponseResultsInner
tag_invoke(boost::json::value_to_tag<BatchRedeemResponseResultsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "BatchRedeemResponseResultsInner");
    BatchRedeemResponseResultsInner out;
    common::detail::json::read(obj, "requestId", out.request_id);
    common::detail::json::read(obj, "txHash", out.tx_hash);
    common::detail::json::read(obj, "status", out.status);
    common::detail::json::read(obj, "error", out.error);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const BatchRedeemResponseResultsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "requestId", v.request_id);
    common::detail::json::write(obj, "txHash", v.tx_hash);
    common::detail::json::write(obj, "status", v.status);
    common::detail::json::write(obj, "error", v.error);
}

} // namespace binance::w3w_prediction::rest_api
