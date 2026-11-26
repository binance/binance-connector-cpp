//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/wallet/rest_api/models/fetch_withdraw_address_list_response_inner.hpp>

namespace binance::wallet::rest_api {

FetchWithdrawAddressListResponseInner
tag_invoke(boost::json::value_to_tag<FetchWithdrawAddressListResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "FetchWithdrawAddressListResponseInner");
    FetchWithdrawAddressListResponseInner out;
    common::detail::json::read(obj, "address", out.address);
    common::detail::json::read(obj, "addressTag", out.address_tag);
    common::detail::json::read(obj, "coin", out.coin);
    common::detail::json::read(obj, "name", out.name);
    common::detail::json::read(obj, "network", out.network);
    common::detail::json::read(obj, "origin", out.origin);
    common::detail::json::read(obj, "originType", out.origin_type);
    common::detail::json::read(obj, "whiteStatus", out.white_status);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const FetchWithdrawAddressListResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "address", v.address);
    common::detail::json::write(obj, "addressTag", v.address_tag);
    common::detail::json::write(obj, "coin", v.coin);
    common::detail::json::write(obj, "name", v.name);
    common::detail::json::write(obj, "network", v.network);
    common::detail::json::write(obj, "origin", v.origin);
    common::detail::json::write(obj, "originType", v.origin_type);
    common::detail::json::write(obj, "whiteStatus", v.white_status);
}

} // namespace binance::wallet::rest_api
