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

#include <binance/derivatives_trading_usds_futures/export.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

struct AcceptTheOfferedQuoteResponse {
    std::optional<std::string> order_id;
    std::optional<std::int64_t> create_time;
    /// PROCESS/ACCEPT_SUCCESS/SUCCESS/FAIL
    std::optional<std::string> order_status;

    bool operator==(const AcceptTheOfferedQuoteResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT AcceptTheOfferedQuoteResponse tag_invoke(
    boost::json::value_to_tag<AcceptTheOfferedQuoteResponse> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const AcceptTheOfferedQuoteResponse& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
