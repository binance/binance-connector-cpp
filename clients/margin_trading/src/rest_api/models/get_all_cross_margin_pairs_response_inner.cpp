//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/margin_trading/rest_api/models/get_all_cross_margin_pairs_response_inner.hpp>

namespace binance::margin_trading::rest_api {

GetAllCrossMarginPairsResponseInner
tag_invoke(boost::json::value_to_tag<GetAllCrossMarginPairsResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetAllCrossMarginPairsResponseInner");
    GetAllCrossMarginPairsResponseInner out;
    common::detail::json::read(obj, "base", out.base);
    common::detail::json::read(obj, "id", out.id);
    common::detail::json::read(obj, "isBuyAllowed", out.is_buy_allowed);
    common::detail::json::read(obj, "isMarginTrade", out.is_margin_trade);
    common::detail::json::read(obj, "isSellAllowed", out.is_sell_allowed);
    common::detail::json::read(obj, "quote", out.quote);
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "delistTime", out.delist_time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetAllCrossMarginPairsResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "base", v.base);
    common::detail::json::write(obj, "id", v.id);
    common::detail::json::write(obj, "isBuyAllowed", v.is_buy_allowed);
    common::detail::json::write(obj, "isMarginTrade", v.is_margin_trade);
    common::detail::json::write(obj, "isSellAllowed", v.is_sell_allowed);
    common::detail::json::write(obj, "quote", v.quote);
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "delistTime", v.delist_time);
}

} // namespace binance::margin_trading::rest_api
