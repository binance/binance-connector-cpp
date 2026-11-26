//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_streams/models/grid_update_gu.hpp>

namespace binance::derivatives_trading_usds_futures::websocket_streams {

GridUpdateGu tag_invoke(boost::json::value_to_tag<GridUpdateGu> /*tag*/,
                        const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GridUpdateGu");
    GridUpdateGu out;
    common::detail::json::read(obj, "si", out.si);
    common::detail::json::read(obj, "st", out.st);
    common::detail::json::read(obj, "ss", out.ss);
    common::detail::json::read(obj, "s", out.s);
    common::detail::json::read(obj, "r", out.r);
    common::detail::json::read(obj, "up", out.up);
    common::detail::json::read(obj, "uq", out.uq);
    common::detail::json::read(obj, "uf", out.uf);
    common::detail::json::read(obj, "mp", out.mp);
    common::detail::json::read(obj, "ut", out.ut);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GridUpdateGu& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "si", v.si);
    common::detail::json::write(obj, "st", v.st);
    common::detail::json::write(obj, "ss", v.ss);
    common::detail::json::write(obj, "s", v.s);
    common::detail::json::write(obj, "r", v.r);
    common::detail::json::write(obj, "up", v.up);
    common::detail::json::write(obj, "uq", v.uq);
    common::detail::json::write(obj, "uf", v.uf);
    common::detail::json::write(obj, "mp", v.mp);
    common::detail::json::write(obj, "ut", v.ut);
}

} // namespace binance::derivatives_trading_usds_futures::websocket_streams
