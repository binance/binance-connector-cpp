//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/websocket_api/models/reference_price_calculation_response_result.hpp>

namespace binance::spot::websocket_api {

ReferencePriceCalculationResponseResult
tag_invoke(boost::json::value_to_tag<ReferencePriceCalculationResponseResult> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "ReferencePriceCalculationResponseResult");
    ReferencePriceCalculationResponseResult out;
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "calculationType", out.calculation_type);
    common::detail::json::read(obj, "bucketCount", out.bucket_count);
    common::detail::json::read(obj, "bucketWidthMs", out.bucket_width_ms);
    common::detail::json::read(obj, "externalCalculationId", out.external_calculation_id);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const ReferencePriceCalculationResponseResult& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "calculationType", v.calculation_type);
    common::detail::json::write(obj, "bucketCount", v.bucket_count);
    common::detail::json::write(obj, "bucketWidthMs", v.bucket_width_ms);
    common::detail::json::write(obj, "externalCalculationId", v.external_calculation_id);
}

} // namespace binance::spot::websocket_api
