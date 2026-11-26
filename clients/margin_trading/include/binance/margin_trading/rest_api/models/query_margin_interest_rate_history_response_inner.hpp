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

struct QueryMarginInterestRateHistoryResponseInner {
    /// asset.
    std::optional<std::string> asset;
    /// daily Interest Rate.
    std::optional<std::string> daily_interest_rate;
    /// timestamp.
    std::optional<std::int64_t> timestamp;
    /// vip Level.
    std::optional<std::int64_t> vip_level;

    bool operator==(const QueryMarginInterestRateHistoryResponseInner& /*other*/) const = default;
};

BINANCE_MARGIN_TRADING_EXPORT QueryMarginInterestRateHistoryResponseInner
tag_invoke(boost::json::value_to_tag<QueryMarginInterestRateHistoryResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const QueryMarginInterestRateHistoryResponseInner& v);

} // namespace binance::margin_trading::rest_api
