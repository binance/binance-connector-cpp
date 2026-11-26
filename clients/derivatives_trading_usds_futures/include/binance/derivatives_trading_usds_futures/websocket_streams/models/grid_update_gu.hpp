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

namespace binance::derivatives_trading_usds_futures::websocket_streams {

struct GridUpdateGu {
    /// Strategy ID
    std::optional<std::int64_t> si;
    /// Strategy Type
    std::optional<std::string> st;
    /// Strategy Status
    std::optional<std::string> ss;
    /// Symbol
    std::optional<std::string> s;
    /// Realized PNL
    std::optional<std::string> r;
    /// Unmatched Average Price
    std::optional<std::string> up;
    /// Unmatched Qty
    std::optional<std::string> uq;
    /// Unmatched Fee
    std::optional<std::string> uf;
    /// Matched PNL
    std::optional<std::string> mp;
    /// Update Time
    std::optional<std::int64_t> ut;

    bool operator==(const GridUpdateGu& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT GridUpdateGu
tag_invoke(boost::json::value_to_tag<GridUpdateGu> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv, const GridUpdateGu& v);

} // namespace binance::derivatives_trading_usds_futures::websocket_streams
