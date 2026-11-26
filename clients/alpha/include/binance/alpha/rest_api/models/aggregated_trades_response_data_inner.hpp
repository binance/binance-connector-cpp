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

#include <binance/alpha/export.hpp>

namespace binance::alpha::rest_api {

struct AggregatedTradesResponseDataInner {
    /// Aggregate trade ID.
    std::optional<std::int64_t> a;
    /// Trade price.
    std::optional<std::string> p;
    /// Trade quantity.
    std::optional<std::string> q;
    /// First trade ID in the aggregation.
    std::optional<std::int64_t> f;
    /// Last trade ID in the aggregation.
    std::optional<std::int64_t> l;
    /// Trade timestamp in milliseconds.
    std::optional<std::int64_t> t_uppercase;
    /// Whether buyer is the market maker (deprecated).
    std::optional<bool> m;

    bool operator==(const AggregatedTradesResponseDataInner& /*other*/) const = default;
};

BINANCE_ALPHA_EXPORT AggregatedTradesResponseDataInner
tag_invoke(boost::json::value_to_tag<AggregatedTradesResponseDataInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_ALPHA_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                     const AggregatedTradesResponseDataInner& v);

} // namespace binance::alpha::rest_api
