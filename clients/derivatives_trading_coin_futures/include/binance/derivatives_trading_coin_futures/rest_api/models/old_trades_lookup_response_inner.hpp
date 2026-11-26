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

#include <binance/derivatives_trading_coin_futures/export.hpp>

namespace binance::derivatives_trading_coin_futures::rest_api {

struct OldTradesLookupResponseInner {
    /// positionId
    std::optional<std::int64_t> id;
    /// Latest token price.
    std::optional<std::string> price;
    /// Quantity.
    std::optional<std::string> qty;
    /// Base asset quantity.
    std::optional<std::string> base_qty;
    /// Time
    std::optional<std::int64_t> time;
    /// Whether buyer is market maker.
    std::optional<bool> is_buyer_maker;

    bool operator==(const OldTradesLookupResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT OldTradesLookupResponseInner tag_invoke(
    boost::json::value_to_tag<OldTradesLookupResponseInner> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const OldTradesLookupResponseInner& v);

} // namespace binance::derivatives_trading_coin_futures::rest_api
