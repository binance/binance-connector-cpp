//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <cstdint>
#include <optional>
#include <string>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/spot/export.hpp>

namespace binance::spot::rest_api {

struct ReferencePriceCalculationResponse {
    std::optional<std::string> symbol;
    /// Either `ARITHMETIC_MEAN` or `EXTERNAL`.
    std::optional<std::string> calculation_type;
    /// Present when calculationType is ARITHMETIC_MEAN.
    std::optional<std::int64_t> bucket_count;
    /// Present when calculationType is ARITHMETIC_MEAN.
    std::optional<std::int64_t> bucket_width_ms;
    /// Present when calculationType is EXTERNAL.
    std::optional<std::int64_t> external_calculation_id;

    bool operator==(const ReferencePriceCalculationResponse& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT ReferencePriceCalculationResponse
tag_invoke(boost::json::value_to_tag<ReferencePriceCalculationResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const ReferencePriceCalculationResponse& v);

} // namespace binance::spot::rest_api
