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

struct QueryCmPositionInformationResponseInner {
    /// Trade symbol, if existing.
    std::optional<std::string> symbol;
    /// position amount
    std::optional<std::string> position_amt;
    /// average entry price
    std::optional<std::string> entry_price;
    /// Mark Price.
    std::optional<std::string> mark_price;
    /// Un Realized Profit.
    std::optional<std::string> un_realized_profit;
    /// Liquidation Price.
    std::optional<std::string> liquidation_price;
    /// current initial leverage
    std::optional<std::string> leverage;
    /// BOTH means that it is the position of One-way Mode
    std::optional<std::string> position_side;
    /// last update time
    std::optional<std::int64_t> update_time;
    /// maximum quantity of base asset
    std::optional<std::string> max_qty;
    /// Notional Value.
    std::optional<std::string> notional_value;

    bool operator==(const QueryCmPositionInformationResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT QueryCmPositionInformationResponseInner
tag_invoke(boost::json::value_to_tag<QueryCmPositionInformationResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const QueryCmPositionInformationResponseInner& v);

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
