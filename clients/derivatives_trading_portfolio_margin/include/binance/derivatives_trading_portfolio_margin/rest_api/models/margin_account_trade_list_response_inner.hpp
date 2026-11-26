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

struct MarginAccountTradeListResponseInner {
    /// Commission.
    std::optional<std::string> commission;
    /// Commission Asset.
    std::optional<std::string> commission_asset;
    /// ID.
    std::optional<std::int64_t> id;
    /// Is Best Match.
    std::optional<bool> is_best_match;
    /// Is Buyer.
    std::optional<bool> is_buyer;
    /// Is Maker.
    std::optional<bool> is_maker;
    /// Normal orderID after trigger if appliable, only have when the strategy is triggered
    std::optional<std::int64_t> order_id;
    /// Price.
    std::optional<std::string> price;
    /// Qty.
    std::optional<std::string> qty;
    /// Trade symbol, if existing.
    std::optional<std::string> symbol;
    /// Event time.
    std::optional<std::int64_t> time;

    bool operator==(const MarginAccountTradeListResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT MarginAccountTradeListResponseInner
tag_invoke(boost::json::value_to_tag<MarginAccountTradeListResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const MarginAccountTradeListResponseInner& v);

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
