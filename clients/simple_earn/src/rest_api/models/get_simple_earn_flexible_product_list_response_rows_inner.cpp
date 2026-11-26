//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/simple_earn/rest_api/models/get_simple_earn_flexible_product_list_response_rows_inner.hpp>

namespace binance::simple_earn::rest_api {

GetSimpleEarnFlexibleProductListResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetSimpleEarnFlexibleProductListResponseRowsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetSimpleEarnFlexibleProductListResponseRowsInner");
    GetSimpleEarnFlexibleProductListResponseRowsInner out;
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "latestAnnualPercentageRate",
                               out.latest_annual_percentage_rate);
    common::detail::json::read(obj, "tierAnnualPercentageRate", out.tier_annual_percentage_rate);
    common::detail::json::read(obj, "airDropPercentageRate", out.air_drop_percentage_rate);
    common::detail::json::read(obj, "canPurchase", out.can_purchase);
    common::detail::json::read(obj, "canRedeem", out.can_redeem);
    common::detail::json::read(obj, "isSoldOut", out.is_sold_out);
    common::detail::json::read(obj, "hot", out.hot);
    common::detail::json::read(obj, "minPurchaseAmount", out.min_purchase_amount);
    common::detail::json::read(obj, "productId", out.product_id);
    common::detail::json::read(obj, "subscriptionStartTime", out.subscription_start_time);
    common::detail::json::read(obj, "status", out.status);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetSimpleEarnFlexibleProductListResponseRowsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "latestAnnualPercentageRate", v.latest_annual_percentage_rate);
    common::detail::json::write(obj, "tierAnnualPercentageRate", v.tier_annual_percentage_rate);
    common::detail::json::write(obj, "airDropPercentageRate", v.air_drop_percentage_rate);
    common::detail::json::write(obj, "canPurchase", v.can_purchase);
    common::detail::json::write(obj, "canRedeem", v.can_redeem);
    common::detail::json::write(obj, "isSoldOut", v.is_sold_out);
    common::detail::json::write(obj, "hot", v.hot);
    common::detail::json::write(obj, "minPurchaseAmount", v.min_purchase_amount);
    common::detail::json::write(obj, "productId", v.product_id);
    common::detail::json::write(obj, "subscriptionStartTime", v.subscription_start_time);
    common::detail::json::write(obj, "status", v.status);
}

} // namespace binance::simple_earn::rest_api
