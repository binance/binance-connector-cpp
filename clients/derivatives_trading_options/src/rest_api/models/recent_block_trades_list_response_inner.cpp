//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_options/rest_api/models/recent_block_trades_list_response_inner.hpp>

namespace binance::derivatives_trading_options::rest_api {

RecentBlockTradesListResponseInner
tag_invoke(boost::json::value_to_tag<RecentBlockTradesListResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "RecentBlockTradesListResponseInner");
    RecentBlockTradesListResponseInner out;
    common::detail::json::read(obj, "id", out.id);
    common::detail::json::read(obj, "tradeId", out.trade_id);
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "price", out.price);
    common::detail::json::read(obj, "qty", out.qty);
    common::detail::json::read(obj, "quoteQty", out.quote_qty);
    common::detail::json::read(obj, "side", out.side);
    common::detail::json::read(obj, "time", out.time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const RecentBlockTradesListResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "id", v.id);
    common::detail::json::write(obj, "tradeId", v.trade_id);
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "price", v.price);
    common::detail::json::write(obj, "qty", v.qty);
    common::detail::json::write(obj, "quoteQty", v.quote_qty);
    common::detail::json::write(obj, "side", v.side);
    common::detail::json::write(obj, "time", v.time);
}

} // namespace binance::derivatives_trading_options::rest_api
