//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/stocks/rest_api/models/create_renew_listen_key_response.hpp>

namespace binance::stocks::rest_api {

CreateRenewListenKeyResponse
tag_invoke(boost::json::value_to_tag<CreateRenewListenKeyResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "CreateRenewListenKeyResponse");
    CreateRenewListenKeyResponse out;
    common::detail::json::read(obj, "listenKey", out.listen_key);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const CreateRenewListenKeyResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "listenKey", v.listen_key);
}

} // namespace binance::stocks::rest_api
