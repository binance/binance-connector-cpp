//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_options/websocket_streams/models/balance_position_update_b_inner.hpp>

namespace binance::derivatives_trading_options::websocket_streams {

BalancePositionUpdateBInner
tag_invoke(boost::json::value_to_tag<BalancePositionUpdateBInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "BalancePositionUpdateBInner");
    BalancePositionUpdateBInner out;
    common::detail::json::read(obj, "a", out.a);
    common::detail::json::read(obj, "b", out.b);
    common::detail::json::read(obj, "bc", out.bc);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const BalancePositionUpdateBInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "a", v.a);
    common::detail::json::write(obj, "b", v.b);
    common::detail::json::write(obj, "bc", v.bc);
}

} // namespace binance::derivatives_trading_options::websocket_streams
