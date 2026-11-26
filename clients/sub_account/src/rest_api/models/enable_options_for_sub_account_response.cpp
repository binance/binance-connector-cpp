//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/sub_account/rest_api/models/enable_options_for_sub_account_response.hpp>

namespace binance::sub_account::rest_api {

EnableOptionsForSubAccountResponse
tag_invoke(boost::json::value_to_tag<EnableOptionsForSubAccountResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "EnableOptionsForSubAccountResponse");
    EnableOptionsForSubAccountResponse out;
    common::detail::json::read(obj, "email", out.email);
    common::detail::json::read(obj, "isEOptionsEnabled", out.is_e_options_enabled);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const EnableOptionsForSubAccountResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "email", v.email);
    common::detail::json::write(obj, "isEOptionsEnabled", v.is_e_options_enabled);
}

} // namespace binance::sub_account::rest_api
