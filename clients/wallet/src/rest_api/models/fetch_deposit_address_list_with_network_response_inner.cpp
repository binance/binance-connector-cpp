//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/wallet/rest_api/models/fetch_deposit_address_list_with_network_response_inner.hpp>

namespace binance::wallet::rest_api {

FetchDepositAddressListWithNetworkResponseInner
tag_invoke(boost::json::value_to_tag<FetchDepositAddressListWithNetworkResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "FetchDepositAddressListWithNetworkResponseInner");
    FetchDepositAddressListWithNetworkResponseInner out;
    common::detail::json::read(obj, "coin", out.coin);
    common::detail::json::read(obj, "address", out.address);
    common::detail::json::read(obj, "tag", out.tag);
    common::detail::json::read(obj, "isDefault", out.is_default);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const FetchDepositAddressListWithNetworkResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "coin", v.coin);
    common::detail::json::write(obj, "address", v.address);
    common::detail::json::write(obj, "tag", v.tag);
    common::detail::json::write(obj, "isDefault", v.is_default);
}

} // namespace binance::wallet::rest_api
