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

struct CancelAlgoOrderSpotAlgoResponse {
    std::optional<std::int64_t> algo_id;
    std::optional<bool> success;
    std::optional<std::int64_t> code;
    std::optional<std::string> msg;

    bool operator==(const CancelAlgoOrderSpotAlgoResponse& /*other*/) const = default;
};

BINANCE_ALGO_EXPORT CancelAlgoOrderSpotAlgoResponse
tag_invoke(boost::json::value_to_tag<CancelAlgoOrderSpotAlgoResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_ALGO_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const CancelAlgoOrderSpotAlgoResponse& v);

} // namespace binance::algo::rest_api
