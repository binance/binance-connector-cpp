//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/cm_position_adl_quantile_estimation_response_inner_adl_quantile.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

CmPositionAdlQuantileEstimationResponseInnerAdlQuantile tag_invoke(
    boost::json::value_to_tag<CmPositionAdlQuantileEstimationResponseInnerAdlQuantile> /*tag*/,
    const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "CmPositionAdlQuantileEstimationResponseInnerAdlQuantile");
    CmPositionAdlQuantileEstimationResponseInnerAdlQuantile out;
    common::detail::json::read(obj, "LONG", out.r_long);
    common::detail::json::read(obj, "SHORT", out.r_short);
    common::detail::json::read(obj, "HEDGE", out.hedge);
    common::detail::json::read(obj, "BOTH", out.both);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const CmPositionAdlQuantileEstimationResponseInnerAdlQuantile& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "LONG", v.r_long);
    common::detail::json::write(obj, "SHORT", v.r_short);
    common::detail::json::write(obj, "HEDGE", v.hedge);
    common::detail::json::write(obj, "BOTH", v.both);
}

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
