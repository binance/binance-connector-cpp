//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin_pro/websocket_streams/models/pm_pro_account_update.hpp>

namespace binance::derivatives_trading_portfolio_margin_pro::websocket_streams {

PmProAccountUpdate tag_invoke(boost::json::value_to_tag<PmProAccountUpdate> /*tag*/,
                              const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "PmProAccountUpdate");
    PmProAccountUpdate out;
    common::detail::json::read(obj, "E", out.e_uppercase);
    common::detail::json::read(obj, "u", out.u);
    common::detail::json::read(obj, "eq", out.eq);
    common::detail::json::read(obj, "ae", out.ae);
    common::detail::json::read(obj, "im", out.im);
    common::detail::json::read(obj, "mm", out.mm);
    common::detail::json::read(obj, "avb", out.avb);
    common::detail::json::read(obj, "vmw", out.vmw);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const PmProAccountUpdate& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "E", v.e_uppercase);
    common::detail::json::write(obj, "u", v.u);
    common::detail::json::write(obj, "eq", v.eq);
    common::detail::json::write(obj, "ae", v.ae);
    common::detail::json::write(obj, "im", v.im);
    common::detail::json::write(obj, "mm", v.mm);
    common::detail::json::write(obj, "avb", v.avb);
    common::detail::json::write(obj, "vmw", v.vmw);
}

} // namespace binance::derivatives_trading_portfolio_margin_pro::websocket_streams
