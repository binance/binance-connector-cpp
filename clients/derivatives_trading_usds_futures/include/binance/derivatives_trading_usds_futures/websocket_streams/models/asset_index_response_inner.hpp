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

struct AssetIndexResponseInner {
    /// Event type.
    std::optional<std::string> e;
    /// Event time.
    std::optional<std::int64_t> e_uppercase;
    /// Asset index symbol.
    std::optional<std::string> s;
    /// Index price.
    std::optional<std::string> i;
    /// Bid buffer.
    std::optional<std::string> b;
    /// Ask buffer.
    std::optional<std::string> a;
    /// Bid rate.
    std::optional<std::string> b_uppercase;
    /// Ask rate.
    std::optional<std::string> a_uppercase;
    /// Auto exchange bid buffer.
    std::optional<std::string> q;
    /// Auto exchange ask buffer.
    std::optional<std::string> g;
    /// Auto exchange bid rate.
    std::optional<std::string> q_uppercase;
    /// Auto exchange ask rate.
    std::optional<std::string> g_uppercase;

    bool operator==(const AssetIndexResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT AssetIndexResponseInner tag_invoke(
    boost::json::value_to_tag<AssetIndexResponseInner> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                                boost::json::value& jv,
                                                                const AssetIndexResponseInner& v);

} // namespace binance::derivatives_trading_usds_futures::websocket_streams
