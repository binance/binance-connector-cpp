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

#include <binance/alpha/export.hpp>
#include <binance/alpha/websocket_streams/models/contract_kline_stream_response_k.hpp>

namespace binance::alpha::websocket_streams {

struct ContractKlineStreamResponse {
    /// Contract address@Chain ID
    std::optional<std::string> ca;
    /// Event type
    std::optional<std::string> e;
    std::optional<ContractKlineStreamResponseK> k;

    bool operator==(const ContractKlineStreamResponse& /*other*/) const = default;
};

BINANCE_ALPHA_EXPORT ContractKlineStreamResponse tag_invoke(
    boost::json::value_to_tag<ContractKlineStreamResponse> /*tag*/, const boost::json::value& jv);
BINANCE_ALPHA_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                     const ContractKlineStreamResponse& v);

} // namespace binance::alpha::websocket_streams
