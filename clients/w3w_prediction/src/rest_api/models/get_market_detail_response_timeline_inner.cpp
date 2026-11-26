//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/w3w_prediction/rest_api/models/get_market_detail_response_timeline_inner.hpp>

namespace binance::w3w_prediction::rest_api {

GetMarketDetailResponseTimelineInner
tag_invoke(boost::json::value_to_tag<GetMarketDetailResponseTimelineInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetMarketDetailResponseTimelineInner");
    GetMarketDetailResponseTimelineInner out;
    common::detail::json::read(obj, "marketTopicId", out.market_topic_id);
    common::detail::json::read(obj, "startDate", out.start_date);
    common::detail::json::read(obj, "endDate", out.end_date);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetMarketDetailResponseTimelineInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "marketTopicId", v.market_topic_id);
    common::detail::json::write(obj, "startDate", v.start_date);
    common::detail::json::write(obj, "endDate", v.end_date);
}

} // namespace binance::w3w_prediction::rest_api
