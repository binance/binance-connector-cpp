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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/derivatives_trading_usds_futures/export.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

struct RpiOrderBookResponse {
    std::optional<std::int64_t> last_update_id;
    /// Message output time
    std::optional<std::int64_t> e_uppercase;
    /// Transaction time
    std::optional<std::int64_t> t_uppercase;
    /// Bid orders. Each entry is [price, quantity].
    std::optional<std::vector<std::vector<std::string>>> bids;
    /// Ask orders. Each entry is [price, quantity].
    std::optional<std::vector<std::vector<std::string>>> asks;

    bool operator==(const RpiOrderBookResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT RpiOrderBookResponse
tag_invoke(boost::json::value_to_tag<RpiOrderBookResponse> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                                boost::json::value& jv,
                                                                const RpiOrderBookResponse& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
