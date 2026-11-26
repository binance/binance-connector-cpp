//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin/websocket_streams/models/account_update_ab_inner.hpp>

namespace binance::derivatives_trading_portfolio_margin::websocket_streams {

AccountUpdateABInner tag_invoke(boost::json::value_to_tag<AccountUpdateABInner> /*tag*/,
                                const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "AccountUpdateABInner");
    AccountUpdateABInner out;
    common::detail::json::read(obj, "a", out.a);
    common::detail::json::read(obj, "wb", out.wb);
    common::detail::json::read(obj, "cw", out.cw);
    common::detail::json::read(obj, "bc", out.bc);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const AccountUpdateABInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "a", v.a);
    common::detail::json::write(obj, "wb", v.wb);
    common::detail::json::write(obj, "cw", v.cw);
    common::detail::json::write(obj, "bc", v.bc);
}

} // namespace binance::derivatives_trading_portfolio_margin::websocket_streams
