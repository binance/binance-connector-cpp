//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/simple_earn/rest_api/models/get_flexible_product_position_response_rows_inner_tier_annual_percentage_rate.hpp>

namespace binance::simple_earn::rest_api {

GetFlexibleProductPositionResponseRowsInnerTierAnnualPercentageRate
tag_invoke(boost::json::value_to_tag<
               GetFlexibleProductPositionResponseRowsInnerTierAnnualPercentageRate> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "GetFlexibleProductPositionResponseRowsInnerTierAnnualPercentageRate");
    GetFlexibleProductPositionResponseRowsInnerTierAnnualPercentageRate out;
    common::detail::json::read(obj, "0-5BTC", out.r_0_5_btc);
    common::detail::json::read(obj, "5-10BTC", out.r_5_10_btc);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetFlexibleProductPositionResponseRowsInnerTierAnnualPercentageRate& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "0-5BTC", v.r_0_5_btc);
    common::detail::json::write(obj, "5-10BTC", v.r_5_10_btc);
}

} // namespace binance::simple_earn::rest_api
