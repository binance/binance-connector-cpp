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

struct AggTradesResponseInner {
    /// Aggregate tradeId
    std::optional<std::int64_t> a;
    /// Price
    std::optional<std::string> p;
    /// Quantity
    std::optional<std::string> q;
    /// First tradeId
    std::optional<std::int64_t> f;
    /// Last tradeId
    std::optional<std::int64_t> l;
    /// Timestamp
    std::optional<std::int64_t> t_uppercase;
    /// Was the buyer the maker?
    std::optional<bool> m;
    /// Was the trade the best price match?
    std::optional<bool> m_uppercase;

    bool operator==(const AggTradesResponseInner& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT AggTradesResponseInner
tag_invoke(boost::json::value_to_tag<AggTradesResponseInner> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const AggTradesResponseInner& v);

} // namespace binance::spot::rest_api
