//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/get_position_margin_change_history_response_inner.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

GetPositionMarginChangeHistoryResponseInner
tag_invoke(boost::json::value_to_tag<GetPositionMarginChangeHistoryResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetPositionMarginChangeHistoryResponseInner");
    GetPositionMarginChangeHistoryResponseInner out;
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "type", out.type);
    common::detail::json::read(obj, "deltaType", out.delta_type);
    common::detail::json::read(obj, "amount", out.amount);
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "time", out.time);
    common::detail::json::read(obj, "positionSide", out.position_side);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetPositionMarginChangeHistoryResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "type", v.type);
    common::detail::json::write(obj, "deltaType", v.delta_type);
    common::detail::json::write(obj, "amount", v.amount);
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "time", v.time);
    common::detail::json::write(obj, "positionSide", v.position_side);
}

} // namespace binance::derivatives_trading_usds_futures::rest_api
