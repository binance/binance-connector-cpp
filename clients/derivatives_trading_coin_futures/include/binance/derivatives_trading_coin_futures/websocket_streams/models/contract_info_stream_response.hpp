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

#include <binance/derivatives_trading_coin_futures/export.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_streams/models/contract_info_stream_response_bks_inner.hpp>

namespace binance::derivatives_trading_coin_futures::websocket_streams {

struct ContractInfoStreamResponse {
    /// Event Type
    std::optional<std::string> e;
    /// Event Time
    std::optional<std::int64_t> e_uppercase;
    /// Symbol
    std::optional<std::string> s;
    /// Pair
    std::optional<std::string> ps;
    /// Contract type
    std::optional<std::string> ct;
    /// Delivery date time
    std::optional<std::int64_t> dt;
    /// onboard date time
    std::optional<std::int64_t> ot;
    /// Contract status
    std::optional<std::string> cs;
    /// Bracket list.
    std::optional<std::vector<ContractInfoStreamResponseBksInner>> bks;
    /// (After CM migration) Symbol type: 1 = UM, 2 = CM
    std::optional<std::int64_t> st;

    bool operator==(const ContractInfoStreamResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT ContractInfoStreamResponse tag_invoke(
    boost::json::value_to_tag<ContractInfoStreamResponse> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const ContractInfoStreamResponse& v);

} // namespace binance::derivatives_trading_coin_futures::websocket_streams
