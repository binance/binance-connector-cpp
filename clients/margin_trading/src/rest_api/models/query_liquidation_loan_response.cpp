//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/margin_trading/rest_api/models/query_liquidation_loan_response.hpp>

namespace binance::margin_trading::rest_api {

QueryLiquidationLoanResponse
tag_invoke(boost::json::value_to_tag<QueryLiquidationLoanResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "QueryLiquidationLoanResponse");
    QueryLiquidationLoanResponse out;
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "amount", out.amount);
    common::detail::json::read(obj, "repaidAmount", out.repaid_amount);
    common::detail::json::read(obj, "remainingAmount", out.remaining_amount);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryLiquidationLoanResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "amount", v.amount);
    common::detail::json::write(obj, "repaidAmount", v.repaid_amount);
    common::detail::json::write(obj, "remainingAmount", v.remaining_amount);
}

} // namespace binance::margin_trading::rest_api
