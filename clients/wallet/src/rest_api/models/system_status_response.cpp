//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/wallet/rest_api/models/system_status_response.hpp>

namespace binance::wallet::rest_api {

SystemStatusResponse tag_invoke(boost::json::value_to_tag<SystemStatusResponse> /*tag*/,
                                const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "SystemStatusResponse");
    SystemStatusResponse out;
    common::detail::json::read(obj, "status", out.status);
    common::detail::json::read(obj, "msg", out.msg);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const SystemStatusResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "status", v.status);
    common::detail::json::write(obj, "msg", v.msg);
}

} // namespace binance::wallet::rest_api
