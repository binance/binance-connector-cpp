//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/stocks/rest_api/models/latest_quote_response.hpp>

namespace binance::stocks::rest_api {

LatestQuoteResponse tag_invoke(boost::json::value_to_tag<LatestQuoteResponse> /*tag*/,
                               const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "LatestQuoteResponse");
    LatestQuoteResponse out;
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "bidPrice", out.bid_price);
    common::detail::json::read(obj, "askPrice", out.ask_price);
    common::detail::json::read(obj, "bidSize", out.bid_size);
    common::detail::json::read(obj, "askSize", out.ask_size);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const LatestQuoteResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "bidPrice", v.bid_price);
    common::detail::json::write(obj, "askPrice", v.ask_price);
    common::detail::json::write(obj, "bidSize", v.bid_size);
    common::detail::json::write(obj, "askSize", v.ask_size);
}

} // namespace binance::stocks::rest_api
