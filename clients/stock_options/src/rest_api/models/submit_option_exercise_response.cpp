//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/stock_options/rest_api/models/submit_option_exercise_response.hpp>

namespace binance::stock_options::rest_api {

SubmitOptionExerciseResponse
tag_invoke(boost::json::value_to_tag<SubmitOptionExerciseResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "SubmitOptionExerciseResponse");
    SubmitOptionExerciseResponse out;
    common::detail::json::read(obj, "tranId", out.tran_id);
    common::detail::json::read(obj, "clientOrderId", out.client_order_id);
    common::detail::json::read(obj, "status", out.status);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const SubmitOptionExerciseResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "tranId", v.tran_id);
    common::detail::json::write(obj, "clientOrderId", v.client_order_id);
    common::detail::json::write(obj, "status", v.status);
}

} // namespace binance::stock_options::rest_api
