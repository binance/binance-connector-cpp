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

#include <binance/alpha/export.hpp>

namespace binance::alpha::websocket_streams {

struct KlineStreamResponseK {
    /// startTime
    std::optional<std::int64_t> t;
    /// endTime
    std::optional<std::int64_t> t_uppercase;
    /// symbol
    std::optional<std::string> s;
    /// interval
    std::optional<std::string> i;
    /// firstTradeId
    std::optional<std::int64_t> f;
    /// lastTradeId
    std::optional<std::int64_t> l_uppercase;
    /// openPrice
    std::optional<std::string> o;
    /// closePrice
    std::optional<std::string> c;
    /// highPrice
    std::optional<std::string> h;
    /// lowPrice
    std::optional<std::string> l;
    /// volume
    std::optional<std::string> v;
    /// tradeNum
    std::optional<std::int64_t> n;
    /// klineComplete
    std::optional<bool> x;
    /// quoteAssetVolume
    std::optional<std::string> q;
    /// takerBuyBaseAssetVolume
    std::optional<std::string> v_uppercase;
    /// takerBuyQuoteAssetVolume
    std::optional<std::string> q_uppercase;
    /// ignore
    std::optional<std::string> b_uppercase;

    bool operator==(const KlineStreamResponseK& /*other*/) const = default;
};

BINANCE_ALPHA_EXPORT KlineStreamResponseK
tag_invoke(boost::json::value_to_tag<KlineStreamResponseK> /*tag*/, const boost::json::value& jv);
BINANCE_ALPHA_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                     const KlineStreamResponseK& v);

} // namespace binance::alpha::websocket_streams
