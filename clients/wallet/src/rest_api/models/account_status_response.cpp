//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/wallet/rest_api/models/account_status_response.hpp>

namespace binance::wallet::rest_api {

AccountStatusResponse tag_invoke(boost::json::value_to_tag<AccountStatusResponse> /*tag*/,
                                 const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "AccountStatusResponse");
    AccountStatusResponse out;
    common::detail::json::read(obj, "data", out.data);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const AccountStatusResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "data", v.data);
}

} // namespace binance::wallet::rest_api
