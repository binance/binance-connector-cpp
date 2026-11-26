//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin_pro/rest_api/models/query_portfolio_margin_asset_index_price_response_inner.hpp>

namespace binance::derivatives_trading_portfolio_margin_pro::rest_api {

QueryPortfolioMarginAssetIndexPriceResponseInner
tag_invoke(boost::json::value_to_tag<QueryPortfolioMarginAssetIndexPriceResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "QueryPortfolioMarginAssetIndexPriceResponseInner");
    QueryPortfolioMarginAssetIndexPriceResponseInner out;
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "assetIndexPrice", out.asset_index_price);
    common::detail::json::read(obj, "time", out.time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryPortfolioMarginAssetIndexPriceResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "assetIndexPrice", v.asset_index_price);
    common::detail::json::write(obj, "time", v.time);
}

} // namespace binance::derivatives_trading_portfolio_margin_pro::rest_api
