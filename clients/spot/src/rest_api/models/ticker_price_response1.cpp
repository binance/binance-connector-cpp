//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/rest_api/models/ticker_price_response1.hpp>

namespace binance::spot::rest_api {

TickerPriceResponse1 tag_invoke(boost::json::value_to_tag<TickerPriceResponse1> /*tag*/,
                                const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "TickerPriceResponse1");
    TickerPriceResponse1 out;
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "price", out.price);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const TickerPriceResponse1& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "price", v.price);
}

} // namespace binance::spot::rest_api
