//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/w3w_prediction/rest_api/models/query_last_trade_price_response.hpp>

namespace binance::w3w_prediction::rest_api {

QueryLastTradePriceResponse
tag_invoke(boost::json::value_to_tag<QueryLastTradePriceResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "QueryLastTradePriceResponse");
    QueryLastTradePriceResponse out;
    common::detail::json::read(obj, "marketId", out.market_id);
    common::detail::json::read(obj, "lastTradePrice", out.last_trade_price);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryLastTradePriceResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "marketId", v.market_id);
    common::detail::json::write(obj, "lastTradePrice", v.last_trade_price);
}

} // namespace binance::w3w_prediction::rest_api
