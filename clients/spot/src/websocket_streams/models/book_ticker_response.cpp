//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/websocket_streams/models/book_ticker_response.hpp>

namespace binance::spot::websocket_streams {

BookTickerResponse tag_invoke(boost::json::value_to_tag<BookTickerResponse> /*tag*/,
                              const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "BookTickerResponse");
    BookTickerResponse out;
    common::detail::json::read(obj, "u", out.u);
    common::detail::json::read(obj, "s", out.s);
    common::detail::json::read(obj, "b", out.b);
    common::detail::json::read(obj, "B", out.b_uppercase);
    common::detail::json::read(obj, "a", out.a);
    common::detail::json::read(obj, "A", out.a_uppercase);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const BookTickerResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "u", v.u);
    common::detail::json::write(obj, "s", v.s);
    common::detail::json::write(obj, "b", v.b);
    common::detail::json::write(obj, "B", v.b_uppercase);
    common::detail::json::write(obj, "a", v.a);
    common::detail::json::write(obj, "A", v.a_uppercase);
}

} // namespace binance::spot::websocket_streams
