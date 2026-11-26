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

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/copy_trading/export.hpp>

namespace binance::copy_trading::rest_api {

struct GetFuturesLeadTraderStatusResponseData {
    /// Whether the user is a futures lead trader
    std::optional<bool> is_lead_trader;
    /// Server timestamp in milliseconds
    std::optional<std::int64_t> time;

    bool operator==(const GetFuturesLeadTraderStatusResponseData& /*other*/) const = default;
};

BINANCE_COPY_TRADING_EXPORT GetFuturesLeadTraderStatusResponseData
tag_invoke(boost::json::value_to_tag<GetFuturesLeadTraderStatusResponseData> /*tag*/,
           const boost::json::value& jv);
BINANCE_COPY_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                            boost::json::value& jv,
                                            const GetFuturesLeadTraderStatusResponseData& v);

} // namespace binance::copy_trading::rest_api
