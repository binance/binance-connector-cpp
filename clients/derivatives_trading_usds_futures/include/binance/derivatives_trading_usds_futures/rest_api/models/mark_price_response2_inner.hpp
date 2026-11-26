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

struct MarkPriceResponse2Inner {
    /// Symbol.
    std::optional<std::string> symbol;
    /// mark price
    std::optional<std::string> mark_price;
    /// index price
    std::optional<std::string> index_price;
    /// Estimated Settle Price, only useful in the last hour before the settlement starts.
    std::optional<std::string> estimated_settle_price;
    /// This is the Latest funding rate
    std::optional<std::string> last_funding_rate;
    /// Interest Rate.
    std::optional<std::string> interest_rate;
    /// Next Funding Time.
    std::optional<std::int64_t> next_funding_time;
    /// Time.
    std::optional<std::int64_t> time;

    bool operator==(const MarkPriceResponse2Inner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT MarkPriceResponse2Inner tag_invoke(
    boost::json::value_to_tag<MarkPriceResponse2Inner> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                                boost::json::value& jv,
                                                                const MarkPriceResponse2Inner& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
