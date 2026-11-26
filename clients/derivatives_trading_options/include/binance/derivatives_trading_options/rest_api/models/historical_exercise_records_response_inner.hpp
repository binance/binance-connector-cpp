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

#include <binance/derivatives_trading_options/export.hpp>

namespace binance::derivatives_trading_options::rest_api {

struct HistoricalExerciseRecordsResponseInner {
    /// symbol
    std::optional<std::string> symbol;
    /// strike price
    std::optional<std::string> strike_price;
    /// real strike price
    std::optional<std::string> real_strike_price;
    /// Exercise time
    std::optional<std::int64_t> expiry_date;
    /// strike result
    std::optional<std::string> strike_result;

    bool operator==(const HistoricalExerciseRecordsResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT HistoricalExerciseRecordsResponseInner
tag_invoke(boost::json::value_to_tag<HistoricalExerciseRecordsResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const HistoricalExerciseRecordsResponseInner& v);

} // namespace binance::derivatives_trading_options::rest_api
