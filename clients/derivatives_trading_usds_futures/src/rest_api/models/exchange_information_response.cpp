//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/exchange_information_response.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

ExchangeInformationResponse
tag_invoke(boost::json::value_to_tag<ExchangeInformationResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "ExchangeInformationResponse");
    ExchangeInformationResponse out;
    common::detail::json::read(obj, "exchangeFilters", out.exchange_filters);
    common::detail::json::read(obj, "rateLimits", out.rate_limits);
    common::detail::json::read(obj, "serverTime", out.server_time);
    common::detail::json::read(obj, "assets", out.assets);
    common::detail::json::read(obj, "symbols", out.symbols);
    common::detail::json::read(obj, "timezone", out.timezone);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const ExchangeInformationResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "exchangeFilters", v.exchange_filters);
    common::detail::json::write(obj, "rateLimits", v.rate_limits);
    common::detail::json::write(obj, "serverTime", v.server_time);
    common::detail::json::write(obj, "assets", v.assets);
    common::detail::json::write(obj, "symbols", v.symbols);
    common::detail::json::write(obj, "timezone", v.timezone);
}

} // namespace binance::derivatives_trading_usds_futures::rest_api
