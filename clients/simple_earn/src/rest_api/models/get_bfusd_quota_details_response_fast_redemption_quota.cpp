//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/simple_earn/rest_api/models/get_bfusd_quota_details_response_fast_redemption_quota.hpp>

namespace binance::simple_earn::rest_api {

GetBfusdQuotaDetailsResponseFastRedemptionQuota
tag_invoke(boost::json::value_to_tag<GetBfusdQuotaDetailsResponseFastRedemptionQuota> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetBfusdQuotaDetailsResponseFastRedemptionQuota");
    GetBfusdQuotaDetailsResponseFastRedemptionQuota out;
    common::detail::json::read(obj, "leftQuota", out.left_quota);
    common::detail::json::read(obj, "minimum", out.minimum);
    common::detail::json::read(obj, "fee", out.fee);
    common::detail::json::read(obj, "freeQuota", out.free_quota);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetBfusdQuotaDetailsResponseFastRedemptionQuota& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "leftQuota", v.left_quota);
    common::detail::json::write(obj, "minimum", v.minimum);
    common::detail::json::write(obj, "fee", v.fee);
    common::detail::json::write(obj, "freeQuota", v.free_quota);
}

} // namespace binance::simple_earn::rest_api
