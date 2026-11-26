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

struct GetConvertTradeHistoryResponseListInner {
    std::optional<std::string> quote_id;
    std::optional<std::int64_t> order_id;
    /// Order status
    std::optional<std::string> order_status;
    /// Source asset
    std::optional<std::string> from_asset;
    /// Source amount
    std::optional<std::string> from_amount;
    /// Destination asset
    std::optional<std::string> to_asset;
    /// Destination amount
    std::optional<std::string> to_amount;
    /// Price ratio
    std::optional<std::string> ratio;
    /// Inverse price ratio
    std::optional<std::string> inverse_ratio;
    std::optional<std::int64_t> create_time;

    bool operator==(const GetConvertTradeHistoryResponseListInner& /*other*/) const = default;
};

BINANCE_CONVERT_EXPORT GetConvertTradeHistoryResponseListInner
tag_invoke(boost::json::value_to_tag<GetConvertTradeHistoryResponseListInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_CONVERT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                       const GetConvertTradeHistoryResponseListInner& v);

} // namespace binance::convert::rest_api
