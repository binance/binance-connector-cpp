//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/w3w_prediction/rest_api/models/query_order_book_response_asks_inner.hpp>

namespace binance::w3w_prediction::rest_api {

QueryOrderBookResponseAsksInner
tag_invoke(boost::json::value_to_tag<QueryOrderBookResponseAsksInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "QueryOrderBookResponseAsksInner");
    QueryOrderBookResponseAsksInner out;
    common::detail::json::read(obj, "price", out.price);
    common::detail::json::read(obj, "size", out.size);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryOrderBookResponseAsksInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "price", v.price);
    common::detail::json::write(obj, "size", v.size);
}

} // namespace binance::w3w_prediction::rest_api
