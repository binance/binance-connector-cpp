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

#include <binance/derivatives_trading_coin_futures/export.hpp>

namespace binance::derivatives_trading_coin_futures::rest_api {

struct CheckServerTimeResponse {
    /// Ignore please. If you want to check current server time, please check via "GET
    /// /dapi/v1/time"
    std::optional<std::int64_t> server_time;

    bool operator==(const CheckServerTimeResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT CheckServerTimeResponse tag_invoke(
    boost::json::value_to_tag<CheckServerTimeResponse> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                                boost::json::value& jv,
                                                                const CheckServerTimeResponse& v);

} // namespace binance::derivatives_trading_coin_futures::rest_api
