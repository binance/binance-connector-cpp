//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/margin_trading/rest_api/models/get_future_hourly_interest_rate_response_inner.hpp>

namespace binance::margin_trading::rest_api {

GetFutureHourlyInterestRateResponseInner
tag_invoke(boost::json::value_to_tag<GetFutureHourlyInterestRateResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetFutureHourlyInterestRateResponseInner");
    GetFutureHourlyInterestRateResponseInner out;
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "nextHourlyInterestRate", out.next_hourly_interest_rate);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetFutureHourlyInterestRateResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "nextHourlyInterestRate", v.next_hourly_interest_rate);
}

} // namespace binance::margin_trading::rest_api
