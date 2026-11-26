//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/w3w_prediction/rest_api/models/get_market_detail_response_markets_inner_outcomes_inner.hpp>

namespace binance::w3w_prediction::rest_api {

GetMarketDetailResponseMarketsInnerOutcomesInner
tag_invoke(boost::json::value_to_tag<GetMarketDetailResponseMarketsInnerOutcomesInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetMarketDetailResponseMarketsInnerOutcomesInner");
    GetMarketDetailResponseMarketsInnerOutcomesInner out;
    common::detail::json::read(obj, "name", out.name);
    common::detail::json::read(obj, "price", out.price);
    common::detail::json::read(obj, "chance", out.chance);
    common::detail::json::read(obj, "index", out.index);
    common::detail::json::read(obj, "tokenId", out.token_id);
    common::detail::json::read(obj, "winner", out.winner);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetMarketDetailResponseMarketsInnerOutcomesInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "name", v.name);
    common::detail::json::write(obj, "price", v.price);
    common::detail::json::write(obj, "chance", v.chance);
    common::detail::json::write(obj, "index", v.index);
    common::detail::json::write(obj, "tokenId", v.token_id);
    common::detail::json::write(obj, "winner", v.winner);
}

} // namespace binance::w3w_prediction::rest_api
