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

struct AcquiringCoinnameResponseDataInner {
    /// Currency name
    std::optional<std::string> coin_name;
    /// ID
    std::optional<std::int64_t> coin_id;
    /// Sort
    std::optional<std::int64_t> pool_index;
    /// Algorithm
    std::optional<std::int64_t> algo_id;
    /// Name of algorithm
    std::optional<std::string> algo_name;

    bool operator==(const AcquiringCoinnameResponseDataInner& /*other*/) const = default;
};

BINANCE_MINING_EXPORT AcquiringCoinnameResponseDataInner
tag_invoke(boost::json::value_to_tag<AcquiringCoinnameResponseDataInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_MINING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const AcquiringCoinnameResponseDataInner& v);

} // namespace binance::mining::rest_api
