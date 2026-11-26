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

#include <binance/derivatives_trading_options/export.hpp>

namespace binance::derivatives_trading_options::websocket_streams {

struct NewSymbolInfoResponse {
    /// Event Type
    std::optional<std::string> e;
    /// Event Time
    std::optional<std::int64_t> e_uppercase;
    /// Symbol
    std::optional<std::string> s;
    /// Underlying index of the contract
    std::optional<std::string> ps;
    /// Quotation asset
    std::optional<std::string> qa;
    /// Option type
    std::optional<std::string> d;
    /// Strike price
    std::optional<std::string> sp;
    /// Delivery date time
    std::optional<std::int64_t> dt;
    /// unit, the quantity of the underlying asset represented by a single contract.
    std::optional<std::int64_t> u;
    /// onboard date time
    std::optional<std::int64_t> ot;
    /// Contract status
    std::optional<std::string> cs;

    bool operator==(const NewSymbolInfoResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT NewSymbolInfoResponse
tag_invoke(boost::json::value_to_tag<NewSymbolInfoResponse> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                           boost::json::value& jv,
                                                           const NewSymbolInfoResponse& v);

} // namespace binance::derivatives_trading_options::websocket_streams
