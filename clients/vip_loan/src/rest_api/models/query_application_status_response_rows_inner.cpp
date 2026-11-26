//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/vip_loan/rest_api/models/query_application_status_response_rows_inner.hpp>

namespace binance::vip_loan::rest_api {

QueryApplicationStatusResponseRowsInner
tag_invoke(boost::json::value_to_tag<QueryApplicationStatusResponseRowsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "QueryApplicationStatusResponseRowsInner");
    QueryApplicationStatusResponseRowsInner out;
    common::detail::json::read(obj, "loanAccountId", out.loan_account_id);
    common::detail::json::read(obj, "orderId", out.order_id);
    common::detail::json::read(obj, "requestId", out.request_id);
    common::detail::json::read(obj, "loanCoin", out.loan_coin);
    common::detail::json::read(obj, "loanAmount", out.loan_amount);
    common::detail::json::read(obj, "collateralAccountId", out.collateral_account_id);
    common::detail::json::read(obj, "collateralCoin", out.collateral_coin);
    common::detail::json::read(obj, "loanTerm", out.loan_term);
    common::detail::json::read(obj, "status", out.status);
    common::detail::json::read(obj, "loanDate", out.loan_date);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryApplicationStatusResponseRowsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "loanAccountId", v.loan_account_id);
    common::detail::json::write(obj, "orderId", v.order_id);
    common::detail::json::write(obj, "requestId", v.request_id);
    common::detail::json::write(obj, "loanCoin", v.loan_coin);
    common::detail::json::write(obj, "loanAmount", v.loan_amount);
    common::detail::json::write(obj, "collateralAccountId", v.collateral_account_id);
    common::detail::json::write(obj, "collateralCoin", v.collateral_coin);
    common::detail::json::write(obj, "loanTerm", v.loan_term);
    common::detail::json::write(obj, "status", v.status);
    common::detail::json::write(obj, "loanDate", v.loan_date);
}

} // namespace binance::vip_loan::rest_api
