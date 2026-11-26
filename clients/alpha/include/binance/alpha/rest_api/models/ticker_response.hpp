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
#include <binance/alpha/rest_api/models/ticker_response_data.hpp>

namespace binance::alpha::rest_api {

struct TickerResponse {
    /// API response code. "000000" indicates success.
    std::optional<std::string> code;
    /// Response message.
    std::optional<std::string> message;
    /// Detailed response message.
    std::optional<std::string> message_detail;
    std::optional<TickerResponseData> data;
    /// Whether request is successful.
    std::optional<bool> success;

    bool operator==(const TickerResponse& /*other*/) const = default;
};

BINANCE_ALPHA_EXPORT TickerResponse tag_invoke(boost::json::value_to_tag<TickerResponse> /*tag*/,
                                               const boost::json::value& jv);
BINANCE_ALPHA_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                     const TickerResponse& v);

} // namespace binance::alpha::rest_api
