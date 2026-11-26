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

struct LatestQuoteResponse {
    /// US-equity ticker.
    std::optional<std::string> symbol;
    /// Best bid price (USD).
    std::optional<std::string> bid_price;
    /// Best ask price (USD).
    std::optional<std::string> ask_price;
    /// Best bid size (shares).
    std::optional<std::int64_t> bid_size;
    /// Best ask size (shares).
    std::optional<std::int64_t> ask_size;

    bool operator==(const LatestQuoteResponse& /*other*/) const = default;
};

BINANCE_STOCKS_EXPORT LatestQuoteResponse
tag_invoke(boost::json::value_to_tag<LatestQuoteResponse> /*tag*/, const boost::json::value& jv);
BINANCE_STOCKS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const LatestQuoteResponse& v);

} // namespace binance::stocks::rest_api
