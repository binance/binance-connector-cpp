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

#include <binance/common/decimal.hpp>
#include <binance/derivatives_trading_coin_futures/export.hpp>

namespace binance::derivatives_trading_coin_futures::rest_api {

struct ModifyIsolatedPositionMarginResponse {
    /// Amount.
    std::optional<common::Decimal> amount;
    /// API response code. "000000" indicates success.
    std::optional<std::int64_t> code;
    /// Message details.
    std::optional<std::string> msg;
    /// Order type.
    std::optional<std::int64_t> type;

    bool operator==(const ModifyIsolatedPositionMarginResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT ModifyIsolatedPositionMarginResponse
tag_invoke(boost::json::value_to_tag<ModifyIsolatedPositionMarginResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const ModifyIsolatedPositionMarginResponse& v);

} // namespace binance::derivatives_trading_coin_futures::rest_api
