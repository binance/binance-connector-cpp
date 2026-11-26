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

#include <binance/stocks/export.hpp>

namespace binance::stocks::rest_api {

struct EquityOrderDetailResponseTradesInner {
    /// Execution (fill) id.
    std::optional<std::string> execution_id;
    /// Execution time (ms epoch).
    std::optional<std::int64_t> execution_at;
    /// Fill price for this execution (USD).
    std::optional<std::string> price;
    /// Fill quantity.
    std::optional<std::string> qty;

    bool operator==(const EquityOrderDetailResponseTradesInner& /*other*/) const = default;
};

BINANCE_STOCKS_EXPORT EquityOrderDetailResponseTradesInner
tag_invoke(boost::json::value_to_tag<EquityOrderDetailResponseTradesInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_STOCKS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const EquityOrderDetailResponseTradesInner& v);

} // namespace binance::stocks::rest_api
