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

#include <binance/margin_trading/export.hpp>

namespace binance::margin_trading::rest_api {

struct QueryCurrentMarginOrderCountUsageResponseInner {
    /// rate Limit Type.
    std::optional<std::string> rate_limit_type;
    /// interval.
    std::optional<std::string> interval;
    /// interval Num.
    std::optional<std::int64_t> interval_num;
    /// limit.
    std::optional<std::int64_t> limit;
    /// count.
    std::optional<std::int64_t> count;

    bool
    operator==(const QueryCurrentMarginOrderCountUsageResponseInner& /*other*/) const = default;
};

BINANCE_MARGIN_TRADING_EXPORT QueryCurrentMarginOrderCountUsageResponseInner
tag_invoke(boost::json::value_to_tag<QueryCurrentMarginOrderCountUsageResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const QueryCurrentMarginOrderCountUsageResponseInner& v);

} // namespace binance::margin_trading::rest_api
