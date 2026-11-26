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

#include <binance/convert/export.hpp>

namespace binance::convert::rest_api {

struct QueryLimitOpenOrdersResponseListInner {
    std::optional<std::string> quote_id;
    std::optional<std::int64_t> order_id;
    std::optional<std::string> order_status;
    std::optional<std::string> from_asset;
    std::optional<std::string> from_amount;
    std::optional<std::string> to_asset;
    std::optional<std::string> to_amount;
    std::optional<std::string> ratio;
    std::optional<std::string> inverse_ratio;
    std::optional<std::int64_t> create_time;
    std::optional<std::int64_t> expired_timestamp;

    bool operator==(const QueryLimitOpenOrdersResponseListInner& /*other*/) const = default;
};

BINANCE_CONVERT_EXPORT QueryLimitOpenOrdersResponseListInner
tag_invoke(boost::json::value_to_tag<QueryLimitOpenOrdersResponseListInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_CONVERT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                       const QueryLimitOpenOrdersResponseListInner& v);

} // namespace binance::convert::rest_api
