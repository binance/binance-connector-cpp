//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/w3w_prediction/rest_api/models/batch_redeem_response.hpp>

namespace binance::w3w_prediction::rest_api {

BatchRedeemResponse tag_invoke(boost::json::value_to_tag<BatchRedeemResponse> /*tag*/,
                               const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "BatchRedeemResponse");
    BatchRedeemResponse out;
    common::detail::json::read(obj, "batchId", out.batch_id);
    common::detail::json::read(obj, "results", out.results);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const BatchRedeemResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "batchId", v.batch_id);
    common::detail::json::write(obj, "results", v.results);
}

} // namespace binance::w3w_prediction::rest_api
