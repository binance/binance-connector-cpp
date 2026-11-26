//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/websocket_streams/models/list_status_o_inner.hpp>

namespace binance::spot::websocket_streams {

ListStatusOInner tag_invoke(boost::json::value_to_tag<ListStatusOInner> /*tag*/,
                            const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "ListStatusOInner");
    ListStatusOInner out;
    common::detail::json::read(obj, "s", out.s);
    common::detail::json::read(obj, "i", out.i);
    common::detail::json::read(obj, "c", out.c);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const ListStatusOInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "s", v.s);
    common::detail::json::write(obj, "i", v.i);
    common::detail::json::write(obj, "c", v.c);
}

} // namespace binance::spot::websocket_streams
