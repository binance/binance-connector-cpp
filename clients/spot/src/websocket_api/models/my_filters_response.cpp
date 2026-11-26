//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/websocket_api/models/my_filters_response.hpp>

namespace binance::spot::websocket_api {

MyFiltersResponse tag_invoke(boost::json::value_to_tag<MyFiltersResponse> /*tag*/,
                             const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "MyFiltersResponse");
    MyFiltersResponse out;
    common::detail::json::read(obj, "exchangeFilters", out.exchange_filters);
    common::detail::json::read(obj, "symbolFilters", out.symbol_filters);
    common::detail::json::read(obj, "assetFilters", out.asset_filters);
    common::detail::json::read(obj, "rateLimits", out.rate_limits);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const MyFiltersResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "exchangeFilters", v.exchange_filters);
    common::detail::json::write(obj, "symbolFilters", v.symbol_filters);
    common::detail::json::write(obj, "assetFilters", v.asset_filters);
    common::detail::json::write(obj, "rateLimits", v.rate_limits);
}

} // namespace binance::spot::websocket_api
