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

#include <binance/derivatives_trading_usds_futures/export.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

struct FuturesAccountConfigurationResponse {
    /// account commission tier
    std::optional<std::int64_t> fee_tier;
    /// if can trade
    std::optional<bool> can_trade;
    /// if can transfer in asset
    std::optional<bool> can_deposit;
    /// if can transfer out asset
    std::optional<bool> can_withdraw;
    std::optional<bool> dual_side_position;
    /// reserved property, please ignore
    std::optional<std::int64_t> update_time;
    std::optional<bool> multi_assets_margin;
    std::optional<std::int64_t> trade_group_id;

    bool operator==(const FuturesAccountConfigurationResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT FuturesAccountConfigurationResponse
tag_invoke(boost::json::value_to_tag<FuturesAccountConfigurationResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const FuturesAccountConfigurationResponse& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
