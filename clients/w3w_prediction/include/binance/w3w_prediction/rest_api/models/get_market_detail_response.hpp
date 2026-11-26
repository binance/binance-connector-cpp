//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/w3w_prediction/export.hpp>
#include <binance/w3w_prediction/rest_api/models/get_market_detail_response_markets_inner.hpp>
#include <binance/w3w_prediction/rest_api/models/get_market_detail_response_timeline_inner.hpp>
#include <binance/w3w_prediction/rest_api/models/get_market_detail_response_variant_data.hpp>

namespace binance::w3w_prediction::rest_api {

struct GetMarketDetailResponse {
    std::optional<std::int64_t> market_topic_id;
    std::optional<std::string> vendor;
    std::optional<std::string> chain_id;
    std::optional<std::string> slug;
    std::optional<std::string> title;
    std::optional<std::string> question;
    std::optional<std::string> description;
    std::optional<std::string> image_url;
    std::optional<std::string> topic_type;
    std::optional<std::string> chart_type;
    std::optional<std::string> symbol;
    std::optional<GetMarketDetailResponseVariantData> variant_data;
    std::optional<std::int64_t> participant_count;
    std::optional<std::string> collateral;
    std::optional<std::int64_t> fee_rate_bps;
    std::optional<std::int64_t> slippage_bps;
    std::optional<bool> is_yield_bearing;
    std::optional<std::string> trade_volume;
    std::optional<std::string> liquidity;
    std::optional<std::int64_t> published_at;
    std::optional<std::int64_t> start_date;
    std::optional<std::int64_t> end_date;
    std::optional<std::string> status;
    std::optional<std::vector<GetMarketDetailResponseTimelineInner>> timeline;
    std::optional<std::vector<GetMarketDetailResponseMarketsInner>> markets;

    bool operator==(const GetMarketDetailResponse& /*other*/) const = default;
};

BINANCE_W3W_PREDICTION_EXPORT GetMarketDetailResponse tag_invoke(
    boost::json::value_to_tag<GetMarketDetailResponse> /*tag*/, const boost::json::value& jv);
BINANCE_W3W_PREDICTION_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const GetMarketDetailResponse& v);

} // namespace binance::w3w_prediction::rest_api
