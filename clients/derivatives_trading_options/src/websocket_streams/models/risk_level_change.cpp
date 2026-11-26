//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_options/websocket_streams/models/risk_level_change.hpp>

namespace binance::derivatives_trading_options::websocket_streams {

RiskLevelChange tag_invoke(boost::json::value_to_tag<RiskLevelChange> /*tag*/,
                           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "RiskLevelChange");
    RiskLevelChange out;
    common::detail::json::read(obj, "E", out.e_uppercase);
    common::detail::json::read(obj, "s", out.s);
    common::detail::json::read(obj, "mb", out.mb);
    common::detail::json::read(obj, "mm", out.mm);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const RiskLevelChange& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "E", v.e_uppercase);
    common::detail::json::write(obj, "s", v.s);
    common::detail::json::write(obj, "mb", v.mb);
    common::detail::json::write(obj, "mm", v.mm);
}

} // namespace binance::derivatives_trading_options::websocket_streams
