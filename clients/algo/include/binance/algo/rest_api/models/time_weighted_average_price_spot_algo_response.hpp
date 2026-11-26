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

#include <binance/algo/export.hpp>

namespace binance::algo::rest_api {

struct TimeWeightedAveragePriceSpotAlgoResponse {
    std::optional<std::string> client_algo_id;
    std::optional<bool> success;
    std::optional<std::int64_t> code;
    std::optional<std::string> msg;

    bool operator==(const TimeWeightedAveragePriceSpotAlgoResponse& /*other*/) const = default;
};

BINANCE_ALGO_EXPORT TimeWeightedAveragePriceSpotAlgoResponse
tag_invoke(boost::json::value_to_tag<TimeWeightedAveragePriceSpotAlgoResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_ALGO_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const TimeWeightedAveragePriceSpotAlgoResponse& v);

} // namespace binance::algo::rest_api
