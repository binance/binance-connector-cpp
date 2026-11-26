//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/compressed_aggregate_trades_list_response_inner.hpp>

namespace binance::derivatives_trading_coin_futures::rest_api {

CompressedAggregateTradesListResponseInner
tag_invoke(boost::json::value_to_tag<CompressedAggregateTradesListResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "CompressedAggregateTradesListResponseInner");
    CompressedAggregateTradesListResponseInner out;
    common::detail::json::read(obj, "a", out.a);
    common::detail::json::read(obj, "p", out.p);
    common::detail::json::read(obj, "q", out.q);
    common::detail::json::read(obj, "f", out.f);
    common::detail::json::read(obj, "l", out.l);
    common::detail::json::read(obj, "T", out.t_uppercase);
    common::detail::json::read(obj, "m", out.m);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const CompressedAggregateTradesListResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "a", v.a);
    common::detail::json::write(obj, "p", v.p);
    common::detail::json::write(obj, "q", v.q);
    common::detail::json::write(obj, "f", v.f);
    common::detail::json::write(obj, "l", v.l);
    common::detail::json::write(obj, "T", v.t_uppercase);
    common::detail::json::write(obj, "m", v.m);
}

} // namespace binance::derivatives_trading_coin_futures::rest_api
