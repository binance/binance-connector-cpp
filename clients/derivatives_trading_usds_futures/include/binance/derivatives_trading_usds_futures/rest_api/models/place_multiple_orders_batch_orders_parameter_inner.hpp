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

enum class PlaceMultipleOrdersBatchOrdersParameterInnerSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(PlaceMultipleOrdersBatchOrdersParameterInnerSideEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT PlaceMultipleOrdersBatchOrdersParameterInnerSideEnum
tag_invoke(boost::json::value_to_tag<PlaceMultipleOrdersBatchOrdersParameterInnerSideEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           PlaceMultipleOrdersBatchOrdersParameterInnerSideEnum value);

enum class PlaceMultipleOrdersBatchOrdersParameterInnerPositionSideEnum {
    Both,
    Long,
    Short,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(PlaceMultipleOrdersBatchOrdersParameterInnerPositionSideEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT
PlaceMultipleOrdersBatchOrdersParameterInnerPositionSideEnum tag_invoke(
    boost::json::value_to_tag<PlaceMultipleOrdersBatchOrdersParameterInnerPositionSideEnum> /*tag*/,
    const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
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

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(PlaceMultipleOrdersBatchOrdersParameterInnerTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT PlaceMultipleOrdersBatchOrdersParameterInnerTypeEnum
tag_invoke(boost::json::value_to_tag<PlaceMultipleOrdersBatchOrdersParameterInnerTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           PlaceMultipleOrdersBatchOrdersParameterInnerTypeEnum value);

enum class PlaceMultipleOrdersBatchOrdersParameterInnerTimeInForceEnum {
    Gtc,
    Ioc,
    Fok,
    Gtx,
    Gtd,
    Rpi,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(PlaceMultipleOrdersBatchOrdersParameterInnerTimeInForceEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT
PlaceMultipleOrdersBatchOrdersParameterInnerTimeInForceEnum tag_invoke(
    boost::json::value_to_tag<PlaceMultipleOrdersBatchOrdersParameterInnerTimeInForceEnum> /*tag*/,
    const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           PlaceMultipleOrdersBatchOrdersParameterInnerTimeInForceEnum value);

enum class PlaceMultipleOrdersBatchOrdersParameterInnerReduceOnlyEnum {
    True_,
    False_,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(PlaceMultipleOrdersBatchOrdersParameterInnerReduceOnlyEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT
PlaceMultipleOrdersBatchOrdersParameterInnerReduceOnlyEnum tag_invoke(
    boost::json::value_to_tag<PlaceMultipleOrdersBatchOrdersParameterInnerReduceOnlyEnum> /*tag*/,
    const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           PlaceMultipleOrdersBatchOrdersParameterInnerReduceOnlyEnum value);

enum class PlaceMultipleOrdersBatchOrdersParameterInnerNewOrderRespTypeEnum {
    Ack,
    Result,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(PlaceMultipleOrdersBatchOrdersParameterInnerNewOrderRespTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT
PlaceMultipleOrdersBatchOrdersParameterInnerNewOrderRespTypeEnum
tag_invoke(boost::json::value_to_tag<
               PlaceMultipleOrdersBatchOrdersParameterInnerNewOrderRespTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
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

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(PlaceMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT
PlaceMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum tag_invoke(
    boost::json::value_to_tag<PlaceMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum> /*tag*/,
    const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           PlaceMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum value);

enum class PlaceMultipleOrdersBatchOrdersParameterInnerSelfTradePreventionModeEnum {
    None_,
    ExpireTaker,
    ExpireBoth,
    ExpireMaker,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(PlaceMultipleOrdersBatchOrdersParameterInnerSelfTradePreventionModeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT
PlaceMultipleOrdersBatchOrdersParameterInnerSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<
               PlaceMultipleOrdersBatchOrdersParameterInnerSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           PlaceMultipleOrdersBatchOrdersParameterInnerSelfTradePreventionModeEnum value);

struct PlaceMultipleOrdersBatchOrdersParameterInner {
    std::optional<std::string> symbol;
    std::optional<PlaceMultipleOrdersBatchOrdersParameterInnerSideEnum> side;
    /// Default `BOTH` for One-way Mode; `LONG` or `SHORT` for Hedge Mode.
    std::optional<PlaceMultipleOrdersBatchOrdersParameterInnerPositionSideEnum> position_side;
    std::optional<PlaceMultipleOrdersBatchOrdersParameterInnerTypeEnum> type;
    std::optional<PlaceMultipleOrdersBatchOrdersParameterInnerTimeInForceEnum> time_in_force;
    std::optional<common::Decimal> quantity;
    std::optional<PlaceMultipleOrdersBatchOrdersParameterInnerReduceOnlyEnum> reduce_only;
    std::optional<common::Decimal> price;
    std::optional<std::string> new_client_order_id;
    std::optional<PlaceMultipleOrdersBatchOrdersParameterInnerNewOrderRespTypeEnum>
        new_order_resp_type;
    /// only avaliable for LIMIT/STOP/TAKE_PROFIT order; Can't be passed together with price
    std::optional<PlaceMultipleOrdersBatchOrdersParameterInnerPriceMatchEnum> price_match;
    /// EXPIRE_TAKER: expire taker order when STP triggers/ EXPIRE_MAKER: expire taker order when
    /// STP triggers/ EXPIRE_BOTH: expire both orders when STP triggers; default NONE
    std::optional<PlaceMultipleOrdersBatchOrdersParameterInnerSelfTradePreventionModeEnum>
        self_trade_prevention_mode;
    /// Auto-cancel time for `GTD` orders.
    std::optional<std::int64_t> good_till_date;

    bool operator==(const PlaceMultipleOrdersBatchOrdersParameterInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT PlaceMultipleOrdersBatchOrdersParameterInner
tag_invoke(boost::json::value_to_tag<PlaceMultipleOrdersBatchOrdersParameterInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const PlaceMultipleOrdersBatchOrdersParameterInner& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
