//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/get_current_multi_assets_mode_response.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

GetCurrentMultiAssetsModeResponse
tag_invoke(boost::json::value_to_tag<GetCurrentMultiAssetsModeResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetCurrentMultiAssetsModeResponse");
    GetCurrentMultiAssetsModeResponse out;
    common::detail::json::read(obj, "multiAssetsMargin", out.multi_assets_margin);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetCurrentMultiAssetsModeResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "multiAssetsMargin", v.multi_assets_margin);
}

} // namespace binance::derivatives_trading_usds_futures::rest_api
