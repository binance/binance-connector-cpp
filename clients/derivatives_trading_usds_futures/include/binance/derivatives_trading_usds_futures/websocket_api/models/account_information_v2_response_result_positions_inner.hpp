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

namespace binance::derivatives_trading_usds_futures::websocket_api {

struct AccountInformationV2ResponseResultPositionsInner {
    std::optional<std::string> symbol;
    /// position side
    std::optional<std::string> position_side;
    std::optional<std::string> position_amt;
    /// unrealized profit
    std::optional<std::string> unrealized_profit;
    std::optional<std::string> isolated_margin;
    std::optional<std::string> notional;
    std::optional<std::string> isolated_wallet;
    /// total initial margin required with current mark price
    std::optional<std::string> initial_margin;
    /// maintenance margin required
    std::optional<std::string> maint_margin;
    /// last update time
    std::optional<std::int64_t> update_time;

    bool
    operator==(const AccountInformationV2ResponseResultPositionsInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT AccountInformationV2ResponseResultPositionsInner
tag_invoke(boost::json::value_to_tag<AccountInformationV2ResponseResultPositionsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const AccountInformationV2ResponseResultPositionsInner& v);

} // namespace binance::derivatives_trading_usds_futures::websocket_api
