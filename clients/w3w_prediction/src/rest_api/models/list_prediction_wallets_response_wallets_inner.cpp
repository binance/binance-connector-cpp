//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/w3w_prediction/rest_api/models/list_prediction_wallets_response_wallets_inner.hpp>

namespace binance::w3w_prediction::rest_api {

ListPredictionWalletsResponseWalletsInner
tag_invoke(boost::json::value_to_tag<ListPredictionWalletsResponseWalletsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "ListPredictionWalletsResponseWalletsInner");
    ListPredictionWalletsResponseWalletsInner out;
    common::detail::json::read(obj, "walletAddress", out.wallet_address);
    common::detail::json::read(obj, "walletId", out.wallet_id);
    common::detail::json::read(obj, "registeredTime", out.registered_time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const ListPredictionWalletsResponseWalletsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "walletAddress", v.wallet_address);
    common::detail::json::write(obj, "walletId", v.wallet_id);
    common::detail::json::write(obj, "registeredTime", v.registered_time);
}

} // namespace binance::w3w_prediction::rest_api
