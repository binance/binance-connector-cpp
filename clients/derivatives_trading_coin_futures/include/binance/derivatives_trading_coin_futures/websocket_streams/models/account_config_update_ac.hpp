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

namespace binance::derivatives_trading_coin_futures::websocket_streams {

struct AccountConfigUpdateAc {
    /// Symbol
    std::optional<std::string> s;
    /// Leverage
    std::optional<std::int64_t> l;

    bool operator==(const AccountConfigUpdateAc& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT AccountConfigUpdateAc
tag_invoke(boost::json::value_to_tag<AccountConfigUpdateAc> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                                boost::json::value& jv,
                                                                const AccountConfigUpdateAc& v);

} // namespace binance::derivatives_trading_coin_futures::websocket_streams
