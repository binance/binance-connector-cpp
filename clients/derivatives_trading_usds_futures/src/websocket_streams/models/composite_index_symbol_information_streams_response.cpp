//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_streams/models/composite_index_symbol_information_streams_response.hpp>

namespace binance::derivatives_trading_usds_futures::websocket_streams {

CompositeIndexSymbolInformationStreamsResponse
tag_invoke(boost::json::value_to_tag<CompositeIndexSymbolInformationStreamsResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "CompositeIndexSymbolInformationStreamsResponse");
    CompositeIndexSymbolInformationStreamsResponse out;
    common::detail::json::read(obj, "e", out.e);
    common::detail::json::read(obj, "E", out.e_uppercase);
    common::detail::json::read(obj, "s", out.s);
    common::detail::json::read(obj, "p", out.p);
    common::detail::json::read(obj, "C", out.c_uppercase);
    common::detail::json::read(obj, "c", out.c);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const CompositeIndexSymbolInformationStreamsResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "e", v.e);
    common::detail::json::write(obj, "E", v.e_uppercase);
    common::detail::json::write(obj, "s", v.s);
    common::detail::json::write(obj, "p", v.p);
    common::detail::json::write(obj, "C", v.c_uppercase);
    common::detail::json::write(obj, "c", v.c);
}

} // namespace binance::derivatives_trading_usds_futures::websocket_streams
