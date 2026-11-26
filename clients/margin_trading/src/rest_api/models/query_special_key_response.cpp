//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/margin_trading/rest_api/models/query_special_key_response.hpp>

namespace binance::margin_trading::rest_api {

QuerySpecialKeyResponse tag_invoke(boost::json::value_to_tag<QuerySpecialKeyResponse> /*tag*/,
                                   const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "QuerySpecialKeyResponse");
    QuerySpecialKeyResponse out;
    common::detail::json::read(obj, "apiKey", out.api_key);
    common::detail::json::read(obj, "ip", out.ip);
    common::detail::json::read(obj, "apiName", out.api_name);
    common::detail::json::read(obj, "type", out.type);
    common::detail::json::read(obj, "permissionMode", out.permission_mode);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QuerySpecialKeyResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "apiKey", v.api_key);
    common::detail::json::write(obj, "ip", v.ip);
    common::detail::json::write(obj, "apiName", v.api_name);
    common::detail::json::write(obj, "type", v.type);
    common::detail::json::write(obj, "permissionMode", v.permission_mode);
}

} // namespace binance::margin_trading::rest_api
