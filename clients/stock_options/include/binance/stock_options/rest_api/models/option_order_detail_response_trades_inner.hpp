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

#include <binance/stock_options/export.hpp>

namespace binance::stock_options::rest_api {

struct OptionOrderDetailResponseTradesInner {
    /// Execution ID.
    std::optional<std::string> execution_id;
    /// Execution time (ms).
    std::optional<std::int64_t> execution_at;
    /// Fill price (premium per share).
    std::optional<std::string> price;
    /// Fill quantity (contracts).
    std::optional<std::string> qty;

    bool operator==(const OptionOrderDetailResponseTradesInner& /*other*/) const = default;
};

BINANCE_STOCK_OPTIONS_EXPORT OptionOrderDetailResponseTradesInner
tag_invoke(boost::json::value_to_tag<OptionOrderDetailResponseTradesInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_STOCK_OPTIONS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                             boost::json::value& jv,
                                             const OptionOrderDetailResponseTradesInner& v);

} // namespace binance::stock_options::rest_api
