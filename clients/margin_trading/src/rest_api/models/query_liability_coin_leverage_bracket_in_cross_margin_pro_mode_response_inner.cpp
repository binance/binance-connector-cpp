//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/margin_trading/rest_api/models/query_liability_coin_leverage_bracket_in_cross_margin_pro_mode_response_inner.hpp>

namespace binance::margin_trading::rest_api {

QueryLiabilityCoinLeverageBracketInCrossMarginProModeResponseInner
tag_invoke(boost::json::value_to_tag<
               QueryLiabilityCoinLeverageBracketInCrossMarginProModeResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "QueryLiabilityCoinLeverageBracketInCrossMarginProModeResponseInner");
    QueryLiabilityCoinLeverageBracketInCrossMarginProModeResponseInner out;
    common::detail::json::read(obj, "assetNames", out.asset_names);
    common::detail::json::read(obj, "rank", out.rank);
    common::detail::json::read(obj, "brackets", out.brackets);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryLiabilityCoinLeverageBracketInCrossMarginProModeResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "assetNames", v.asset_names);
    common::detail::json::write(obj, "rank", v.rank);
    common::detail::json::write(obj, "brackets", v.brackets);
}

} // namespace binance::margin_trading::rest_api
