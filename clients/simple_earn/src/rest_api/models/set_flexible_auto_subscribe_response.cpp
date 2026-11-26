//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/simple_earn/rest_api/models/set_flexible_auto_subscribe_response.hpp>

namespace binance::simple_earn::rest_api {

SetFlexibleAutoSubscribeResponse
tag_invoke(boost::json::value_to_tag<SetFlexibleAutoSubscribeResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "SetFlexibleAutoSubscribeResponse");
    SetFlexibleAutoSubscribeResponse out;
    common::detail::json::read(obj, "success", out.success);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const SetFlexibleAutoSubscribeResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "success", v.success);
}

} // namespace binance::simple_earn::rest_api
