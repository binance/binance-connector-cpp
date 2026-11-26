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

struct AccountTradeListResponseInner {
    /// Buyer.
    std::optional<bool> buyer;
    /// Commission.
    std::optional<std::string> commission;
    /// Commission Asset.
    std::optional<std::string> commission_asset;
    /// Id.
    std::optional<std::int64_t> id;
    /// Maker.
    std::optional<bool> maker;
    /// Order Id.
    std::optional<std::int64_t> order_id;
    /// Price.
    std::optional<std::string> price;
    /// Qty.
    std::optional<std::string> qty;
    /// Quote asset quantity. Populated for USDⓈ-M symbols; returns "0" for COIN-M symbols.
    std::optional<std::string> quote_qty;
    /// Base asset quantity. Populated for COIN-M symbols; returns "0" for USDⓈ-M symbols.
    std::optional<std::string> base_qty;
    /// Margin Asset.
    std::optional<std::string> margin_asset;
    /// Realized Pnl.
    std::optional<std::string> realized_pnl;
    /// Side.
    std::optional<std::string> side;
    /// Position Side.
    std::optional<std::string> position_side;
    /// Symbol.
    std::optional<std::string> symbol;
    /// Pair.
    std::optional<std::string> pair;
    /// Time.
    std::optional<std::int64_t> time;

    bool operator==(const AccountTradeListResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT AccountTradeListResponseInner tag_invoke(
    boost::json::value_to_tag<AccountTradeListResponseInner> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const AccountTradeListResponseInner& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
