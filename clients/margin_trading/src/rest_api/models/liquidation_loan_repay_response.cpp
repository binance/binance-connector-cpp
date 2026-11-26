//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/margin_trading/rest_api/models/liquidation_loan_repay_response.hpp>

namespace binance::margin_trading::rest_api {

LiquidationLoanRepayResponse
tag_invoke(boost::json::value_to_tag<LiquidationLoanRepayResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "LiquidationLoanRepayResponse");
    LiquidationLoanRepayResponse out;
    common::detail::json::read(obj, "repayId", out.repay_id);
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "amount", out.amount);
    common::detail::json::read(obj, "status", out.status);
    common::detail::json::read(obj, "createTime", out.create_time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const LiquidationLoanRepayResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "repayId", v.repay_id);
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "amount", v.amount);
    common::detail::json::write(obj, "status", v.status);
    common::detail::json::write(obj, "createTime", v.create_time);
}

} // namespace binance::margin_trading::rest_api
