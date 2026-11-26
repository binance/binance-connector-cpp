//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/vip_loan/rest_api/models/vip_loan_fixed_rate_borrow_response.hpp>

namespace binance::vip_loan::rest_api {

VipLoanFixedRateBorrowResponse
tag_invoke(boost::json::value_to_tag<VipLoanFixedRateBorrowResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "VipLoanFixedRateBorrowResponse");
    VipLoanFixedRateBorrowResponse out;
    common::detail::json::read(obj, "borrowCoin", out.borrow_coin);
    common::detail::json::read(obj, "borrowAmount", out.borrow_amount);
    common::detail::json::read(obj, "actualReceivedAmount", out.actual_received_amount);
    common::detail::json::read(obj, "collateralCoin", out.collateral_coin);
    common::detail::json::read(obj, "collateralAccountId", out.collateral_account_id);
    common::detail::json::read(obj, "borrowInterestRate", out.borrow_interest_rate);
    common::detail::json::read(obj, "duration", out.duration);
    common::detail::json::read(obj, "autoRepay", out.auto_repay);
    common::detail::json::read(obj, "orderId", out.order_id);
    common::detail::json::read(obj, "status", out.status);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const VipLoanFixedRateBorrowResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "borrowCoin", v.borrow_coin);
    common::detail::json::write(obj, "borrowAmount", v.borrow_amount);
    common::detail::json::write(obj, "actualReceivedAmount", v.actual_received_amount);
    common::detail::json::write(obj, "collateralCoin", v.collateral_coin);
    common::detail::json::write(obj, "collateralAccountId", v.collateral_account_id);
    common::detail::json::write(obj, "borrowInterestRate", v.borrow_interest_rate);
    common::detail::json::write(obj, "duration", v.duration);
    common::detail::json::write(obj, "autoRepay", v.auto_repay);
    common::detail::json::write(obj, "orderId", v.order_id);
    common::detail::json::write(obj, "status", v.status);
}

} // namespace binance::vip_loan::rest_api
