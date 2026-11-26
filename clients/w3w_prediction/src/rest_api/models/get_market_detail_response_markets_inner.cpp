//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/w3w_prediction/rest_api/models/get_market_detail_response_markets_inner.hpp>

namespace binance::w3w_prediction::rest_api {

GetMarketDetailResponseMarketsInner
tag_invoke(boost::json::value_to_tag<GetMarketDetailResponseMarketsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetMarketDetailResponseMarketsInner");
    GetMarketDetailResponseMarketsInner out;
    common::detail::json::read(obj, "marketId", out.market_id);
    common::detail::json::read(obj, "externalId", out.external_id);
    common::detail::json::read(obj, "title", out.title);
    common::detail::json::read(obj, "question", out.question);
    common::detail::json::read(obj, "description", out.description);
    common::detail::json::read(obj, "conditionId", out.condition_id);
    common::detail::json::read(obj, "status", out.status);
    common::detail::json::read(obj, "tradingStatus", out.trading_status);
    common::detail::json::read(obj, "tradeVolume", out.trade_volume);
    common::detail::json::read(obj, "liquidity", out.liquidity);
    common::detail::json::read(obj, "decimalPrecision", out.decimal_precision);
    common::detail::json::read(obj, "outcomes", out.outcomes);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetMarketDetailResponseMarketsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "marketId", v.market_id);
    common::detail::json::write(obj, "externalId", v.external_id);
    common::detail::json::write(obj, "title", v.title);
    common::detail::json::write(obj, "question", v.question);
    common::detail::json::write(obj, "description", v.description);
    common::detail::json::write(obj, "conditionId", v.condition_id);
    common::detail::json::write(obj, "status", v.status);
    common::detail::json::write(obj, "tradingStatus", v.trading_status);
    common::detail::json::write(obj, "tradeVolume", v.trade_volume);
    common::detail::json::write(obj, "liquidity", v.liquidity);
    common::detail::json::write(obj, "decimalPrecision", v.decimal_precision);
    common::detail::json::write(obj, "outcomes", v.outcomes);
}

} // namespace binance::w3w_prediction::rest_api
