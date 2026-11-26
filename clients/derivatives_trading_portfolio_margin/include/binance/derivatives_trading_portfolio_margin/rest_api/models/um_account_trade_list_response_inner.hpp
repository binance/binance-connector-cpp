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

#include <binance/derivatives_trading_portfolio_margin/export.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

struct UmAccountTradeListResponseInner {
    /// Trade symbol, if existing.
    std::optional<std::string> symbol;
    /// ID.
    std::optional<std::int64_t> id;
    /// Normal orderID after trigger if appliable, only have when the strategy is triggered
    std::optional<std::int64_t> order_id;
    /// Side.
    std::optional<std::string> side;
    /// Price.
    std::optional<std::string> price;
    /// Qty.
    std::optional<std::string> qty;
    /// Realized Pnl.
    std::optional<std::string> realized_pnl;
    /// Quote Qty.
    std::optional<std::string> quote_qty;
    /// Commission.
    std::optional<std::string> commission;
    /// Commission Asset.
    std::optional<std::string> commission_asset;
    /// Event time.
    std::optional<std::int64_t> time;
    /// Buyer.
    std::optional<bool> buyer;
    /// Maker.
    std::optional<bool> maker;
    /// BOTH means that it is the position of One-way Mode
    std::optional<std::string> position_side;

    bool operator==(const UmAccountTradeListResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT UmAccountTradeListResponseInner
tag_invoke(boost::json::value_to_tag<UmAccountTradeListResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const UmAccountTradeListResponseInner& v);

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
