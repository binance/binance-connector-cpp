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
#include <binance/alpha/rest_api/models/token_list_response_data_inner.hpp>

namespace binance::alpha::rest_api {

struct TokenListResponse {
    /// API response code. "000000" indicates success.
    std::optional<std::string> code;
    /// Response message.
    std::optional<std::string> message;
    /// Detailed response message.
    std::optional<std::string> message_detail;
    /// Whether request is successful.
    std::optional<bool> success;
    /// List of ALPHA tokens and metadata.
    std::optional<std::vector<TokenListResponseDataInner>> data;

    bool operator==(const TokenListResponse& /*other*/) const = default;
};

BINANCE_ALPHA_EXPORT TokenListResponse
tag_invoke(boost::json::value_to_tag<TokenListResponse> /*tag*/, const boost::json::value& jv);
BINANCE_ALPHA_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                     const TokenListResponse& v);

} // namespace binance::alpha::rest_api
