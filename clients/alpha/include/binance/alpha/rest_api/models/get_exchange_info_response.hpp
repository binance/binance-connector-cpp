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
#include <binance/alpha/rest_api/models/get_exchange_info_response_data.hpp>

namespace binance::alpha::rest_api {

struct GetExchangeInfoResponse {
    /// API response code. "000000" indicates success.
    std::optional<std::string> code;
    /// Response message.
    std::optional<std::string> message;
    /// Detailed response message.
    std::optional<std::string> message_detail;
    /// Whether request is successful.
    std::optional<bool> success;
    std::optional<GetExchangeInfoResponseData> data;

    bool operator==(const GetExchangeInfoResponse& /*other*/) const = default;
};

BINANCE_ALPHA_EXPORT GetExchangeInfoResponse tag_invoke(
    boost::json::value_to_tag<GetExchangeInfoResponse> /*tag*/, const boost::json::value& jv);
BINANCE_ALPHA_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                     const GetExchangeInfoResponse& v);

} // namespace binance::alpha::rest_api
