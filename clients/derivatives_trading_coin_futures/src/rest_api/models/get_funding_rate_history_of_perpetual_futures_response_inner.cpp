//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/get_funding_rate_history_of_perpetual_futures_response_inner.hpp>

namespace binance::derivatives_trading_coin_futures::rest_api {

GetFundingRateHistoryOfPerpetualFuturesResponseInner
tag_invoke(boost::json::value_to_tag<GetFundingRateHistoryOfPerpetualFuturesResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetFundingRateHistoryOfPerpetualFuturesResponseInner");
    GetFundingRateHistoryOfPerpetualFuturesResponseInner out;
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "fundingTime", out.funding_time);
    common::detail::json::read(obj, "fundingRate", out.funding_rate);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetFundingRateHistoryOfPerpetualFuturesResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "fundingTime", v.funding_time);
    common::detail::json::write(obj, "fundingRate", v.funding_rate);
}

} // namespace binance::derivatives_trading_coin_futures::rest_api
