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

struct RecentTradesListResponseInner {
    /// Id.
    std::optional<std::int64_t> id;
    /// Price.
    std::optional<std::string> price;
    /// Qty.
    std::optional<std::string> qty;
    /// Quote Qty.
    std::optional<std::string> quote_qty;
    /// Time.
    std::optional<std::int64_t> time;
    /// Is Buyer Maker.
    std::optional<bool> is_buyer_maker;
    /// Is RPITrade.
    std::optional<bool> is_rpi_trade;

    bool operator==(const RecentTradesListResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT RecentTradesListResponseInner tag_invoke(
    boost::json::value_to_tag<RecentTradesListResponseInner> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const RecentTradesListResponseInner& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
