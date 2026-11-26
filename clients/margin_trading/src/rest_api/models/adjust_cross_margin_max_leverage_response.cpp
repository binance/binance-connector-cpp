//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/margin_trading/rest_api/models/adjust_cross_margin_max_leverage_response.hpp>

namespace binance::margin_trading::rest_api {

AdjustCrossMarginMaxLeverageResponse
tag_invoke(boost::json::value_to_tag<AdjustCrossMarginMaxLeverageResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "AdjustCrossMarginMaxLeverageResponse");
    AdjustCrossMarginMaxLeverageResponse out;
    common::detail::json::read(obj, "success", out.success);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const AdjustCrossMarginMaxLeverageResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "success", v.success);
}

} // namespace binance::margin_trading::rest_api
