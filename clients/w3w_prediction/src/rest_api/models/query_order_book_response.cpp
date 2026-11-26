//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/w3w_prediction/rest_api/models/query_order_book_response.hpp>

namespace binance::w3w_prediction::rest_api {

QueryOrderBookResponse tag_invoke(boost::json::value_to_tag<QueryOrderBookResponse> /*tag*/,
                                  const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "QueryOrderBookResponse");
    QueryOrderBookResponse out;
    common::detail::json::read(obj, "outcome", out.outcome);
    common::detail::json::read(obj, "tokenId", out.token_id);
    common::detail::json::read(obj, "timestamp", out.timestamp);
    common::detail::json::read(obj, "bids", out.bids);
    common::detail::json::read(obj, "asks", out.asks);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryOrderBookResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "outcome", v.outcome);
    common::detail::json::write(obj, "tokenId", v.token_id);
    common::detail::json::write(obj, "timestamp", v.timestamp);
    common::detail::json::write(obj, "bids", v.bids);
    common::detail::json::write(obj, "asks", v.asks);
}

} // namespace binance::w3w_prediction::rest_api
