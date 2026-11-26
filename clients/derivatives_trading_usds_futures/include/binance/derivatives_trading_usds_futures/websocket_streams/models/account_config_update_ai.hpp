//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <optional>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/derivatives_trading_usds_futures/export.hpp>

namespace binance::derivatives_trading_usds_futures::websocket_streams {

/// User's Account Configuration
struct AccountConfigUpdateAi {
    /// Multi-Assets Mode
    std::optional<bool> j;

    bool operator==(const AccountConfigUpdateAi& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT AccountConfigUpdateAi
tag_invoke(boost::json::value_to_tag<AccountConfigUpdateAi> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                                boost::json::value& jv,
                                                                const AccountConfigUpdateAi& v);

} // namespace binance::derivatives_trading_usds_futures::websocket_streams
