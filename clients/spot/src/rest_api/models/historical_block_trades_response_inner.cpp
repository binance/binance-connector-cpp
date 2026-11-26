//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/rest_api/models/historical_block_trades_response_inner.hpp>

namespace binance::spot::rest_api {

HistoricalBlockTradesResponseInner
tag_invoke(boost::json::value_to_tag<HistoricalBlockTradesResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "HistoricalBlockTradesResponseInner");
    HistoricalBlockTradesResponseInner out;
    common::detail::json::read(obj, "id", out.id);
    common::detail::json::read(obj, "price", out.price);
    common::detail::json::read(obj, "qty", out.qty);
    common::detail::json::read(obj, "quoteQty", out.quote_qty);
    common::detail::json::read(obj, "time", out.time);
    common::detail::json::read(obj, "isBuyerMaker", out.is_buyer_maker);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const HistoricalBlockTradesResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "id", v.id);
    common::detail::json::write(obj, "price", v.price);
    common::detail::json::write(obj, "qty", v.qty);
    common::detail::json::write(obj, "quoteQty", v.quote_qty);
    common::detail::json::write(obj, "time", v.time);
    common::detail::json::write(obj, "isBuyerMaker", v.is_buyer_maker);
}

} // namespace binance::spot::rest_api
