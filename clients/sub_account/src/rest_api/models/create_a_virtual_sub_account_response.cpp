//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/sub_account/rest_api/models/create_a_virtual_sub_account_response.hpp>

namespace binance::sub_account::rest_api {

CreateAVirtualSubAccountResponse
tag_invoke(boost::json::value_to_tag<CreateAVirtualSubAccountResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "CreateAVirtualSubAccountResponse");
    CreateAVirtualSubAccountResponse out;
    common::detail::json::read(obj, "email", out.email);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const CreateAVirtualSubAccountResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "email", v.email);
}

} // namespace binance::sub_account::rest_api
