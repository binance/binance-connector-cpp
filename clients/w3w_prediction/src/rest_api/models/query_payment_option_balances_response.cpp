//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/w3w_prediction/rest_api/models/query_payment_option_balances_response.hpp>

namespace binance::w3w_prediction::rest_api {

QueryPaymentOptionBalancesResponse
tag_invoke(boost::json::value_to_tag<QueryPaymentOptionBalancesResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "QueryPaymentOptionBalancesResponse");
    QueryPaymentOptionBalancesResponse out;
    common::detail::json::read(obj, "items", out.items);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryPaymentOptionBalancesResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "items", v.items);
}

} // namespace binance::w3w_prediction::rest_api
