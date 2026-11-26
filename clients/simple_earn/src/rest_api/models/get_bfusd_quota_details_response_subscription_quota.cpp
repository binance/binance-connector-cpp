//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/simple_earn/rest_api/models/get_bfusd_quota_details_response_subscription_quota.hpp>

namespace binance::simple_earn::rest_api {

GetBfusdQuotaDetailsResponseSubscriptionQuota
tag_invoke(boost::json::value_to_tag<GetBfusdQuotaDetailsResponseSubscriptionQuota> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetBfusdQuotaDetailsResponseSubscriptionQuota");
    GetBfusdQuotaDetailsResponseSubscriptionQuota out;
    common::detail::json::read(obj, "leftQuota", out.left_quota);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetBfusdQuotaDetailsResponseSubscriptionQuota& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "leftQuota", v.left_quota);
}

} // namespace binance::simple_earn::rest_api
