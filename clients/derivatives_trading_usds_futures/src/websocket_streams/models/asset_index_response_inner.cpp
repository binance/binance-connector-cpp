//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_streams/models/asset_index_response_inner.hpp>

namespace binance::derivatives_trading_usds_futures::websocket_streams {

AssetIndexResponseInner tag_invoke(boost::json::value_to_tag<AssetIndexResponseInner> /*tag*/,
                                   const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "AssetIndexResponseInner");
    AssetIndexResponseInner out;
    common::detail::json::read(obj, "e", out.e);
    common::detail::json::read(obj, "E", out.e_uppercase);
    common::detail::json::read(obj, "s", out.s);
    common::detail::json::read(obj, "i", out.i);
    common::detail::json::read(obj, "b", out.b);
    common::detail::json::read(obj, "a", out.a);
    common::detail::json::read(obj, "B", out.b_uppercase);
    common::detail::json::read(obj, "A", out.a_uppercase);
    common::detail::json::read(obj, "q", out.q);
    common::detail::json::read(obj, "g", out.g);
    common::detail::json::read(obj, "Q", out.q_uppercase);
    common::detail::json::read(obj, "G", out.g_uppercase);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const AssetIndexResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "e", v.e);
    common::detail::json::write(obj, "E", v.e_uppercase);
    common::detail::json::write(obj, "s", v.s);
    common::detail::json::write(obj, "i", v.i);
    common::detail::json::write(obj, "b", v.b);
    common::detail::json::write(obj, "a", v.a);
    common::detail::json::write(obj, "B", v.b_uppercase);
    common::detail::json::write(obj, "A", v.a_uppercase);
    common::detail::json::write(obj, "q", v.q);
    common::detail::json::write(obj, "g", v.g);
    common::detail::json::write(obj, "Q", v.q_uppercase);
    common::detail::json::write(obj, "G", v.g_uppercase);
}

} // namespace binance::derivatives_trading_usds_futures::websocket_streams
