//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/w3w_prediction/rest_api/models/list_prediction_wallets_response.hpp>

namespace binance::w3w_prediction::rest_api {

ListPredictionWalletsResponse
tag_invoke(boost::json::value_to_tag<ListPredictionWalletsResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "ListPredictionWalletsResponse");
    ListPredictionWalletsResponse out;
    common::detail::json::read(obj, "wallets", out.wallets);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const ListPredictionWalletsResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "wallets", v.wallets);
}

} // namespace binance::w3w_prediction::rest_api
