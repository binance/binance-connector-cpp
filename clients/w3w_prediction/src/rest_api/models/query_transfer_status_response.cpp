//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/w3w_prediction/rest_api/models/query_transfer_status_response.hpp>

namespace binance::w3w_prediction::rest_api {

QueryTransferStatusResponse
tag_invoke(boost::json::value_to_tag<QueryTransferStatusResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "QueryTransferStatusResponse");
    QueryTransferStatusResponse out;
    common::detail::json::read(obj, "transferId", out.transfer_id);
    common::detail::json::read(obj, "direction", out.direction);
    common::detail::json::read(obj, "status", out.status);
    common::detail::json::read(obj, "fromToken", out.from_token);
    common::detail::json::read(obj, "fromTokenAmount", out.from_token_amount);
    common::detail::json::read(obj, "toToken", out.to_token);
    common::detail::json::read(obj, "toTokenAmount", out.to_token_amount);
    common::detail::json::read(obj, "errorCode", out.error_code);
    common::detail::json::read(obj, "errorMessage", out.error_message);
    common::detail::json::read(obj, "createTime", out.create_time);
    common::detail::json::read(obj, "updateTime", out.update_time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryTransferStatusResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "transferId", v.transfer_id);
    common::detail::json::write(obj, "direction", v.direction);
    common::detail::json::write(obj, "status", v.status);
    common::detail::json::write(obj, "fromToken", v.from_token);
    common::detail::json::write(obj, "fromTokenAmount", v.from_token_amount);
    common::detail::json::write(obj, "toToken", v.to_token);
    common::detail::json::write(obj, "toTokenAmount", v.to_token_amount);
    common::detail::json::write(obj, "errorCode", v.error_code);
    common::detail::json::write(obj, "errorMessage", v.error_message);
    common::detail::json::write(obj, "createTime", v.create_time);
    common::detail::json::write(obj, "updateTime", v.update_time);
}

} // namespace binance::w3w_prediction::rest_api
