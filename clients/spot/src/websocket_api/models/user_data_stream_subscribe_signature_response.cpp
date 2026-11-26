//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/websocket_api/models/user_data_stream_subscribe_signature_response.hpp>

namespace binance::spot::websocket_api {

UserDataStreamSubscribeSignatureResponse
tag_invoke(boost::json::value_to_tag<UserDataStreamSubscribeSignatureResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "UserDataStreamSubscribeSignatureResponse");
    UserDataStreamSubscribeSignatureResponse out;
    common::detail::json::read(obj, "id", out.id);
    common::detail::json::read(obj, "status", out.status);
    common::detail::json::read(obj, "result", out.result);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const UserDataStreamSubscribeSignatureResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "id", v.id);
    common::detail::json::write(obj, "status", v.status);
    common::detail::json::write(obj, "result", v.result);
}

} // namespace binance::spot::websocket_api
