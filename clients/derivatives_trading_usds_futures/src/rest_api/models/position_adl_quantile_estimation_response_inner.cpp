//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/position_adl_quantile_estimation_response_inner.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

PositionAdlQuantileEstimationResponseInner
tag_invoke(boost::json::value_to_tag<PositionAdlQuantileEstimationResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "PositionAdlQuantileEstimationResponseInner");
    PositionAdlQuantileEstimationResponseInner out;
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "adlQuantile", out.adl_quantile);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const PositionAdlQuantileEstimationResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "adlQuantile", v.adl_quantile);
}

} // namespace binance::derivatives_trading_usds_futures::rest_api
