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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/alpha/export.hpp>
#include <binance/alpha/rest_api/models/aggregated_trades_response_data_inner.hpp>

namespace binance::alpha::rest_api {

struct AggregatedTradesResponse {
    /// API response code. "000000" indicates success.
    std::optional<std::string> code;
    /// Response message.
    std::optional<std::string> message;
    /// Detailed response message.
    std::optional<std::string> message_detail;
    /// Array of aggregated trades.
    std::optional<std::vector<AggregatedTradesResponseDataInner>> data;

    bool operator==(const AggregatedTradesResponse& /*other*/) const = default;
};

BINANCE_ALPHA_EXPORT AggregatedTradesResponse tag_invoke(
    boost::json::value_to_tag<AggregatedTradesResponse> /*tag*/, const boost::json::value& jv);
BINANCE_ALPHA_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                     const AggregatedTradesResponse& v);

} // namespace binance::alpha::rest_api
