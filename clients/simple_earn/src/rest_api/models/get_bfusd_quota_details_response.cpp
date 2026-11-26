//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/simple_earn/rest_api/models/get_bfusd_quota_details_response.hpp>

namespace binance::simple_earn::rest_api {

GetBfusdQuotaDetailsResponse
tag_invoke(boost::json::value_to_tag<GetBfusdQuotaDetailsResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetBfusdQuotaDetailsResponse");
    GetBfusdQuotaDetailsResponse out;
    common::detail::json::read(obj, "subscriptionQuota", out.subscription_quota);
    common::detail::json::read(obj, "fastRedemptionQuota", out.fast_redemption_quota);
    common::detail::json::read(obj, "standardRedemptionQuota", out.standard_redemption_quota);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetBfusdQuotaDetailsResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "subscriptionQuota", v.subscription_quota);
    common::detail::json::write(obj, "fastRedemptionQuota", v.fast_redemption_quota);
    common::detail::json::write(obj, "standardRedemptionQuota", v.standard_redemption_quota);
}

} // namespace binance::simple_earn::rest_api
