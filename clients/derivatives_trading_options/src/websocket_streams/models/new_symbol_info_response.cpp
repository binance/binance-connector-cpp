//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_options/websocket_streams/models/new_symbol_info_response.hpp>

namespace binance::derivatives_trading_options::websocket_streams {

NewSymbolInfoResponse tag_invoke(boost::json::value_to_tag<NewSymbolInfoResponse> /*tag*/,
                                 const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "NewSymbolInfoResponse");
    NewSymbolInfoResponse out;
    common::detail::json::read(obj, "e", out.e);
    common::detail::json::read(obj, "E", out.e_uppercase);
    common::detail::json::read(obj, "s", out.s);
    common::detail::json::read(obj, "ps", out.ps);
    common::detail::json::read(obj, "qa", out.qa);
    common::detail::json::read(obj, "d", out.d);
    common::detail::json::read(obj, "sp", out.sp);
    common::detail::json::read(obj, "dt", out.dt);
    common::detail::json::read(obj, "u", out.u);
    common::detail::json::read(obj, "ot", out.ot);
    common::detail::json::read(obj, "cs", out.cs);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const NewSymbolInfoResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "e", v.e);
    common::detail::json::write(obj, "E", v.e_uppercase);
    common::detail::json::write(obj, "s", v.s);
    common::detail::json::write(obj, "ps", v.ps);
    common::detail::json::write(obj, "qa", v.qa);
    common::detail::json::write(obj, "d", v.d);
    common::detail::json::write(obj, "sp", v.sp);
    common::detail::json::write(obj, "dt", v.dt);
    common::detail::json::write(obj, "u", v.u);
    common::detail::json::write(obj, "ot", v.ot);
    common::detail::json::write(obj, "cs", v.cs);
}

} // namespace binance::derivatives_trading_options::websocket_streams
