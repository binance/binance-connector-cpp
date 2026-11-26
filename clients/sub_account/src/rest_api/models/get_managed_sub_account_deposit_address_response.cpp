//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/sub_account/rest_api/models/get_managed_sub_account_deposit_address_response.hpp>

namespace binance::sub_account::rest_api {

GetManagedSubAccountDepositAddressResponse
tag_invoke(boost::json::value_to_tag<GetManagedSubAccountDepositAddressResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetManagedSubAccountDepositAddressResponse");
    GetManagedSubAccountDepositAddressResponse out;
    common::detail::json::read(obj, "coin", out.coin);
    common::detail::json::read(obj, "address", out.address);
    common::detail::json::read(obj, "tag", out.tag);
    common::detail::json::read(obj, "url", out.url);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetManagedSubAccountDepositAddressResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "coin", v.coin);
    common::detail::json::write(obj, "address", v.address);
    common::detail::json::write(obj, "tag", v.tag);
    common::detail::json::write(obj, "url", v.url);
}

} // namespace binance::sub_account::rest_api
