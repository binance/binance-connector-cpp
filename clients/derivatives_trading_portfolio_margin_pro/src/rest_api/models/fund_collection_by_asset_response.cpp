//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin_pro/rest_api/models/fund_collection_by_asset_response.hpp>

namespace binance::derivatives_trading_portfolio_margin_pro::rest_api {

FundCollectionByAssetResponse
tag_invoke(boost::json::value_to_tag<FundCollectionByAssetResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "FundCollectionByAssetResponse");
    FundCollectionByAssetResponse out;
    common::detail::json::read(obj, "msg", out.msg);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const FundCollectionByAssetResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "msg", v.msg);
}

} // namespace binance::derivatives_trading_portfolio_margin_pro::rest_api
