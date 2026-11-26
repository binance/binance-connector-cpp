//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/margin_trading/rest_api/models/margin_manual_liquidation_response.hpp>

namespace binance::margin_trading::rest_api {

MarginManualLiquidationResponse
tag_invoke(boost::json::value_to_tag<MarginManualLiquidationResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "MarginManualLiquidationResponse");
    MarginManualLiquidationResponse out;
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "interest", out.interest);
    common::detail::json::read(obj, "principal", out.principal);
    common::detail::json::read(obj, "liabilityAsset", out.liability_asset);
    common::detail::json::read(obj, "liabilityQty", out.liability_qty);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const MarginManualLiquidationResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "interest", v.interest);
    common::detail::json::write(obj, "principal", v.principal);
    common::detail::json::write(obj, "liabilityAsset", v.liability_asset);
    common::detail::json::write(obj, "liabilityQty", v.liability_qty);
}

} // namespace binance::margin_trading::rest_api
