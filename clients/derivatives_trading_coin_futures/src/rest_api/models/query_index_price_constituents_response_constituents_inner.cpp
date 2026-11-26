//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/query_index_price_constituents_response_constituents_inner.hpp>

namespace binance::derivatives_trading_coin_futures::rest_api {

QueryIndexPriceConstituentsResponseConstituentsInner
tag_invoke(boost::json::value_to_tag<QueryIndexPriceConstituentsResponseConstituentsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "QueryIndexPriceConstituentsResponseConstituentsInner");
    QueryIndexPriceConstituentsResponseConstituentsInner out;
    common::detail::json::read(obj, "exchange", out.exchange);
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "price", out.price);
    common::detail::json::read(obj, "weight", out.weight);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryIndexPriceConstituentsResponseConstituentsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "exchange", v.exchange);
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "price", v.price);
    common::detail::json::write(obj, "weight", v.weight);
}

} // namespace binance::derivatives_trading_coin_futures::rest_api
