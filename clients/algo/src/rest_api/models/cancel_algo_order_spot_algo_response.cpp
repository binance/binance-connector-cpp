//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/algo/rest_api/models/cancel_algo_order_spot_algo_response.hpp>
#include <binance/common/detail/json.hpp>

namespace binance::algo::rest_api {

CancelAlgoOrderSpotAlgoResponse
tag_invoke(boost::json::value_to_tag<CancelAlgoOrderSpotAlgoResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "CancelAlgoOrderSpotAlgoResponse");
    CancelAlgoOrderSpotAlgoResponse out;
    common::detail::json::read(obj, "algoId", out.algo_id);
    common::detail::json::read(obj, "success", out.success);
    common::detail::json::read(obj, "code", out.code);
    common::detail::json::read(obj, "msg", out.msg);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const CancelAlgoOrderSpotAlgoResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "algoId", v.algo_id);
    common::detail::json::write(obj, "success", v.success);
    common::detail::json::write(obj, "code", v.code);
    common::detail::json::write(obj, "msg", v.msg);
}

} // namespace binance::algo::rest_api
