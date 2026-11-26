//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/adl_risk_response2_inner.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

AdlRiskResponse2Inner tag_invoke(boost::json::value_to_tag<AdlRiskResponse2Inner> /*tag*/,
                                 const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "AdlRiskResponse2Inner");
    AdlRiskResponse2Inner out;
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "adlRisk", out.adl_risk);
    common::detail::json::read(obj, "updateTime", out.update_time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const AdlRiskResponse2Inner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "adlRisk", v.adl_risk);
    common::detail::json::write(obj, "updateTime", v.update_time);
}

} // namespace binance::derivatives_trading_usds_futures::rest_api
