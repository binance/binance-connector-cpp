//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_options/rest_api/models/exchange_information_response.hpp>

namespace binance::derivatives_trading_options::rest_api {

ExchangeInformationResponse
tag_invoke(boost::json::value_to_tag<ExchangeInformationResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "ExchangeInformationResponse");
    ExchangeInformationResponse out;
    common::detail::json::read(obj, "timezone", out.timezone);
    common::detail::json::read(obj, "serverTime", out.server_time);
    common::detail::json::read(obj, "optionContracts", out.option_contracts);
    common::detail::json::read(obj, "optionAssets", out.option_assets);
    common::detail::json::read(obj, "optionSymbols", out.option_symbols);
    common::detail::json::read(obj, "rateLimits", out.rate_limits);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const ExchangeInformationResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "timezone", v.timezone);
    common::detail::json::write(obj, "serverTime", v.server_time);
    common::detail::json::write(obj, "optionContracts", v.option_contracts);
    common::detail::json::write(obj, "optionAssets", v.option_assets);
    common::detail::json::write(obj, "optionSymbols", v.option_symbols);
    common::detail::json::write(obj, "rateLimits", v.rate_limits);
}

} // namespace binance::derivatives_trading_options::rest_api
