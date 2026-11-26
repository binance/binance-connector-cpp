//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/dual_investment/rest_api/models/subscribe_dual_investment_products_response.hpp>

namespace binance::dual_investment::rest_api {

SubscribeDualInvestmentProductsResponse
tag_invoke(boost::json::value_to_tag<SubscribeDualInvestmentProductsResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "SubscribeDualInvestmentProductsResponse");
    SubscribeDualInvestmentProductsResponse out;
    common::detail::json::read(obj, "positionId", out.position_id);
    common::detail::json::read(obj, "investCoin", out.invest_coin);
    common::detail::json::read(obj, "exercisedCoin", out.exercised_coin);
    common::detail::json::read(obj, "subscriptionAmount", out.subscription_amount);
    common::detail::json::read(obj, "duration", out.duration);
    common::detail::json::read(obj, "autoCompoundPlan", out.auto_compound_plan);
    common::detail::json::read(obj, "strikePrice", out.strike_price);
    common::detail::json::read(obj, "settleDate", out.settle_date);
    common::detail::json::read(obj, "purchaseStatus", out.purchase_status);
    common::detail::json::read(obj, "apr", out.apr);
    common::detail::json::read(obj, "orderId", out.order_id);
    common::detail::json::read(obj, "purchaseTime", out.purchase_time);
    common::detail::json::read(obj, "optionType", out.option_type);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const SubscribeDualInvestmentProductsResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "positionId", v.position_id);
    common::detail::json::write(obj, "investCoin", v.invest_coin);
    common::detail::json::write(obj, "exercisedCoin", v.exercised_coin);
    common::detail::json::write(obj, "subscriptionAmount", v.subscription_amount);
    common::detail::json::write(obj, "duration", v.duration);
    common::detail::json::write(obj, "autoCompoundPlan", v.auto_compound_plan);
    common::detail::json::write(obj, "strikePrice", v.strike_price);
    common::detail::json::write(obj, "settleDate", v.settle_date);
    common::detail::json::write(obj, "purchaseStatus", v.purchase_status);
    common::detail::json::write(obj, "apr", v.apr);
    common::detail::json::write(obj, "orderId", v.order_id);
    common::detail::json::write(obj, "purchaseTime", v.purchase_time);
    common::detail::json::write(obj, "optionType", v.option_type);
}

} // namespace binance::dual_investment::rest_api
