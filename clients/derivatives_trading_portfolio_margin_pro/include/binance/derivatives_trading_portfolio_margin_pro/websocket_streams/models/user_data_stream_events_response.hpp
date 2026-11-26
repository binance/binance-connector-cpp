//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <variant>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/derivatives_trading_portfolio_margin_pro/export.hpp>
#include <binance/derivatives_trading_portfolio_margin_pro/websocket_streams/models/pm_pro_account_update.hpp>
#include <binance/derivatives_trading_portfolio_margin_pro/websocket_streams/models/risklevelchange.hpp>

namespace binance::derivatives_trading_portfolio_margin_pro::websocket_streams {

struct UserDataStreamEventsResponse {
    /// One of the alternatives, or the raw JSON when none matches.
    std::variant<PmProAccountUpdate, Risklevelchange, boost::json::value> value;

    bool operator==(const UserDataStreamEventsResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_PRO_EXPORT UserDataStreamEventsResponse tag_invoke(
    boost::json::value_to_tag<UserDataStreamEventsResponse> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_PRO_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const UserDataStreamEventsResponse& v);

} // namespace binance::derivatives_trading_portfolio_margin_pro::websocket_streams
