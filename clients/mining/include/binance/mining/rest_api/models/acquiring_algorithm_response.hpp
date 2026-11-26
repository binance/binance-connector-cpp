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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/mining/export.hpp>
#include <binance/mining/rest_api/models/acquiring_algorithm_response_data_inner.hpp>

namespace binance::mining::rest_api {

struct AcquiringAlgorithmResponse {
    std::optional<std::int64_t> code;
    std::optional<std::string> msg;
    std::optional<std::vector<AcquiringAlgorithmResponseDataInner>> data;

    bool operator==(const AcquiringAlgorithmResponse& /*other*/) const = default;
};

BINANCE_MINING_EXPORT AcquiringAlgorithmResponse tag_invoke(
    boost::json::value_to_tag<AcquiringAlgorithmResponse> /*tag*/, const boost::json::value& jv);
BINANCE_MINING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const AcquiringAlgorithmResponse& v);

} // namespace binance::mining::rest_api
