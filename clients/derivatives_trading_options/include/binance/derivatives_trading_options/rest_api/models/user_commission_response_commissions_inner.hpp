//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <optional>
#include <string>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/derivatives_trading_options/export.hpp>

namespace binance::derivatives_trading_options::rest_api {

struct UserCommissionResponseCommissionsInner {
    /// underlying
    std::optional<std::string> underlying;
    /// maker Fee
    std::optional<std::string> maker_fee;
    /// taker Fee
    std::optional<std::string> taker_fee;

    bool operator==(const UserCommissionResponseCommissionsInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT UserCommissionResponseCommissionsInner
tag_invoke(boost::json::value_to_tag<UserCommissionResponseCommissionsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const UserCommissionResponseCommissionsInner& v);

} // namespace binance::derivatives_trading_options::rest_api
