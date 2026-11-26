//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/get_funding_rate_info_response_inner.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

GetFundingRateInfoResponseInner
tag_invoke(boost::json::value_to_tag<GetFundingRateInfoResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetFundingRateInfoResponseInner");
    GetFundingRateInfoResponseInner out;
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "adjustedFundingRateCap", out.adjusted_funding_rate_cap);
    common::detail::json::read(obj, "adjustedFundingRateFloor", out.adjusted_funding_rate_floor);
    common::detail::json::read(obj, "fundingIntervalHours", out.funding_interval_hours);
    common::detail::json::read(obj, "disclaimer", out.disclaimer);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetFundingRateInfoResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "adjustedFundingRateCap", v.adjusted_funding_rate_cap);
    common::detail::json::write(obj, "adjustedFundingRateFloor", v.adjusted_funding_rate_floor);
    common::detail::json::write(obj, "fundingIntervalHours", v.funding_interval_hours);
    common::detail::json::write(obj, "disclaimer", v.disclaimer);
}

} // namespace binance::derivatives_trading_usds_futures::rest_api
