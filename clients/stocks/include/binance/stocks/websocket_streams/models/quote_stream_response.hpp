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

#include <binance/stocks/export.hpp>

namespace binance::stocks::websocket_streams {

struct QuoteStreamResponse {
    /// Event type, always `"quote"`.
    std::optional<std::string> e;
    /// Event time — epoch milliseconds when the server pushed the message.
    std::optional<std::int64_t> e_uppercase;
    /// Symbol (UPPERCASE ticker), e.g. `"AAPL"`.
    std::optional<std::string> s;
    /// Best bid price.
    std::optional<std::string> bp;
    /// Best ask price.
    std::optional<std::string> ap;
    /// Best bid size (shares).
    std::optional<std::int64_t> bs;
    /// Best ask size (shares).
    std::optional<std::int64_t> as;
    /// Source quote timestamp (epoch milliseconds); may be null.
    /// `std::nullopt` when the field is absent; holds `std::nullopt` when it is `null`.
    std::optional<std::optional<std::int64_t>> t_uppercase;

    bool operator==(const QuoteStreamResponse& /*other*/) const = default;
};

BINANCE_STOCKS_EXPORT QuoteStreamResponse
tag_invoke(boost::json::value_to_tag<QuoteStreamResponse> /*tag*/, const boost::json::value& jv);
BINANCE_STOCKS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const QuoteStreamResponse& v);

} // namespace binance::stocks::websocket_streams
