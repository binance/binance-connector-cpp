//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_options/websocket_streams/models/open_interest_response_inner.hpp>

namespace binance::derivatives_trading_options::websocket_streams {

OpenInterestResponseInner tag_invoke(boost::json::value_to_tag<OpenInterestResponseInner> /*tag*/,
                                     const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "OpenInterestResponseInner");
    OpenInterestResponseInner out;
    common::detail::json::read(obj, "e", out.e);
    common::detail::json::read(obj, "E", out.e_uppercase);
    common::detail::json::read(obj, "s", out.s);
    common::detail::json::read(obj, "o", out.o);
    common::detail::json::read(obj, "h", out.h);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const OpenInterestResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "e", v.e);
    common::detail::json::write(obj, "E", v.e_uppercase);
    common::detail::json::write(obj, "s", v.s);
    common::detail::json::write(obj, "o", v.o);
    common::detail::json::write(obj, "h", v.h);
}

} // namespace binance::derivatives_trading_options::websocket_streams
