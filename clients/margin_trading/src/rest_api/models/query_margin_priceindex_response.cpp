//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/margin_trading/rest_api/models/query_margin_priceindex_response.hpp>

namespace binance::margin_trading::rest_api {

QueryMarginPriceindexResponse
tag_invoke(boost::json::value_to_tag<QueryMarginPriceindexResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "QueryMarginPriceindexResponse");
    QueryMarginPriceindexResponse out;
    common::detail::json::read(obj, "calcTime", out.calc_time);
    common::detail::json::read(obj, "price", out.price);
    common::detail::json::read(obj, "symbol", out.symbol);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryMarginPriceindexResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "calcTime", v.calc_time);
    common::detail::json::write(obj, "price", v.price);
    common::detail::json::write(obj, "symbol", v.symbol);
}

} // namespace binance::margin_trading::rest_api
