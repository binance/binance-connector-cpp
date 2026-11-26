//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/futures_trading_quantitative_rules_indicators_response_indicators.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

FuturesTradingQuantitativeRulesIndicatorsResponseIndicators tag_invoke(
    boost::json::value_to_tag<FuturesTradingQuantitativeRulesIndicatorsResponseIndicators> /*tag*/,
    const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "FuturesTradingQuantitativeRulesIndicatorsResponseIndicators");
    FuturesTradingQuantitativeRulesIndicatorsResponseIndicators out;
    common::detail::json::read(obj, "BTCUSDT", out.btcusdt);
    common::detail::json::read(obj, "ETHUSDT", out.ethusdt);
    common::detail::json::read(obj, "ACCOUNT", out.account);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const FuturesTradingQuantitativeRulesIndicatorsResponseIndicators& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "BTCUSDT", v.btcusdt);
    common::detail::json::write(obj, "ETHUSDT", v.ethusdt);
    common::detail::json::write(obj, "ACCOUNT", v.account);
}

} // namespace binance::derivatives_trading_usds_futures::rest_api
