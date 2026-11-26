//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/simple_earn/rest_api/models/get_flexible_personal_left_quota_response.hpp>

namespace binance::simple_earn::rest_api {

GetFlexiblePersonalLeftQuotaResponse
tag_invoke(boost::json::value_to_tag<GetFlexiblePersonalLeftQuotaResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetFlexiblePersonalLeftQuotaResponse");
    GetFlexiblePersonalLeftQuotaResponse out;
    common::detail::json::read(obj, "leftPersonalQuota", out.left_personal_quota);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetFlexiblePersonalLeftQuotaResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "leftPersonalQuota", v.left_personal_quota);
}

} // namespace binance::simple_earn::rest_api
