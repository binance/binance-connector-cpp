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
#include <binance/alpha/rest_api/models/klines_response_data_inner_inner.hpp>

namespace binance::alpha::rest_api {

struct KlinesResponse {
    /// API response code. "000000" indicates success.
    std::optional<std::string> code;
    /// Response message.
    std::optional<std::string> message;
    /// Detailed response message.
    std::optional<std::string> message_detail;
    /// Whether request is successful.
    std::optional<bool> success;
    /// Array of kline rows. Each row contains: open time, open, high, low, close, volume, close
    /// time, quote volume, trade count, taker buy base volume, taker buy quote volume, and a static
    /// 0.
    std::optional<std::vector<std::vector<KlinesResponseDataInnerInner>>> data;

    bool operator==(const KlinesResponse& /*other*/) const = default;
};

BINANCE_ALPHA_EXPORT KlinesResponse tag_invoke(boost::json::value_to_tag<KlinesResponse> /*tag*/,
                                               const boost::json::value& jv);
BINANCE_ALPHA_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                     const KlinesResponse& v);

} // namespace binance::alpha::rest_api
