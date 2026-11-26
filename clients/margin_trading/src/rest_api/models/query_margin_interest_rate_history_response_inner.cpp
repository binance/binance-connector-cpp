//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/margin_trading/rest_api/models/query_margin_interest_rate_history_response_inner.hpp>

namespace binance::margin_trading::rest_api {

QueryMarginInterestRateHistoryResponseInner
tag_invoke(boost::json::value_to_tag<QueryMarginInterestRateHistoryResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "QueryMarginInterestRateHistoryResponseInner");
    QueryMarginInterestRateHistoryResponseInner out;
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "dailyInterestRate", out.daily_interest_rate);
    common::detail::json::read(obj, "timestamp", out.timestamp);
    common::detail::json::read(obj, "vipLevel", out.vip_level);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryMarginInterestRateHistoryResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "dailyInterestRate", v.daily_interest_rate);
    common::detail::json::write(obj, "timestamp", v.timestamp);
    common::detail::json::write(obj, "vipLevel", v.vip_level);
}

} // namespace binance::margin_trading::rest_api
