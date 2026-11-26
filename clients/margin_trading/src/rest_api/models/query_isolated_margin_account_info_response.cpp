//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/margin_trading/rest_api/models/query_isolated_margin_account_info_response.hpp>

namespace binance::margin_trading::rest_api {

QueryIsolatedMarginAccountInfoResponse
tag_invoke(boost::json::value_to_tag<QueryIsolatedMarginAccountInfoResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "QueryIsolatedMarginAccountInfoResponse");
    QueryIsolatedMarginAccountInfoResponse out;
    common::detail::json::read(obj, "assets", out.assets);
    common::detail::json::read(obj, "totalAssetOfBtc", out.total_asset_of_btc);
    common::detail::json::read(obj, "totalLiabilityOfBtc", out.total_liability_of_btc);
    common::detail::json::read(obj, "totalNetAssetOfBtc", out.total_net_asset_of_btc);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryIsolatedMarginAccountInfoResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "assets", v.assets);
    common::detail::json::write(obj, "totalAssetOfBtc", v.total_asset_of_btc);
    common::detail::json::write(obj, "totalLiabilityOfBtc", v.total_liability_of_btc);
    common::detail::json::write(obj, "totalNetAssetOfBtc", v.total_net_asset_of_btc);
}

} // namespace binance::margin_trading::rest_api
