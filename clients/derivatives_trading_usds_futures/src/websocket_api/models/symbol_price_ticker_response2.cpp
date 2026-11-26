//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_api/models/symbol_price_ticker_response2.hpp>

namespace binance::derivatives_trading_usds_futures::websocket_api {

SymbolPriceTickerResponse2 tag_invoke(boost::json::value_to_tag<SymbolPriceTickerResponse2> /*tag*/,
                                      const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "SymbolPriceTickerResponse2");
    SymbolPriceTickerResponse2 out;
    common::detail::json::read(obj, "id", out.id);
    common::detail::json::read(obj, "status", out.status);
    common::detail::json::read(obj, "result", out.result);
    common::detail::json::read(obj, "rateLimits", out.rate_limits);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const SymbolPriceTickerResponse2& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "id", v.id);
    common::detail::json::write(obj, "status", v.status);
    common::detail::json::write(obj, "result", v.result);
    common::detail::json::write(obj, "rateLimits", v.rate_limits);
}

} // namespace binance::derivatives_trading_usds_futures::websocket_api
