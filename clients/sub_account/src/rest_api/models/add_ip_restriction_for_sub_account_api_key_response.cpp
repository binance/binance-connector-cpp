//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/sub_account/rest_api/models/add_ip_restriction_for_sub_account_api_key_response.hpp>

namespace binance::sub_account::rest_api {

AddIpRestrictionForSubAccountApiKeyResponse
tag_invoke(boost::json::value_to_tag<AddIpRestrictionForSubAccountApiKeyResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "AddIpRestrictionForSubAccountApiKeyResponse");
    AddIpRestrictionForSubAccountApiKeyResponse out;
    common::detail::json::read(obj, "status", out.status);
    common::detail::json::read(obj, "ipList", out.ip_list);
    common::detail::json::read(obj, "updateTime", out.update_time);
    common::detail::json::read(obj, "apiKey", out.api_key);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const AddIpRestrictionForSubAccountApiKeyResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "status", v.status);
    common::detail::json::write(obj, "ipList", v.ip_list);
    common::detail::json::write(obj, "updateTime", v.update_time);
    common::detail::json::write(obj, "apiKey", v.api_key);
}

} // namespace binance::sub_account::rest_api
