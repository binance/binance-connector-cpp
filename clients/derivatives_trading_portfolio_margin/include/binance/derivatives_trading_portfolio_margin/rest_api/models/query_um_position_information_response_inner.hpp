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

struct QueryUmPositionInformationResponseInner {
    /// average entry price
    std::optional<std::string> entry_price;
    /// current initial leverage
    std::optional<std::string> leverage;
    /// Mark Price.
    std::optional<std::string> mark_price;
    /// Max Notional Value.
    std::optional<std::string> max_notional_value;
    /// position amount
    std::optional<std::string> position_amt;
    /// Notional.
    std::optional<std::string> notional;
    /// Trade symbol, if existing.
    std::optional<std::string> symbol;
    /// Un Realized Profit.
    std::optional<std::string> un_realized_profit;
    /// Liquidation Price.
    std::optional<std::string> liquidation_price;
    /// BOTH means that it is the position of One-way Mode
    std::optional<std::string> position_side;
    /// last update time
    std::optional<std::int64_t> update_time;

    bool operator==(const QueryUmPositionInformationResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT QueryUmPositionInformationResponseInner
tag_invoke(boost::json::value_to_tag<QueryUmPositionInformationResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const QueryUmPositionInformationResponseInner& v);

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
