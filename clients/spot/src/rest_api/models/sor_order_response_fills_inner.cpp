//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/rest_api/models/sor_order_response_fills_inner.hpp>

namespace binance::spot::rest_api {

SorOrderResponseFillsInner tag_invoke(boost::json::value_to_tag<SorOrderResponseFillsInner> /*tag*/,
                                      const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "SorOrderResponseFillsInner");
    SorOrderResponseFillsInner out;
    common::detail::json::read(obj, "matchType", out.match_type);
    common::detail::json::read(obj, "price", out.price);
    common::detail::json::read(obj, "qty", out.qty);
    common::detail::json::read(obj, "commission", out.commission);
    common::detail::json::read(obj, "commissionAsset", out.commission_asset);
    common::detail::json::read(obj, "tradeId", out.trade_id);
    common::detail::json::read(obj, "allocId", out.alloc_id);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const SorOrderResponseFillsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "matchType", v.match_type);
    common::detail::json::write(obj, "price", v.price);
    common::detail::json::write(obj, "qty", v.qty);
    common::detail::json::write(obj, "commission", v.commission);
    common::detail::json::write(obj, "commissionAsset", v.commission_asset);
    common::detail::json::write(obj, "tradeId", v.trade_id);
    common::detail::json::write(obj, "allocId", v.alloc_id);
}

} // namespace binance::spot::rest_api
