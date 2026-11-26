//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/margin_trading/rest_api/models/create_special_key_response.hpp>

namespace binance::margin_trading::rest_api {

CreateSpecialKeyResponse tag_invoke(boost::json::value_to_tag<CreateSpecialKeyResponse> /*tag*/,
                                    const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "CreateSpecialKeyResponse");
    CreateSpecialKeyResponse out;
    common::detail::json::read(obj, "apiKey", out.api_key);
    common::detail::json::read(obj, "secretKey", out.secret_key);
    common::detail::json::read(obj, "type", out.type);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const CreateSpecialKeyResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "apiKey", v.api_key);
    common::detail::json::write(obj, "secretKey", v.secret_key);
    common::detail::json::write(obj, "type", v.type);
}

} // namespace binance::margin_trading::rest_api
