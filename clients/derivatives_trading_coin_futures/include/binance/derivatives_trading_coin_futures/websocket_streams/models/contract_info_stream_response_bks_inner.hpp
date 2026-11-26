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

#include <binance/common/decimal.hpp>
#include <binance/derivatives_trading_coin_futures/export.hpp>

namespace binance::derivatives_trading_coin_futures::websocket_streams {

struct ContractInfoStreamResponseBksInner {
    /// Notional bracket
    std::optional<std::int64_t> bs;
    /// Floor notional of this bracket
    std::optional<std::int64_t> bnf;
    /// Cap notional of this bracket
    std::optional<std::int64_t> bnc;
    /// Maintenance ratio for this bracket
    std::optional<common::Decimal> mmr;
    /// Auxiliary number for quick calculation
    std::optional<std::int64_t> cf;
    /// Min leverage for this bracket
    std::optional<std::int64_t> mi;
    /// Max leverage for this bracket
    std::optional<std::int64_t> ma;

    bool operator==(const ContractInfoStreamResponseBksInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT ContractInfoStreamResponseBksInner
tag_invoke(boost::json::value_to_tag<ContractInfoStreamResponseBksInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const ContractInfoStreamResponseBksInner& v);

} // namespace binance::derivatives_trading_coin_futures::websocket_streams
