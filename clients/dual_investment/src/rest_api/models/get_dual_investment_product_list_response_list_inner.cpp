//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/dual_investment/rest_api/models/get_dual_investment_product_list_response_list_inner.hpp>

namespace binance::dual_investment::rest_api {

GetDualInvestmentProductListResponseListInner
tag_invoke(boost::json::value_to_tag<GetDualInvestmentProductListResponseListInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetDualInvestmentProductListResponseListInner");
    GetDualInvestmentProductListResponseListInner out;
    common::detail::json::read(obj, "id", out.id);
    common::detail::json::read(obj, "investCoin", out.invest_coin);
    common::detail::json::read(obj, "exercisedCoin", out.exercised_coin);
    common::detail::json::read(obj, "strikePrice", out.strike_price);
    common::detail::json::read(obj, "duration", out.duration);
    common::detail::json::read(obj, "settleDate", out.settle_date);
    common::detail::json::read(obj, "purchaseDecimal", out.purchase_decimal);
    common::detail::json::read(obj, "purchaseEndTime", out.purchase_end_time);
    common::detail::json::read(obj, "canPurchase", out.can_purchase);
    common::detail::json::read(obj, "apr", out.apr);
    common::detail::json::read(obj, "orderId", out.order_id);
    common::detail::json::read(obj, "minAmount", out.min_amount);
    common::detail::json::read(obj, "maxAmount", out.max_amount);
    common::detail::json::read(obj, "createTimestamp", out.create_timestamp);
    common::detail::json::read(obj, "optionType", out.option_type);
    common::detail::json::read(obj, "isAutoCompoundEnable", out.is_auto_compound_enable);
    common::detail::json::read(obj, "autoCompoundPlanList", out.auto_compound_plan_list);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetDualInvestmentProductListResponseListInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "id", v.id);
    common::detail::json::write(obj, "investCoin", v.invest_coin);
    common::detail::json::write(obj, "exercisedCoin", v.exercised_coin);
    common::detail::json::write(obj, "strikePrice", v.strike_price);
    common::detail::json::write(obj, "duration", v.duration);
    common::detail::json::write(obj, "settleDate", v.settle_date);
    common::detail::json::write(obj, "purchaseDecimal", v.purchase_decimal);
    common::detail::json::write(obj, "purchaseEndTime", v.purchase_end_time);
    common::detail::json::write(obj, "canPurchase", v.can_purchase);
    common::detail::json::write(obj, "apr", v.apr);
    common::detail::json::write(obj, "orderId", v.order_id);
    common::detail::json::write(obj, "minAmount", v.min_amount);
    common::detail::json::write(obj, "maxAmount", v.max_amount);
    common::detail::json::write(obj, "createTimestamp", v.create_timestamp);
    common::detail::json::write(obj, "optionType", v.option_type);
    common::detail::json::write(obj, "isAutoCompoundEnable", v.is_auto_compound_enable);
    common::detail::json::write(obj, "autoCompoundPlanList", v.auto_compound_plan_list);
}

} // namespace binance::dual_investment::rest_api
