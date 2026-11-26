//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/margin_trading/rest_api/models/query_isolated_margin_tier_data_response_inner.hpp>

namespace binance::margin_trading::rest_api {

QueryIsolatedMarginTierDataResponseInner
tag_invoke(boost::json::value_to_tag<QueryIsolatedMarginTierDataResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "QueryIsolatedMarginTierDataResponseInner");
    QueryIsolatedMarginTierDataResponseInner out;
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "tier", out.tier);
    common::detail::json::read(obj, "effectiveMultiple", out.effective_multiple);
    common::detail::json::read(obj, "initialRiskRatio", out.initial_risk_ratio);
    common::detail::json::read(obj, "liquidationRiskRatio", out.liquidation_risk_ratio);
    common::detail::json::read(obj, "baseAssetMaxBorrowable", out.base_asset_max_borrowable);
    common::detail::json::read(obj, "quoteAssetMaxBorrowable", out.quote_asset_max_borrowable);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryIsolatedMarginTierDataResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "tier", v.tier);
    common::detail::json::write(obj, "effectiveMultiple", v.effective_multiple);
    common::detail::json::write(obj, "initialRiskRatio", v.initial_risk_ratio);
    common::detail::json::write(obj, "liquidationRiskRatio", v.liquidation_risk_ratio);
    common::detail::json::write(obj, "baseAssetMaxBorrowable", v.base_asset_max_borrowable);
    common::detail::json::write(obj, "quoteAssetMaxBorrowable", v.quote_asset_max_borrowable);
}

} // namespace binance::margin_trading::rest_api
