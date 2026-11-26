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

struct QueryMarginPriceindexResponse {
    /// calc Time.
    std::optional<std::int64_t> calc_time;
    /// price.
    std::optional<std::string> price;
    /// symbol.
    std::optional<std::string> symbol;

    bool operator==(const QueryMarginPriceindexResponse& /*other*/) const = default;
};

BINANCE_MARGIN_TRADING_EXPORT QueryMarginPriceindexResponse tag_invoke(
    boost::json::value_to_tag<QueryMarginPriceindexResponse> /*tag*/, const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const QueryMarginPriceindexResponse& v);

} // namespace binance::margin_trading::rest_api
