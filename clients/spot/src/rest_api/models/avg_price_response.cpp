//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/rest_api/models/avg_price_response.hpp>

namespace binance::spot::rest_api {

AvgPriceResponse tag_invoke(boost::json::value_to_tag<AvgPriceResponse> /*tag*/,
                            const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "AvgPriceResponse");
    AvgPriceResponse out;
    common::detail::json::read(obj, "mins", out.mins);
    common::detail::json::read(obj, "price", out.price);
    common::detail::json::read(obj, "closeTime", out.close_time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const AvgPriceResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "mins", v.mins);
    common::detail::json::write(obj, "price", v.price);
    common::detail::json::write(obj, "closeTime", v.close_time);
}

} // namespace binance::spot::rest_api
