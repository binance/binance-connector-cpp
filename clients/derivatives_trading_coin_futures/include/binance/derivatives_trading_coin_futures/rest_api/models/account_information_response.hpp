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
#include <binance/derivatives_trading_coin_futures/rest_api/models/account_information_response_assets_inner.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/account_information_response_positions_inner.hpp>

namespace binance::derivatives_trading_coin_futures::rest_api {

struct AccountInformationResponse {
    /// Supported assets.
    std::optional<std::vector<AccountInformationResponseAssetsInner>> assets;
    /// Position list.
    std::optional<std::vector<AccountInformationResponsePositionsInner>> positions;
    /// Whether deposits are enabled.
    std::optional<bool> can_deposit;
    /// Whether trading is enabled.
    std::optional<bool> can_trade;
    /// Whether withdrawals are enabled.
    std::optional<bool> can_withdraw;
    /// Fee tier level.
    std::optional<std::int64_t> fee_tier;
    /// update time
    std::optional<std::int64_t> update_time;

    bool operator==(const AccountInformationResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT AccountInformationResponse tag_invoke(
    boost::json::value_to_tag<AccountInformationResponse> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const AccountInformationResponse& v);

} // namespace binance::derivatives_trading_coin_futures::rest_api
