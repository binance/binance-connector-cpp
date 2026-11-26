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
#include <string_view>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/common/decimal.hpp>
#include <binance/derivatives_trading_usds_futures/export.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

enum class ModifyMultipleOrdersBatchOrdersParameterInnerSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(ModifyMultipleOrdersBatchOrdersParameterInnerSideEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT
ModifyMultipleOrdersBatchOrdersParameterInnerSideEnum
tag_invoke(boost::json::value_to_tag<ModifyMultipleOrdersBatchOrdersParameterInnerSideEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           ModifyMultipleOrdersBatchOrdersParameterInnerSideEnum value);

enum class ModifyMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum {
    Opponent,
    Opponent5,
    Opponent10,
    Opponent20,
    Queue,
    Queue5,
    Queue10,
    Queue20,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(ModifyMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT
ModifyMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum tag_invoke(
    boost::json::value_to_tag<ModifyMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum> /*tag*/,
    const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           ModifyMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum value);

struct ModifyMultipleOrdersBatchOrdersParameterInner {
    std::optional<std::int64_t> order_id;
    std::optional<std::string> orig_client_order_id;
    std::optional<std::string> symbol;
    std::optional<ModifyMultipleOrdersBatchOrdersParameterInnerSideEnum> side;
    /// Order quantity, cannot be sent with closePosition=true
    std::optional<common::Decimal> quantity;
    std::optional<common::Decimal> price;
    /// Only avaliable for LIMIT/STOP/TAKE_PROFIT order; Cannot be sent together with `price`.
    std::optional<ModifyMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum> price_match;
    /// stop price, only STOP, STOP_MARKET, TAKE_PROFIT, TAKE_PROFIT_MARKET need
    std::optional<common::Decimal> stop_price;
    /// User-defined modification identifier, returned as-is in the response. Optional; not
    /// validated for uniqueness.
    std::optional<std::int64_t> modify_id;
    /// Validity window in milliseconds.
    std::optional<std::int64_t> recv_window;
    /// Unix timestamp in milliseconds.
    std::optional<std::int64_t> timestamp;

    bool operator==(const ModifyMultipleOrdersBatchOrdersParameterInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT ModifyMultipleOrdersBatchOrdersParameterInner
tag_invoke(boost::json::value_to_tag<ModifyMultipleOrdersBatchOrdersParameterInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const ModifyMultipleOrdersBatchOrdersParameterInner& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
