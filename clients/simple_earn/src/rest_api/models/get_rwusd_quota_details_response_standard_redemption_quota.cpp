//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/simple_earn/rest_api/models/get_rwusd_quota_details_response_standard_redemption_quota.hpp>

namespace binance::simple_earn::rest_api {

GetRwusdQuotaDetailsResponseStandardRedemptionQuota
tag_invoke(boost::json::value_to_tag<GetRwusdQuotaDetailsResponseStandardRedemptionQuota> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetRwusdQuotaDetailsResponseStandardRedemptionQuota");
    GetRwusdQuotaDetailsResponseStandardRedemptionQuota out;
    common::detail::json::read(obj, "leftQuota", out.left_quota);
    common::detail::json::read(obj, "minimum", out.minimum);
    common::detail::json::read(obj, "fee", out.fee);
    common::detail::json::read(obj, "redeemPeriod", out.redeem_period);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetRwusdQuotaDetailsResponseStandardRedemptionQuota& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "leftQuota", v.left_quota);
    common::detail::json::write(obj, "minimum", v.minimum);
    common::detail::json::write(obj, "fee", v.fee);
    common::detail::json::write(obj, "redeemPeriod", v.redeem_period);
}

} // namespace binance::simple_earn::rest_api
