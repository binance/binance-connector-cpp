//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/simple_earn/rest_api/models/get_rwusd_quota_details_response_subscription_quota.hpp>

namespace binance::simple_earn::rest_api {

GetRwusdQuotaDetailsResponseSubscriptionQuota
tag_invoke(boost::json::value_to_tag<GetRwusdQuotaDetailsResponseSubscriptionQuota> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetRwusdQuotaDetailsResponseSubscriptionQuota");
    GetRwusdQuotaDetailsResponseSubscriptionQuota out;
    common::detail::json::read(obj, "assets", out.assets);
    common::detail::json::read(obj, "leftQuota", out.left_quota);
    common::detail::json::read(obj, "minimum", out.minimum);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetRwusdQuotaDetailsResponseSubscriptionQuota& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "assets", v.assets);
    common::detail::json::write(obj, "leftQuota", v.left_quota);
    common::detail::json::write(obj, "minimum", v.minimum);
}

} // namespace binance::simple_earn::rest_api
