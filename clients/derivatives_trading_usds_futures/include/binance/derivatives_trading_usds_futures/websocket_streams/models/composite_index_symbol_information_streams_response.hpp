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
#include <binance/derivatives_trading_usds_futures/websocket_streams/models/composite_index_symbol_information_streams_response_c_inner.hpp>

namespace binance::derivatives_trading_usds_futures::websocket_streams {

struct CompositeIndexSymbolInformationStreamsResponse {
    /// Event type
    std::optional<std::string> e;
    /// Event time
    std::optional<std::int64_t> e_uppercase;
    /// Symbol
    std::optional<std::string> s;
    /// Price
    std::optional<std::string> p;
    /// Base asset category.
    std::optional<std::string> c_uppercase;
    /// Composition
    std::optional<std::vector<CompositeIndexSymbolInformationStreamsResponseCInner>> c;

    bool
    operator==(const CompositeIndexSymbolInformationStreamsResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT CompositeIndexSymbolInformationStreamsResponse
tag_invoke(boost::json::value_to_tag<CompositeIndexSymbolInformationStreamsResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const CompositeIndexSymbolInformationStreamsResponse& v);

} // namespace binance::derivatives_trading_usds_futures::websocket_streams
