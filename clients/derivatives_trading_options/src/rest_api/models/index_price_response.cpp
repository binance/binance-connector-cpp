//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_options/rest_api/models/index_price_response.hpp>

namespace binance::derivatives_trading_options::rest_api {

IndexPriceResponse tag_invoke(boost::json::value_to_tag<IndexPriceResponse> /*tag*/,
                              const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "IndexPriceResponse");
    IndexPriceResponse out;
    common::detail::json::read(obj, "time", out.time);
    common::detail::json::read(obj, "indexPrice", out.index_price);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const IndexPriceResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "time", v.time);
    common::detail::json::write(obj, "indexPrice", v.index_price);
}

} // namespace binance::derivatives_trading_options::rest_api
