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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/derivatives_trading_coin_futures/export.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_api/models/account_information_response_result_assets_inner.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_api/models/account_information_response_result_positions_inner.hpp>

namespace binance::derivatives_trading_coin_futures::websocket_api {

/// Indicates that combined is set to true.
struct AccountInformationResponseResult {
    /// Fee tier level.
    std::optional<std::int64_t> fee_tier;
    /// Whether trading is enabled.
    std::optional<bool> can_trade;
    /// Whether deposits are enabled.
    std::optional<bool> can_deposit;
    /// Whether withdrawals are enabled.
    std::optional<bool> can_withdraw;
    /// update time
    std::optional<std::int64_t> update_time;
    /// Supported assets.
    std::optional<std::vector<AccountInformationResponseResultAssetsInner>> assets;
    /// Position list.
    std::optional<std::vector<AccountInformationResponseResultPositionsInner>> positions;

    bool operator==(const AccountInformationResponseResult& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT AccountInformationResponseResult
tag_invoke(boost::json::value_to_tag<AccountInformationResponseResult> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const AccountInformationResponseResult& v);

} // namespace binance::derivatives_trading_coin_futures::websocket_api
