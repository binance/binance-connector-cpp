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

#include <binance/derivatives_trading_coin_futures/export.hpp>

namespace binance::derivatives_trading_coin_futures::rest_api {

/// Latest token price.
struct GetOrderModifyHistoryResponseInnerAmendmentPrice {
    /// Before value.
    std::optional<std::string> before;
    /// After value.
    std::optional<std::string> after;

    bool
    operator==(const GetOrderModifyHistoryResponseInnerAmendmentPrice& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT GetOrderModifyHistoryResponseInnerAmendmentPrice
tag_invoke(boost::json::value_to_tag<GetOrderModifyHistoryResponseInnerAmendmentPrice> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetOrderModifyHistoryResponseInnerAmendmentPrice& v);

} // namespace binance::derivatives_trading_coin_futures::rest_api
