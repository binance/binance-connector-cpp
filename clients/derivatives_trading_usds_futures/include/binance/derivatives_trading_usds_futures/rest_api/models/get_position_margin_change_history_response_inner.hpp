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

namespace binance::derivatives_trading_usds_futures::rest_api {

struct GetPositionMarginChangeHistoryResponseInner {
    /// Symbol.
    std::optional<std::string> symbol;
    /// Type.
    std::optional<std::int64_t> type;
    /// Delta Type.
    std::optional<std::string> delta_type;
    /// Amount.
    std::optional<std::string> amount;
    /// Asset.
    std::optional<std::string> asset;
    /// Time.
    std::optional<std::int64_t> time;
    /// Position Side.
    std::optional<std::string> position_side;

    bool operator==(const GetPositionMarginChangeHistoryResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT GetPositionMarginChangeHistoryResponseInner
tag_invoke(boost::json::value_to_tag<GetPositionMarginChangeHistoryResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetPositionMarginChangeHistoryResponseInner& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
