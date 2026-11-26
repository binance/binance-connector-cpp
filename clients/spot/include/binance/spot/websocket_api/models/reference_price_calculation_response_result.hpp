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

namespace binance::spot::websocket_api {

struct ReferencePriceCalculationResponseResult {
    std::optional<std::string> symbol;
    std::optional<std::string> calculation_type;
    /// If the reference price is being calculated by the matching engine as an arithmetic mean
    std::optional<std::int64_t> bucket_count;
    /// If the reference price is being calculated by the matching engine as an arithmetic mean
    std::optional<std::int64_t> bucket_width_ms;
    /// If the reference price is being calculated outside the matching engine
    std::optional<std::int64_t> external_calculation_id;

    bool operator==(const ReferencePriceCalculationResponseResult& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT ReferencePriceCalculationResponseResult
tag_invoke(boost::json::value_to_tag<ReferencePriceCalculationResponseResult> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const ReferencePriceCalculationResponseResult& v);

} // namespace binance::spot::websocket_api
