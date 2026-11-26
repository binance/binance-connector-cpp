//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <optional>
#include <string>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/derivatives_trading_usds_futures/export.hpp>

namespace binance::derivatives_trading_usds_futures::websocket_streams {

struct CompositeIndexSymbolInformationStreamsResponseCInner {
    /// Base asset
    std::optional<std::string> b;
    /// Quote asset
    std::optional<std::string> q;
    /// Weight in quantity
    std::optional<std::string> w;
    /// Weight in percentage
    std::optional<std::string> w_uppercase;
    /// Index price
    std::optional<std::string> i;

    bool operator==(const CompositeIndexSymbolInformationStreamsResponseCInner& /*other*/) const =
        default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT CompositeIndexSymbolInformationStreamsResponseCInner
tag_invoke(boost::json::value_to_tag<CompositeIndexSymbolInformationStreamsResponseCInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const CompositeIndexSymbolInformationStreamsResponseCInner& v);

} // namespace binance::derivatives_trading_usds_futures::websocket_streams
