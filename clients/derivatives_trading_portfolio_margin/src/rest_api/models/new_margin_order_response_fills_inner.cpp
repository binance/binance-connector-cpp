//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/new_margin_order_response_fills_inner.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

NewMarginOrderResponseFillsInner
tag_invoke(boost::json::value_to_tag<NewMarginOrderResponseFillsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "NewMarginOrderResponseFillsInner");
    NewMarginOrderResponseFillsInner out;
    common::detail::json::read(obj, "price", out.price);
    common::detail::json::read(obj, "qty", out.qty);
    common::detail::json::read(obj, "commission", out.commission);
    common::detail::json::read(obj, "commissionAsset", out.commission_asset);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const NewMarginOrderResponseFillsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "price", v.price);
    common::detail::json::write(obj, "qty", v.qty);
    common::detail::json::write(obj, "commission", v.commission);
    common::detail::json::write(obj, "commissionAsset", v.commission_asset);
}

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
