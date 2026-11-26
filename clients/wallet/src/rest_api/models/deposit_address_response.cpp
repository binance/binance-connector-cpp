//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/wallet/rest_api/models/deposit_address_response.hpp>

namespace binance::wallet::rest_api {

DepositAddressResponse tag_invoke(boost::json::value_to_tag<DepositAddressResponse> /*tag*/,
                                  const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "DepositAddressResponse");
    DepositAddressResponse out;
    common::detail::json::read(obj, "address", out.address);
    common::detail::json::read(obj, "coin", out.coin);
    common::detail::json::read(obj, "tag", out.tag);
    common::detail::json::read(obj, "url", out.url);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const DepositAddressResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "address", v.address);
    common::detail::json::write(obj, "coin", v.coin);
    common::detail::json::write(obj, "tag", v.tag);
    common::detail::json::write(obj, "url", v.url);
}

} // namespace binance::wallet::rest_api
