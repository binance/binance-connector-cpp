//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/wallet/rest_api/models/user_universal_transfer_response.hpp>

namespace binance::wallet::rest_api {

UserUniversalTransferResponse
tag_invoke(boost::json::value_to_tag<UserUniversalTransferResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "UserUniversalTransferResponse");
    UserUniversalTransferResponse out;
    common::detail::json::read(obj, "tranId", out.tran_id);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const UserUniversalTransferResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "tranId", v.tran_id);
}

} // namespace binance::wallet::rest_api
