//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/common/decimal.hpp>
#include <binance/common/required.hpp>
#include <binance/common/websocket_api.hpp>
#include <binance/derivatives_trading_usds_futures/export.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_api/models/cancel_algo_order_response_result.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_api/models/cancel_order_response_result.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_api/models/modify_order_response_result.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_api/models/new_algo_order_response_result.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_api/models/new_order_response_result.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_api/models/position_information_response_result_inner.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_api/models/position_information_v2_response_result_inner.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_api/models/query_order_response_result.hpp>

namespace binance::derivatives_trading_usds_futures::websocket_api {

enum class ModifyOrderSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(ModifyOrderSideEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT ModifyOrderSideEnum
tag_invoke(boost::json::value_to_tag<ModifyOrderSideEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv, ModifyOrderSideEnum value);

enum class ModifyOrderPriceMatchEnum {
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
to_string(ModifyOrderPriceMatchEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT ModifyOrderPriceMatchEnum tag_invoke(
    boost::json::value_to_tag<ModifyOrderPriceMatchEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                                boost::json::value& jv,
                                                                ModifyOrderPriceMatchEnum value);

enum class ModifyOrderReduceOnlyEnum {
    True_,
    False_,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(ModifyOrderReduceOnlyEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT ModifyOrderReduceOnlyEnum tag_invoke(
    boost::json::value_to_tag<ModifyOrderReduceOnlyEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                                boost::json::value& jv,
                                                                ModifyOrderReduceOnlyEnum value);

enum class NewAlgoOrderAlgoTypeEnum {
    Conditional,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(NewAlgoOrderAlgoTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT NewAlgoOrderAlgoTypeEnum tag_invoke(
    boost::json::value_to_tag<NewAlgoOrderAlgoTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                                boost::json::value& jv,
                                                                NewAlgoOrderAlgoTypeEnum value);

enum class NewAlgoOrderSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(NewAlgoOrderSideEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT NewAlgoOrderSideEnum
tag_invoke(boost::json::value_to_tag<NewAlgoOrderSideEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv, NewAlgoOrderSideEnum value);

enum class NewAlgoOrderTypeEnum {
    StopMarket,
    TakeProfitMarket,
    Stop,
    TakeProfit,
    TrailingStopMarket,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(NewAlgoOrderTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT NewAlgoOrderTypeEnum
tag_invoke(boost::json::value_to_tag<NewAlgoOrderTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv, NewAlgoOrderTypeEnum value);

enum class NewAlgoOrderPositionSideEnum {
    Both,
    Long,
    Short,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(NewAlgoOrderPositionSideEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT NewAlgoOrderPositionSideEnum tag_invoke(
    boost::json::value_to_tag<NewAlgoOrderPositionSideEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                                boost::json::value& jv,
                                                                NewAlgoOrderPositionSideEnum value);

enum class NewAlgoOrderTimeInForceEnum {
    Ioc,
    Gtc,
    Fok,
    Gtx,
    Gtd,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(NewAlgoOrderTimeInForceEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT NewAlgoOrderTimeInForceEnum tag_invoke(
    boost::json::value_to_tag<NewAlgoOrderTimeInForceEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                                boost::json::value& jv,
                                                                NewAlgoOrderTimeInForceEnum value);

enum class NewAlgoOrderWorkingTypeEnum {
    MarkPrice,
    ContractPrice,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(NewAlgoOrderWorkingTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT NewAlgoOrderWorkingTypeEnum tag_invoke(
    boost::json::value_to_tag<NewAlgoOrderWorkingTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                                boost::json::value& jv,
                                                                NewAlgoOrderWorkingTypeEnum value);

enum class NewAlgoOrderPriceMatchEnum {
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
to_string(NewAlgoOrderPriceMatchEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT NewAlgoOrderPriceMatchEnum tag_invoke(
    boost::json::value_to_tag<NewAlgoOrderPriceMatchEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                                boost::json::value& jv,
                                                                NewAlgoOrderPriceMatchEnum value);

enum class NewAlgoOrderClosePositionEnum {
    True_,
    False_,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(NewAlgoOrderClosePositionEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT NewAlgoOrderClosePositionEnum tag_invoke(
    boost::json::value_to_tag<NewAlgoOrderClosePositionEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           NewAlgoOrderClosePositionEnum value);

enum class NewAlgoOrderPriceProtectEnum {
    True_,
    False_,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(NewAlgoOrderPriceProtectEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT NewAlgoOrderPriceProtectEnum tag_invoke(
    boost::json::value_to_tag<NewAlgoOrderPriceProtectEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                                boost::json::value& jv,
                                                                NewAlgoOrderPriceProtectEnum value);

enum class NewAlgoOrderReduceOnlyEnum {
    True_,
    False_,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(NewAlgoOrderReduceOnlyEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT NewAlgoOrderReduceOnlyEnum tag_invoke(
    boost::json::value_to_tag<NewAlgoOrderReduceOnlyEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                                boost::json::value& jv,
                                                                NewAlgoOrderReduceOnlyEnum value);

enum class NewAlgoOrderNewOrderRespTypeEnum {
    Ack,
    Result,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(NewAlgoOrderNewOrderRespTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT NewAlgoOrderNewOrderRespTypeEnum
tag_invoke(boost::json::value_to_tag<NewAlgoOrderNewOrderRespTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           NewAlgoOrderNewOrderRespTypeEnum value);

enum class NewAlgoOrderSelfTradePreventionModeEnum {
    None_,
    ExpireTaker,
    ExpireBoth,
    ExpireMaker,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(NewAlgoOrderSelfTradePreventionModeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT NewAlgoOrderSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<NewAlgoOrderSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           NewAlgoOrderSelfTradePreventionModeEnum value);

enum class NewOrderSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(NewOrderSideEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT NewOrderSideEnum
tag_invoke(boost::json::value_to_tag<NewOrderSideEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv, NewOrderSideEnum value);

enum class NewOrderTypeEnum {
    Limit,
    Market,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(NewOrderTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT NewOrderTypeEnum
tag_invoke(boost::json::value_to_tag<NewOrderTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv, NewOrderTypeEnum value);

enum class NewOrderPositionSideEnum {
    Both,
    Long,
    Short,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(NewOrderPositionSideEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT NewOrderPositionSideEnum tag_invoke(
    boost::json::value_to_tag<NewOrderPositionSideEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                                boost::json::value& jv,
                                                                NewOrderPositionSideEnum value);

enum class NewOrderTimeInForceEnum {
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
to_string(NewOrderTimeInForceEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT NewOrderTimeInForceEnum tag_invoke(
    boost::json::value_to_tag<NewOrderTimeInForceEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                                boost::json::value& jv,
                                                                NewOrderTimeInForceEnum value);

enum class NewOrderReduceOnlyEnum {
    True_,
    False_,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(NewOrderReduceOnlyEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT NewOrderReduceOnlyEnum
tag_invoke(boost::json::value_to_tag<NewOrderReduceOnlyEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                                boost::json::value& jv,
                                                                NewOrderReduceOnlyEnum value);

enum class NewOrderNewOrderRespTypeEnum {
    Ack,
    Result,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(NewOrderNewOrderRespTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT NewOrderNewOrderRespTypeEnum tag_invoke(
    boost::json::value_to_tag<NewOrderNewOrderRespTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                                boost::json::value& jv,
                                                                NewOrderNewOrderRespTypeEnum value);

enum class NewOrderPriceMatchEnum {
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
to_string(NewOrderPriceMatchEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT NewOrderPriceMatchEnum
tag_invoke(boost::json::value_to_tag<NewOrderPriceMatchEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                                boost::json::value& jv,
                                                                NewOrderPriceMatchEnum value);

enum class NewOrderSelfTradePreventionModeEnum {
    None_,
    ExpireTaker,
    ExpireBoth,
    ExpireMaker,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(NewOrderSelfTradePreventionModeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT NewOrderSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<NewOrderSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           NewOrderSelfTradePreventionModeEnum value);

struct CancelAlgoOrderParams {
    /// Id.
    std::optional<std::string> id = std::nullopt;
    /// Algo Id.
    std::optional<std::int64_t> algo_id = std::nullopt;
    /// Client Algo Id.
    std::optional<std::string> client_algo_id = std::nullopt;
    /// Recv Window.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct CancelOrderParams {
    /// Symbol.
    common::Required<std::string> symbol;
    /// Id.
    std::optional<std::string> id = std::nullopt;
    /// Order Id.
    std::optional<std::int64_t> order_id = std::nullopt;
    /// Orig Client Order Id.
    std::optional<std::string> orig_client_order_id = std::nullopt;
    /// Recv Window.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct ModifyOrderParams {
    /// Symbol.
    common::Required<std::string> symbol;
    /// `SELL`, `BUY`
    common::Required<ModifyOrderSideEnum> side;
    /// Order quantity, cannot be sent with `closePosition=true`
    common::Required<common::Decimal> quantity;
    /// Price.
    common::Required<common::Decimal> price;
    /// Id.
    std::optional<std::string> id = std::nullopt;
    /// Order Id.
    std::optional<std::int64_t> order_id = std::nullopt;
    /// Orig Client Order Id.
    std::optional<std::string> orig_client_order_id = std::nullopt;
    /// only avaliable for LIMIT/STOP/TAKE_PROFIT order; Can't be passed together with price
    std::optional<ModifyOrderPriceMatchEnum> price_match = std::nullopt;
    /// User-defined modification identifier, returned as-is in the response. Optional; not
    /// validated for uniqueness.
    std::optional<std::int64_t> modify_id = std::nullopt;
    /// See notes below for behavior.
    std::optional<ModifyOrderReduceOnlyEnum> reduce_only = std::nullopt;
    /// Recv Window.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct NewAlgoOrderParams {
    /// Only support `CONDITIONAL`
    common::Required<NewAlgoOrderAlgoTypeEnum> algo_type;
    /// Symbol.
    common::Required<std::string> symbol;
    /// Side.
    common::Required<NewAlgoOrderSideEnum> side;
    /// For `CONDITIONAL` algoType,
    /// `STOP_MARKET`/`TAKE_PROFIT_MARKET`/`STOP`/`TAKE_PROFIT`/`TRAILING_STOP_MARKET` as order type
    common::Required<NewAlgoOrderTypeEnum> type;
    /// Id.
    std::optional<std::string> id = std::nullopt;
    /// Default BOTH for One-way Mode ; LONG or SHORT for Hedge Mode. It must be sent in Hedge Mode.
    std::optional<NewAlgoOrderPositionSideEnum> position_side = std::nullopt;
    /// `IOC` or `GTC` or `FOK` or `GTX` or `GTD`, default `GTC`
    std::optional<NewAlgoOrderTimeInForceEnum> time_in_force = std::nullopt;
    /// Cannot be sent with `closePosition`=`true`(Close-All)
    std::optional<common::Decimal> quantity = std::nullopt;
    /// Price.
    std::optional<common::Decimal> price = std::nullopt;
    /// Trigger Price.
    std::optional<common::Decimal> trigger_price = std::nullopt;
    /// triggerPrice triggered by: `MARK_PRICE`, `CONTRACT_PRICE`. Default `CONTRACT_PRICE`
    std::optional<NewAlgoOrderWorkingTypeEnum> working_type = std::nullopt;
    /// only avaliable for LIMIT/STOP/TAKE_PROFIT order; Can't be passed together with price
    std::optional<NewAlgoOrderPriceMatchEnum> price_match = std::nullopt;
    /// Close-All，used with STOP_MARKET or TAKE_PROFIT_MARKET.
    std::optional<NewAlgoOrderClosePositionEnum> close_position = std::nullopt;
    /// Used with STOP_MARKET or TAKE_PROFIT_MARKET order. when price reaches the triggerPrice ，the
    /// difference rate between "MARK_PRICE" and "CONTRACT_PRICE" cannot be larger than the Price
    /// Protection Threshold of the symbol.
    std::optional<NewAlgoOrderPriceProtectEnum> price_protect = std::nullopt;
    /// Cannot be sent in Hedge Mode; cannot be sent with closePosition=true
    std::optional<NewAlgoOrderReduceOnlyEnum> reduce_only = std::nullopt;
    /// Used with TRAILING_STOP_MARKET orders, default as the latest price(supporting different
    /// workingType)
    std::optional<common::Decimal> activate_price = std::nullopt;
    /// Used with TRAILING_STOP_MARKET orders
    std::optional<common::Decimal> callback_rate = std::nullopt;
    /// A unique id among open orders. Automatically generated if not sent. Can only be string
    /// following the rule: `^[\.A-Z\:/a-z0-9_-]{1,36}$`
    std::optional<std::string> client_algo_id = std::nullopt;
    /// "ACK", "RESULT", default "ACK"
    std::optional<NewAlgoOrderNewOrderRespTypeEnum> new_order_resp_type = std::nullopt;
    /// `EXPIRE_TAKER`: expire taker order when STP triggers/ `EXPIRE_MAKER`: expire taker order
    /// when STP triggers/ `EXPIRE_BOTH`: expire both orders when STP triggers; default `NONE`
    std::optional<NewAlgoOrderSelfTradePreventionModeEnum> self_trade_prevention_mode =
        std::nullopt;
    /// order cancel time for timeInForce `GTD`, mandatory when `timeInforce` set to `GTD`; order
    /// the timestamp only retains second-level precision, ms part will be ignored; The goodTillDate
    /// timestamp must be greater than the current time plus 600 seconds and smaller than
    /// 253402300799000
    std::optional<std::int64_t> good_till_date = std::nullopt;
    /// Recv Window.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct NewOrderParams {
    /// Symbol.
    common::Required<std::string> symbol;
    /// Side.
    common::Required<NewOrderSideEnum> side;
    common::Required<NewOrderTypeEnum> type;
    /// Id.
    std::optional<std::string> id = std::nullopt;
    /// Default `BOTH` for One-way Mode ; `LONG` or `SHORT` for Hedge Mode. It must be sent in Hedge
    /// Mode.
    std::optional<NewOrderPositionSideEnum> position_side = std::nullopt;
    /// Time In Force.
    std::optional<NewOrderTimeInForceEnum> time_in_force = std::nullopt;
    /// Cannot be sent in Hedge Mode
    std::optional<NewOrderReduceOnlyEnum> reduce_only = std::nullopt;
    std::optional<common::Decimal> quantity = std::nullopt;
    /// Price.
    std::optional<common::Decimal> price = std::nullopt;
    /// A unique id among open orders. Automatically generated if not sent. Can only be string
    /// following the rule: `^[\.A-Z\:/a-z0-9_-]{1,36}$`
    std::optional<std::string> new_client_order_id = std::nullopt;
    std::optional<NewOrderNewOrderRespTypeEnum> new_order_resp_type = std::nullopt;
    /// only available for `LIMIT` order; Can't be passed together with `price`
    std::optional<NewOrderPriceMatchEnum> price_match = std::nullopt;
    /// `NONE`: No STP / `EXPIRE_TAKER`: expire taker order when STP triggers/ `EXPIRE_MAKER`:
    /// expire taker order when STP triggers/ `EXPIRE_BOTH`: expire both orders when STP triggers;
    /// default `NONE`
    std::optional<NewOrderSelfTradePreventionModeEnum> self_trade_prevention_mode = std::nullopt;
    /// order cancel time for timeInForce `GTD`, mandatory when `timeInforce` set to `GTD`; order
    /// the timestamp only retains second-level precision, ms part will be ignored; The goodTillDate
    /// timestamp must be greater than the current time plus 600 seconds and smaller than
    /// 253402300799000
    std::optional<std::int64_t> good_till_date = std::nullopt;
    /// Recv Window.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct PositionInformationParams {
    /// Id.
    std::optional<std::string> id = std::nullopt;
    /// Symbol.
    std::optional<std::string> symbol = std::nullopt;
    /// Recv Window.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct PositionInformationV2Params {
    /// Id.
    std::optional<std::string> id = std::nullopt;
    /// Symbol.
    std::optional<std::string> symbol = std::nullopt;
    /// Recv Window.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryOrderParams {
    /// Symbol.
    common::Required<std::string> symbol;
    /// Id.
    std::optional<std::string> id = std::nullopt;
    /// Order Id.
    std::optional<std::int64_t> order_id = std::nullopt;
    /// Orig Client Order Id.
    std::optional<std::string> orig_client_order_id = std::nullopt;
    /// Recv Window.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT TradeApi {
public:
    explicit TradeApi(std::shared_ptr<common::WebsocketApi> client);

    /// Cancel Algo Order (TRADE)
    ///
    /// `algoOrder.cancel`.
    ///
    /// Cancel an active algo order.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Either `algoId` or `clientAlgoId` must be sent.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-api/trade#cancel-algo-order
    [[nodiscard]] common::WebsocketApiResponse<CancelAlgoOrderResponseResult>
    cancel_algo_order(const CancelAlgoOrderParams& params = {}) const;

    /// Asynchronous `cancel_algo_order()`. Completes with
    /// `void(std::exception_ptr, common::WebsocketApiResponse<CancelAlgoOrderResponseResult>)`.
    template <class CompletionToken>
    auto async_cancel_algo_order(const CancelAlgoOrderParams& params,
                                 CompletionToken&& token) const {
        return common::async_send<CancelAlgoOrderResponseResult>(
            client_, "algoOrder.cancel", cancel_algo_order_payload(params),
            make_options(false, true, false, false), std::forward<CompletionToken>(token));
    }

    /// Cancel Order (TRADE)
    ///
    /// `order.cancel`.
    ///
    /// Cancel an active order.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Either `orderId` or `origClientOrderId` must be sent.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-api/trade#cancel-order
    [[nodiscard]] common::WebsocketApiResponse<CancelOrderResponseResult>
    cancel_order(const CancelOrderParams& params) const;

    /// Asynchronous `cancel_order()`. Completes with
    /// `void(std::exception_ptr, common::WebsocketApiResponse<CancelOrderResponseResult>)`.
    template <class CompletionToken>
    auto async_cancel_order(const CancelOrderParams& params, CompletionToken&& token) const {
        return common::async_send<CancelOrderResponseResult>(
            client_, "order.cancel", cancel_order_payload(params),
            make_options(false, true, false, false), std::forward<CompletionToken>(token));
    }

    /// Modify Order (TRADE)
    ///
    /// `order.modify`.
    ///
    /// Order modify function, currently only LIMIT order modification is supported, modified orders
    /// will be reordered in the match queue
    ///
    /// Weight: 1 on 10s order rate limit(X-MBX-ORDER-COUNT-10S);
    /// 1 on 1min order rate limit(X-MBX-ORDER-COUNT-1M);
    /// 0 on IP rate limit(x-mbx-used-weight-1m)
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Either `orderId` or `origClientOrderId` must be sent, and the
    /// `orderId` will prevail if both are sent.
    ///
    /// - Both `quantity` and `price` must be sent. *(After CM migration, the dapi modify order
    /// endpoint follows the same rule.)*
    ///
    /// - When the new `quantity` or `price` doesn't satisfy PRICE_FILTER /
    /// PERCENT_FILTER / LOT_SIZE, amendment will be rejected and the order will
    /// stay as it is.
    ///
    /// - However the order will be cancelled by the amendment in the following
    /// situations:
    ///
    /// - when the order is in partially filled status and the new `quantity` <=
    /// `executedQty`
    ///
    /// - When the order is `GTX` and the new price will cause it to be executed
    /// immediately
    ///
    /// - One order can only be modfied for less than 10000 times
    ///
    /// - `reduceOnly` behavior:
    ///   - `false` or omitted: behave as today — `min_notional` is enforced on the modified order.
    ///   - `true` and the original order's `reduceOnly` attribute is also `true` (consistent): the
    ///   `min_notional` check is skipped on the modified order, matching placement semantics.
    ///   - `true` but the original order's `reduceOnly` attribute is `false` (inconsistent): the
    ///   modify request is rejected with error code `-5047`, "The original order is not a
    ///   reduce-only order".
    ///   - `reduceOnly` is used purely for validation — passing `true` does not change the original
    ///   order's `reduceOnly` attribute; that flag remains whatever it was set to at placement
    ///   time.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-api/trade#modify-order
    [[nodiscard]] common::WebsocketApiResponse<ModifyOrderResponseResult>
    modify_order(const ModifyOrderParams& params) const;

    /// Asynchronous `modify_order()`. Completes with
    /// `void(std::exception_ptr, common::WebsocketApiResponse<ModifyOrderResponseResult>)`.
    template <class CompletionToken>
    auto async_modify_order(const ModifyOrderParams& params, CompletionToken&& token) const {
        return common::async_send<ModifyOrderResponseResult>(
            client_, "order.modify", modify_order_payload(params),
            make_options(false, true, false, false), std::forward<CompletionToken>(token));
    }

    /// New Algo Order (TRADE)
    ///
    /// `algoOrder.place`.
    ///
    /// Send in a new algo order.
    ///
    /// Weight(IP): 0
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Condition orders will be triggered when:
    ///
    /// >
    ///
    /// - If parameter`priceProtect`is sent as true:
    ///
    /// - when price reaches the `triggerPrice` ，the difference rate between
    /// "MARK_PRICE" and "CONTRACT_PRICE" cannot be larger than the
    /// "triggerProtect" of the symbol
    ///
    /// - "triggerProtect" of a symbol can be got from `GET
    /// /fapi/v1/exchangeInfo`
    ///
    /// >
    ///
    /// - `STOP`, `STOP_MARKET`:
    ///
    /// - BUY: latest price ("MARK_PRICE" or "CONTRACT_PRICE") >= `triggerPrice`
    ///
    /// - SELL: latest price ("MARK_PRICE" or "CONTRACT_PRICE") <=
    /// `triggerPrice`
    ///
    /// - `TAKE_PROFIT`, `TAKE_PROFIT_MARKET`:
    ///
    /// - BUY: latest price ("MARK_PRICE" or "CONTRACT_PRICE") <= `triggerPrice`
    ///
    /// - SELL: latest price ("MARK_PRICE" or "CONTRACT_PRICE") >=
    /// `triggerPrice`
    ///
    /// - `TRAILING_STOP_MARKET`:
    ///
    /// - BUY: the lowest price after order placed <= `activatePrice`, and the
    /// latest price >= the lowest price * (1 + `callbackRate`)
    ///
    /// - SELL: the highest price after order placed >= `activatePrice`, and the
    /// latest price <= the highest price * (1 - `callbackRate`)
    ///
    /// >
    ///
    /// - For `TRAILING_STOP_MARKET`, if you got such error code.
    ///
    /// >   ``{"code": -2021, "msg": "Order would immediately trigger."}``
    ///
    /// >   means that the parameters you send do not meet the following
    /// requirements:
    ///
    /// - BUY: `activatePrice` should be smaller than latest price.
    ///
    /// - SELL: `activatePrice` should be larger than latest price.
    ///
    /// >
    ///
    /// - `STOP_MARKET`, `TAKE_PROFIT_MARKET` with `closePosition`=`true`:
    ///
    /// - Follow the same rules for condition orders.
    ///
    /// - If triggered，**close all** current long position( if `SELL`) or
    /// current short position( if `BUY`).
    ///
    /// - Cannot be used with `quantity` paremeter
    ///
    /// - Cannot be used with `reduceOnly` parameter
    ///
    /// - In Hedge Mode,cannot be used with `BUY` orders in `LONG` position
    /// side. and cannot be used with `SELL` orders in `SHORT` position side
    ///
    /// - `selfTradePreventionMode` is only effective when `timeInForce` set to
    /// `IOC` or `GTC` or `GTD`.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-api/trade#new-algo-order
    [[nodiscard]] common::WebsocketApiResponse<NewAlgoOrderResponseResult>
    new_algo_order(const NewAlgoOrderParams& params) const;

    /// Asynchronous `new_algo_order()`. Completes with
    /// `void(std::exception_ptr, common::WebsocketApiResponse<NewAlgoOrderResponseResult>)`.
    template <class CompletionToken>
    auto async_new_algo_order(const NewAlgoOrderParams& params, CompletionToken&& token) const {
        return common::async_send<NewAlgoOrderResponseResult>(
            client_, "algoOrder.place", new_algo_order_payload(params),
            make_options(false, true, false, false), std::forward<CompletionToken>(token));
    }

    /// New Order (TRADE)
    ///
    /// `order.place`.
    ///
    /// Send in a new order.
    ///
    /// Weight(IP): 0
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// Additional mandatory parameters based on `type`:
    ///
    /// - `LIMIT`: `timeInForce`, `quantity`, `price`
    /// - `MARKET`: `quantity`
    ///
    /// > * If `newOrderRespType` is sent as `RESULT`:
    /// >   * `MARKET` order: the final FILLED result of the order will be return directly.
    /// >   * `LIMIT` order with special `timeInForce`: the final status result of the order(FILLED
    /// or EXPIRED) will be returned directly.
    /// >
    /// > * `selfTradePreventionMode` is only effective when `timeInForce` set to `IOC` or `GTC` or
    /// `GTD`. > * In extreme market conditions, timeInForce `GTD` order auto cancel time might be
    /// delayed comparing to `goodTillDate`
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-api/trade#new-order
    [[nodiscard]] common::WebsocketApiResponse<NewOrderResponseResult>
    new_order(const NewOrderParams& params) const;

    /// Asynchronous `new_order()`. Completes with
    /// `void(std::exception_ptr, common::WebsocketApiResponse<NewOrderResponseResult>)`.
    template <class CompletionToken>
    auto async_new_order(const NewOrderParams& params, CompletionToken&& token) const {
        return common::async_send<NewOrderResponseResult>(
            client_, "order.place", new_order_payload(params),
            make_options(false, true, false, false), std::forward<CompletionToken>(token));
    }

    /// Position Information (USER_DATA)
    ///
    /// `account.position`.
    ///
    /// Get current position information.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Please use with user data stream `ACCOUNT_UPDATE` to meet your
    /// timeliness and accuracy needs.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-api/trade#position-information
    [[nodiscard]] common::WebsocketApiResponse<std::vector<PositionInformationResponseResultInner>>
    position_information(const PositionInformationParams& params = {}) const;

    /// Asynchronous `position_information()`. Completes with
    /// `void(std::exception_ptr,
    /// common::WebsocketApiResponse<std::vector<PositionInformationResponseResultInner>>)`.
    template <class CompletionToken>
    auto async_position_information(const PositionInformationParams& params,
                                    CompletionToken&& token) const {
        return common::async_send<std::vector<PositionInformationResponseResultInner>>(
            client_, "account.position", position_information_payload(params),
            make_options(false, true, false, false), std::forward<CompletionToken>(token));
    }

    /// Position Information V2 (USER_DATA)
    ///
    /// `v2/account.position`.
    ///
    /// Get current position information(only symbol that has position or open
    /// orders will be returned).
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Please use with user data stream `ACCOUNT_UPDATE` to meet your
    /// timeliness and accuracy needs.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-api/trade#position-information-v2
    [[nodiscard]] common::WebsocketApiResponse<
        std::vector<PositionInformationV2ResponseResultInner>>
    position_information_v2(const PositionInformationV2Params& params = {}) const;

    /// Asynchronous `position_information_v2()`. Completes with
    /// `void(std::exception_ptr,
    /// common::WebsocketApiResponse<std::vector<PositionInformationV2ResponseResultInner>>)`.
    template <class CompletionToken>
    auto async_position_information_v2(const PositionInformationV2Params& params,
                                       CompletionToken&& token) const {
        return common::async_send<std::vector<PositionInformationV2ResponseResultInner>>(
            client_, "v2/account.position", position_information_v2_payload(params),
            make_options(false, true, false, false), std::forward<CompletionToken>(token));
    }

    /// Query Order (USER_DATA)
    ///
    /// `order.status`.
    ///
    /// Check an order's status.
    ///
    /// * These orders will not be found:
    ///   * order status is `CANCELED` or `EXPIRED` **AND** order has NO filled trade **AND**
    ///   created time + 3 days < current time
    ///   * order create time + 90 days < current time
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// Notes:
    /// - Either `orderId` or `origClientOrderId` must be sent.
    /// - `orderId` is self-increment for each specific `symbol`
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-api/trade#query-order
    [[nodiscard]] common::WebsocketApiResponse<QueryOrderResponseResult>
    query_order(const QueryOrderParams& params) const;

    /// Asynchronous `query_order()`. Completes with
    /// `void(std::exception_ptr, common::WebsocketApiResponse<QueryOrderResponseResult>)`.
    template <class CompletionToken>
    auto async_query_order(const QueryOrderParams& params, CompletionToken&& token) const {
        return common::async_send<QueryOrderResponseResult>(
            client_, "order.status", query_order_payload(params),
            make_options(false, true, false, false), std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] static common::Params
    cancel_algo_order_payload(const CancelAlgoOrderParams& params);
    [[nodiscard]] static common::Params cancel_order_payload(const CancelOrderParams& params);
    [[nodiscard]] static common::Params modify_order_payload(const ModifyOrderParams& params);
    [[nodiscard]] static common::Params new_algo_order_payload(const NewAlgoOrderParams& params);
    [[nodiscard]] static common::Params new_order_payload(const NewOrderParams& params);
    [[nodiscard]] static common::Params
    position_information_payload(const PositionInformationParams& params);
    [[nodiscard]] static common::Params
    position_information_v2_payload(const PositionInformationV2Params& params);
    [[nodiscard]] static common::Params query_order_payload(const QueryOrderParams& params);
    [[nodiscard]] static common::WebsocketMessageSendOptions
    make_options(bool with_api_key, bool is_signed, bool is_session_logon, bool is_session_logout) {
        common::WebsocketMessageSendOptions options;
        options.with_api_key = with_api_key;
        options.is_signed = is_signed;
        options.is_session_logon = is_session_logon;
        options.is_session_logout = is_session_logout;
        return options;
    }

    std::shared_ptr<common::WebsocketApi> client_;
};

} // namespace binance::derivatives_trading_usds_futures::websocket_api
