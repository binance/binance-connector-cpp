//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_streams/models/strategy_update_su.hpp>

namespace binance::derivatives_trading_usds_futures::websocket_streams {

StrategyUpdateSu tag_invoke(boost::json::value_to_tag<StrategyUpdateSu> /*tag*/,
                            const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "StrategyUpdateSu");
    StrategyUpdateSu out;
    common::detail::json::read(obj, "si", out.si);
    common::detail::json::read(obj, "st", out.st);
    common::detail::json::read(obj, "ss", out.ss);
    common::detail::json::read(obj, "s", out.s);
    common::detail::json::read(obj, "ut", out.ut);
    common::detail::json::read(obj, "c", out.c);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const StrategyUpdateSu& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "si", v.si);
    common::detail::json::write(obj, "st", v.st);
    common::detail::json::write(obj, "ss", v.ss);
    common::detail::json::write(obj, "s", v.s);
    common::detail::json::write(obj, "ut", v.ut);
    common::detail::json::write(obj, "c", v.c);
}

} // namespace binance::derivatives_trading_usds_futures::websocket_streams
