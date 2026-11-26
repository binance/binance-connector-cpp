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

#include <binance/derivatives_trading_usds_futures/export.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

struct CompressedAggregateTradesListResponseInner {
    /// Aggregate tradeId
    std::optional<std::int64_t> a;
    /// Price
    std::optional<std::string> p;
    /// Quantity
    std::optional<std::string> q;
    /// Normal quantity without the trades involving RPI orders
    std::optional<std::string> nq;
    /// First tradeId
    std::optional<std::int64_t> f;
    /// Last tradeId
    std::optional<std::int64_t> l;
    /// Timestamp
    std::optional<std::int64_t> t_uppercase;
    /// Was the buyer the maker?
    std::optional<bool> m;

    bool operator==(const CompressedAggregateTradesListResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT CompressedAggregateTradesListResponseInner
tag_invoke(boost::json::value_to_tag<CompressedAggregateTradesListResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const CompressedAggregateTradesListResponseInner& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
