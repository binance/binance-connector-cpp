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
#include <string_view>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/common/decimal.hpp>
#include <binance/derivatives_trading_coin_futures/export.hpp>

namespace binance::derivatives_trading_coin_futures::rest_api {

enum class PlaceMultipleOrdersBatchOrdersParameterInnerSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT std::string_view
to_string(PlaceMultipleOrdersBatchOrdersParameterInnerSideEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT PlaceMultipleOrdersBatchOrdersParameterInnerSideEnum
tag_invoke(boost::json::value_to_tag<PlaceMultipleOrdersBatchOrdersParameterInnerSideEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           PlaceMultipleOrdersBatchOrdersParameterInnerSideEnum value);

enum class PlaceMultipleOrdersBatchOrdersParameterInnerPositionSideEnum {
    Both,
    Long,
    Short,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT std::string_view
to_string(PlaceMultipleOrdersBatchOrdersParameterInnerPositionSideEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT
PlaceMultipleOrdersBatchOrdersParameterInnerPositionSideEnum tag_invoke(
    boost::json::value_to_tag<PlaceMultipleOrdersBatchOrdersParameterInnerPositionSideEnum> /*tag*/,
    const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           PlaceMultipleOrdersBatchOrdersParameterInnerPositionSideEnum value);

enum class PlaceMultipleOrdersBatchOrdersParameterInnerTypeEnum {
    Limit,
    Market,
    Stop,
    StopMarket,
    TakeProfit,
    TakeProfitMarket,
    TrailingStopMarket,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT std::string_view
to_string(PlaceMultipleOrdersBatchOrdersParameterInnerTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT PlaceMultipleOrdersBatchOrdersParameterInnerTypeEnum
tag_invoke(boost::json::value_to_tag<PlaceMultipleOrdersBatchOrdersParameterInnerTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           PlaceMultipleOrdersBatchOrdersParameterInnerTypeEnum value);

enum class PlaceMultipleOrdersBatchOrdersParameterInnerTimeInForceEnum {
    Gtc,
    Ioc,
    Fok,
    Gtx,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT std::string_view
to_string(PlaceMultipleOrdersBatchOrdersParameterInnerTimeInForceEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT
PlaceMultipleOrdersBatchOrdersParameterInnerTimeInForceEnum tag_invoke(
    boost::json::value_to_tag<PlaceMultipleOrdersBatchOrdersParameterInnerTimeInForceEnum> /*tag*/,
    const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           PlaceMultipleOrdersBatchOrdersParameterInnerTimeInForceEnum value);

enum class PlaceMultipleOrdersBatchOrdersParameterInnerReduceOnlyEnum {
    True_,
    False_,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT std::string_view
to_string(PlaceMultipleOrdersBatchOrdersParameterInnerReduceOnlyEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT
PlaceMultipleOrdersBatchOrdersParameterInnerReduceOnlyEnum tag_invoke(
    boost::json::value_to_tag<PlaceMultipleOrdersBatchOrdersParameterInnerReduceOnlyEnum> /*tag*/,
    const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           PlaceMultipleOrdersBatchOrdersParameterInnerReduceOnlyEnum value);

enum class PlaceMultipleOrdersBatchOrdersParameterInnerWorkingTypeEnum {
    MarkPrice,
    ContractPrice,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT std::string_view
to_string(PlaceMultipleOrdersBatchOrdersParameterInnerWorkingTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT
PlaceMultipleOrdersBatchOrdersParameterInnerWorkingTypeEnum tag_invoke(
    boost::json::value_to_tag<PlaceMultipleOrdersBatchOrdersParameterInnerWorkingTypeEnum> /*tag*/,
    const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           PlaceMultipleOrdersBatchOrdersParameterInnerWorkingTypeEnum value);

enum class PlaceMultipleOrdersBatchOrdersParameterInnerPriceProtectEnum {
    True_,
    False_,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT std::string_view
to_string(PlaceMultipleOrdersBatchOrdersParameterInnerPriceProtectEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT
PlaceMultipleOrdersBatchOrdersParameterInnerPriceProtectEnum tag_invoke(
    boost::json::value_to_tag<PlaceMultipleOrdersBatchOrdersParameterInnerPriceProtectEnum> /*tag*/,
    const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           PlaceMultipleOrdersBatchOrdersParameterInnerPriceProtectEnum value);

enum class PlaceMultipleOrdersBatchOrdersParameterInnerNewOrderRespTypeEnum {
    Ack,
    Result,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT std::string_view
to_string(PlaceMultipleOrdersBatchOrdersParameterInnerNewOrderRespTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT
PlaceMultipleOrdersBatchOrdersParameterInnerNewOrderRespTypeEnum
tag_invoke(boost::json::value_to_tag<
               PlaceMultipleOrdersBatchOrdersParameterInnerNewOrderRespTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           PlaceMultipleOrdersBatchOrdersParameterInnerNewOrderRespTypeEnum value);

enum class PlaceMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum {
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

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT std::string_view
to_string(PlaceMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT
PlaceMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum tag_invoke(
    boost::json::value_to_tag<PlaceMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum> /*tag*/,
    const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           PlaceMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum value);

enum class PlaceMultipleOrdersBatchOrdersParameterInnerSelfTradePreventionModeEnum {
    ExpireTaker,
    ExpireMaker,
    ExpireBoth,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT std::string_view
to_string(PlaceMultipleOrdersBatchOrdersParameterInnerSelfTradePreventionModeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT
PlaceMultipleOrdersBatchOrdersParameterInnerSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<
               PlaceMultipleOrdersBatchOrdersParameterInnerSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           PlaceMultipleOrdersBatchOrdersParameterInnerSelfTradePreventionModeEnum value);

struct PlaceMultipleOrdersBatchOrdersParameterInner {
    /// Symbol
    std::optional<std::string> symbol;
    std::optional<PlaceMultipleOrdersBatchOrdersParameterInnerSideEnum> side;
    /// Default `BOTH` for One-way Mode ; `LONG` or `SHORT` for Hedge Mode. It must be sent with
    /// Hedge Mode.
    std::optional<PlaceMultipleOrdersBatchOrdersParameterInnerPositionSideEnum> position_side;
    /// **After CM migration, stop-type values (`STOP`, `STOP_MARKET`, `TAKE_PROFIT`,
    /// `TAKE_PROFIT_MARKET`, `TRAILING_STOP_MARKET`) are no longer accepted on a per-element basis
    /// and will return element-level `-4120`. Use the new `/dapi/v1/algoOrder` endpoint instead.**
    std::optional<PlaceMultipleOrdersBatchOrdersParameterInnerTypeEnum> type;
    std::optional<PlaceMultipleOrdersBatchOrdersParameterInnerTimeInForceEnum> time_in_force;
    /// quantity measured by contract number
    std::optional<common::Decimal> quantity;
    std::optional<PlaceMultipleOrdersBatchOrdersParameterInnerReduceOnlyEnum> reduce_only;
    /// Order price
    std::optional<common::Decimal> price;
    /// A unique id among open orders. Automatically generated if not sent. Can only be string
    /// following the rule: `^[\.A-Z\:/a-z0-9_-]{1,36}$`
    std::optional<std::string> new_client_order_id;
    /// Used with `STOP/STOP_MARKET` or `TAKE_PROFIT/TAKE_PROFIT_MARKET` orders.
    std::optional<common::Decimal> stop_price;
    /// Used with `TRAILING_STOP_MARKET` orders, default as the latest price(supporting different
    /// `workingType`)
    std::optional<common::Decimal> activation_price;
    /// Used with `TRAILING_STOP_MARKET` orders, min 0.1, max 4 where 1 for 1%
    std::optional<common::Decimal> callback_rate;
    std::optional<PlaceMultipleOrdersBatchOrdersParameterInnerWorkingTypeEnum> working_type;
    /// Used with `STOP/STOP_MARKET` or `TAKE_PROFIT/TAKE_PROFIT_MARKET` orders.
    std::optional<PlaceMultipleOrdersBatchOrdersParameterInnerPriceProtectEnum> price_protect;
    std::optional<PlaceMultipleOrdersBatchOrdersParameterInnerNewOrderRespTypeEnum>
        new_order_resp_type;
    /// only avaliable for `LIMIT`/`STOP`/`TAKE_PROFIT` order; can't be passed together with `price`
    std::optional<PlaceMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum> price_match;
    /// `EXPIRE_TAKER`: expire taker order when STP triggers/ `EXPIRE_MAKER`: expire taker order
    /// when STP triggers/ `EXPIRE_BOTH`: expire both orders when STP triggers
    std::optional<PlaceMultipleOrdersBatchOrdersParameterInnerSelfTradePreventionModeEnum>
        self_trade_prevention_mode;

    bool operator==(const PlaceMultipleOrdersBatchOrdersParameterInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT PlaceMultipleOrdersBatchOrdersParameterInner
tag_invoke(boost::json::value_to_tag<PlaceMultipleOrdersBatchOrdersParameterInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const PlaceMultipleOrdersBatchOrdersParameterInner& v);

} // namespace binance::derivatives_trading_coin_futures::rest_api
