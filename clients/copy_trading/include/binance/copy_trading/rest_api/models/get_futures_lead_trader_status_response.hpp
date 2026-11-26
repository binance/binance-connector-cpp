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

#include <binance/copy_trading/export.hpp>
#include <binance/copy_trading/rest_api/models/get_futures_lead_trader_status_response_data.hpp>

namespace binance::copy_trading::rest_api {

struct GetFuturesLeadTraderStatusResponse {
    /// API response code. "000000" indicates success.
    std::optional<std::string> code;
    /// Response message.
    std::optional<std::string> message;
    std::optional<GetFuturesLeadTraderStatusResponseData> data;
    /// Whether request is successful
    std::optional<bool> success;

    bool operator==(const GetFuturesLeadTraderStatusResponse& /*other*/) const = default;
};

BINANCE_COPY_TRADING_EXPORT GetFuturesLeadTraderStatusResponse
tag_invoke(boost::json::value_to_tag<GetFuturesLeadTraderStatusResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_COPY_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                            boost::json::value& jv,
                                            const GetFuturesLeadTraderStatusResponse& v);

} // namespace binance::copy_trading::rest_api
