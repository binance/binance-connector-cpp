//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/w3w_prediction/rest_api/models/get_market_detail_response_variant_data.hpp>

namespace binance::w3w_prediction::rest_api {

GetMarketDetailResponseVariantData
tag_invoke(boost::json::value_to_tag<GetMarketDetailResponseVariantData> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetMarketDetailResponseVariantData");
    GetMarketDetailResponseVariantData out;
    common::detail::json::read(obj, "type", out.type);
    common::detail::json::read(obj, "startPrice", out.start_price);
    common::detail::json::read(obj, "endPrice", out.end_price);
    common::detail::json::read(obj, "priceFeedId", out.price_feed_id);
    common::detail::json::read(obj, "priceFeedProvider", out.price_feed_provider);
    common::detail::json::read(obj, "priceFeedSymbol", out.price_feed_symbol);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetMarketDetailResponseVariantData& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "type", v.type);
    common::detail::json::write(obj, "startPrice", v.start_price);
    common::detail::json::write(obj, "endPrice", v.end_price);
    common::detail::json::write(obj, "priceFeedId", v.price_feed_id);
    common::detail::json::write(obj, "priceFeedProvider", v.price_feed_provider);
    common::detail::json::write(obj, "priceFeedSymbol", v.price_feed_symbol);
}

} // namespace binance::w3w_prediction::rest_api
