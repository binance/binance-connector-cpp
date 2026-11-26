//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/margin_trading/rest_api/models/get_limit_price_pairs_response.hpp>

namespace binance::margin_trading::rest_api {

GetLimitPricePairsResponse tag_invoke(boost::json::value_to_tag<GetLimitPricePairsResponse> /*tag*/,
                                      const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetLimitPricePairsResponse");
    GetLimitPricePairsResponse out;
    common::detail::json::read(obj, "crossMarginSymbols", out.cross_margin_symbols);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetLimitPricePairsResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "crossMarginSymbols", v.cross_margin_symbols);
}

} // namespace binance::margin_trading::rest_api
