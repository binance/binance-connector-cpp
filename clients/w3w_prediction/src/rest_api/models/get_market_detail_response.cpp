//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/w3w_prediction/rest_api/models/get_market_detail_response.hpp>

namespace binance::w3w_prediction::rest_api {

GetMarketDetailResponse tag_invoke(boost::json::value_to_tag<GetMarketDetailResponse> /*tag*/,
                                   const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetMarketDetailResponse");
    GetMarketDetailResponse out;
    common::detail::json::read(obj, "marketTopicId", out.market_topic_id);
    common::detail::json::read(obj, "vendor", out.vendor);
    common::detail::json::read(obj, "chainId", out.chain_id);
    common::detail::json::read(obj, "slug", out.slug);
    common::detail::json::read(obj, "title", out.title);
    common::detail::json::read(obj, "question", out.question);
    common::detail::json::read(obj, "description", out.description);
    common::detail::json::read(obj, "imageUrl", out.image_url);
    common::detail::json::read(obj, "topicType", out.topic_type);
    common::detail::json::read(obj, "chartType", out.chart_type);
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "variantData", out.variant_data);
    common::detail::json::read(obj, "participantCount", out.participant_count);
    common::detail::json::read(obj, "collateral", out.collateral);
    common::detail::json::read(obj, "feeRateBps", out.fee_rate_bps);
    common::detail::json::read(obj, "slippageBps", out.slippage_bps);
    common::detail::json::read(obj, "isYieldBearing", out.is_yield_bearing);
    common::detail::json::read(obj, "tradeVolume", out.trade_volume);
    common::detail::json::read(obj, "liquidity", out.liquidity);
    common::detail::json::read(obj, "publishedAt", out.published_at);
    common::detail::json::read(obj, "startDate", out.start_date);
    common::detail::json::read(obj, "endDate", out.end_date);
    common::detail::json::read(obj, "status", out.status);
    common::detail::json::read(obj, "timeline", out.timeline);
    common::detail::json::read(obj, "markets", out.markets);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetMarketDetailResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "marketTopicId", v.market_topic_id);
    common::detail::json::write(obj, "vendor", v.vendor);
    common::detail::json::write(obj, "chainId", v.chain_id);
    common::detail::json::write(obj, "slug", v.slug);
    common::detail::json::write(obj, "title", v.title);
    common::detail::json::write(obj, "question", v.question);
    common::detail::json::write(obj, "description", v.description);
    common::detail::json::write(obj, "imageUrl", v.image_url);
    common::detail::json::write(obj, "topicType", v.topic_type);
    common::detail::json::write(obj, "chartType", v.chart_type);
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "variantData", v.variant_data);
    common::detail::json::write(obj, "participantCount", v.participant_count);
    common::detail::json::write(obj, "collateral", v.collateral);
    common::detail::json::write(obj, "feeRateBps", v.fee_rate_bps);
    common::detail::json::write(obj, "slippageBps", v.slippage_bps);
    common::detail::json::write(obj, "isYieldBearing", v.is_yield_bearing);
    common::detail::json::write(obj, "tradeVolume", v.trade_volume);
    common::detail::json::write(obj, "liquidity", v.liquidity);
    common::detail::json::write(obj, "publishedAt", v.published_at);
    common::detail::json::write(obj, "startDate", v.start_date);
    common::detail::json::write(obj, "endDate", v.end_date);
    common::detail::json::write(obj, "status", v.status);
    common::detail::json::write(obj, "timeline", v.timeline);
    common::detail::json::write(obj, "markets", v.markets);
}

} // namespace binance::w3w_prediction::rest_api
