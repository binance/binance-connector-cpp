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

#include <binance/mining/export.hpp>

namespace binance::mining::rest_api {

struct AcquiringAlgorithmResponseDataInner {
    /// Algorithm name
    std::optional<std::string> algo_name;
    /// Algorithm ID
    std::optional<std::int64_t> algo_id;
    /// Sequence
    std::optional<std::int64_t> pool_index;
    /// Unit
    std::optional<std::string> unit;

    bool operator==(const AcquiringAlgorithmResponseDataInner& /*other*/) const = default;
};

BINANCE_MINING_EXPORT AcquiringAlgorithmResponseDataInner
tag_invoke(boost::json::value_to_tag<AcquiringAlgorithmResponseDataInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_MINING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const AcquiringAlgorithmResponseDataInner& v);

} // namespace binance::mining::rest_api
