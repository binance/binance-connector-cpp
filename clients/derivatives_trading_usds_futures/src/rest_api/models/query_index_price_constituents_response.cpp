//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/query_index_price_constituents_response.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

QueryIndexPriceConstituentsResponse
tag_invoke(boost::json::value_to_tag<QueryIndexPriceConstituentsResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "QueryIndexPriceConstituentsResponse");
    QueryIndexPriceConstituentsResponse out;
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "time", out.time);
    common::detail::json::read(obj, "constituents", out.constituents);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryIndexPriceConstituentsResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "time", v.time);
    common::detail::json::write(obj, "constituents", v.constituents);
}

} // namespace binance::derivatives_trading_usds_futures::rest_api
