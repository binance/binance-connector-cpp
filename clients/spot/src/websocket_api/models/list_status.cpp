//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/websocket_api/models/list_status.hpp>

namespace binance::spot::websocket_api {

ListStatus tag_invoke(boost::json::value_to_tag<ListStatus> /*tag*/, const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "ListStatus");
    ListStatus out;
    common::detail::json::read(obj, "E", out.e_uppercase);
    common::detail::json::read(obj, "s", out.s);
    common::detail::json::read(obj, "g", out.g);
    common::detail::json::read(obj, "c", out.c);
    common::detail::json::read(obj, "l", out.l);
    common::detail::json::read(obj, "L", out.l_uppercase);
    common::detail::json::read(obj, "r", out.r);
    common::detail::json::read(obj, "C", out.c_uppercase);
    common::detail::json::read(obj, "T", out.t_uppercase);
    common::detail::json::read(obj, "O", out.o_uppercase);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv, const ListStatus& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "E", v.e_uppercase);
    common::detail::json::write(obj, "s", v.s);
    common::detail::json::write(obj, "g", v.g);
    common::detail::json::write(obj, "c", v.c);
    common::detail::json::write(obj, "l", v.l);
    common::detail::json::write(obj, "L", v.l_uppercase);
    common::detail::json::write(obj, "r", v.r);
    common::detail::json::write(obj, "C", v.c_uppercase);
    common::detail::json::write(obj, "T", v.t_uppercase);
    common::detail::json::write(obj, "O", v.o_uppercase);
}

} // namespace binance::spot::websocket_api
