//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_streams/models/composite_index_symbol_information_streams_response_c_inner.hpp>

namespace binance::derivatives_trading_usds_futures::websocket_streams {

CompositeIndexSymbolInformationStreamsResponseCInner
tag_invoke(boost::json::value_to_tag<CompositeIndexSymbolInformationStreamsResponseCInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "CompositeIndexSymbolInformationStreamsResponseCInner");
    CompositeIndexSymbolInformationStreamsResponseCInner out;
    common::detail::json::read(obj, "b", out.b);
    common::detail::json::read(obj, "q", out.q);
    common::detail::json::read(obj, "w", out.w);
    common::detail::json::read(obj, "W", out.w_uppercase);
    common::detail::json::read(obj, "i", out.i);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const CompositeIndexSymbolInformationStreamsResponseCInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "b", v.b);
    common::detail::json::write(obj, "q", v.q);
    common::detail::json::write(obj, "w", v.w);
    common::detail::json::write(obj, "W", v.w_uppercase);
    common::detail::json::write(obj, "i", v.i);
}

} // namespace binance::derivatives_trading_usds_futures::websocket_streams
