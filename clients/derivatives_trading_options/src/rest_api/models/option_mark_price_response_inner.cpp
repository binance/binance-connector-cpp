//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_options/rest_api/models/option_mark_price_response_inner.hpp>

namespace binance::derivatives_trading_options::rest_api {

OptionMarkPriceResponseInner
tag_invoke(boost::json::value_to_tag<OptionMarkPriceResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "OptionMarkPriceResponseInner");
    OptionMarkPriceResponseInner out;
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "markPrice", out.mark_price);
    common::detail::json::read(obj, "bidIV", out.bid_iv);
    common::detail::json::read(obj, "askIV", out.ask_iv);
    common::detail::json::read(obj, "markIV", out.mark_iv);
    common::detail::json::read(obj, "delta", out.delta);
    common::detail::json::read(obj, "theta", out.theta);
    common::detail::json::read(obj, "gamma", out.gamma);
    common::detail::json::read(obj, "vega", out.vega);
    common::detail::json::read(obj, "highPriceLimit", out.high_price_limit);
    common::detail::json::read(obj, "lowPriceLimit", out.low_price_limit);
    common::detail::json::read(obj, "riskFreeInterest", out.risk_free_interest);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const OptionMarkPriceResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "markPrice", v.mark_price);
    common::detail::json::write(obj, "bidIV", v.bid_iv);
    common::detail::json::write(obj, "askIV", v.ask_iv);
    common::detail::json::write(obj, "markIV", v.mark_iv);
    common::detail::json::write(obj, "delta", v.delta);
    common::detail::json::write(obj, "theta", v.theta);
    common::detail::json::write(obj, "gamma", v.gamma);
    common::detail::json::write(obj, "vega", v.vega);
    common::detail::json::write(obj, "highPriceLimit", v.high_price_limit);
    common::detail::json::write(obj, "lowPriceLimit", v.low_price_limit);
    common::detail::json::write(obj, "riskFreeInterest", v.risk_free_interest);
}

} // namespace binance::derivatives_trading_options::rest_api
