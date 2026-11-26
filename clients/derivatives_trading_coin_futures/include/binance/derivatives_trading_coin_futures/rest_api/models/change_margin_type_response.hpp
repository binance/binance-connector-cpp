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

#include <binance/derivatives_trading_coin_futures/export.hpp>

namespace binance::derivatives_trading_coin_futures::rest_api {

struct ChangeMarginTypeResponse {
    /// API response code. "000000" indicates success.
    std::optional<std::int64_t> code;
    /// Message details.
    std::optional<std::string> msg;

    bool operator==(const ChangeMarginTypeResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT ChangeMarginTypeResponse tag_invoke(
    boost::json::value_to_tag<ChangeMarginTypeResponse> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                                boost::json::value& jv,
                                                                const ChangeMarginTypeResponse& v);

} // namespace binance::derivatives_trading_coin_futures::rest_api
