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

struct TakerBuySellVolumeResponseInner {
    /// Pair
    std::optional<std::string> pair;
    /// Contract type.
    std::optional<std::string> contract_type;
    /// unit: cont
    std::optional<std::string> taker_buy_vol;
    /// unit: cont
    std::optional<std::string> taker_sell_vol;
    /// unit: base asset
    std::optional<std::string> taker_buy_vol_value;
    /// unit: base asset
    std::optional<std::string> taker_sell_vol_value;
    /// Start time of the period, in milliseconds.
    std::optional<std::int64_t> timestamp;

    bool operator==(const TakerBuySellVolumeResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT TakerBuySellVolumeResponseInner
tag_invoke(boost::json::value_to_tag<TakerBuySellVolumeResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const TakerBuySellVolumeResponseInner& v);

} // namespace binance::derivatives_trading_coin_futures::rest_api
