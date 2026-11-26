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
#include <binance/common/rest.hpp>
#include <binance/derivatives_trading_usds_futures/export.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/account_trade_list_response_inner.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/all_orders_response_inner.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/auto_cancel_all_open_orders_response.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/cancel_algo_order_response.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/cancel_all_algo_open_orders_response.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/cancel_all_open_orders_response.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/cancel_multiple_orders_response_inner.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/cancel_order_response.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/change_initial_leverage_response.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/change_margin_type_response.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/change_multi_assets_mode_response.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/change_position_mode_response.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/current_all_algo_open_orders_response_inner.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/current_all_open_orders_response_inner.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/futures_tradfi_perps_contract_response.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/get_order_modify_history_response_inner.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/get_position_margin_change_history_response_inner.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/modify_isolated_position_margin_response.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/modify_multiple_orders_batch_orders_parameter_inner.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/modify_multiple_orders_response_inner.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/modify_order_response.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/new_algo_order_response.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/new_order_response.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/place_multiple_orders_batch_orders_parameter_inner.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/place_multiple_orders_response_inner.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/position_adl_quantile_estimation_response_inner.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/position_information_v2_response_inner.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/position_information_v3_response_inner.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/query_algo_order_response.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/query_all_algo_orders_response_inner.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/query_current_open_order_response.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/query_order_response.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/test_order_response.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/users_force_orders_response_inner.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

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
to_string(NewAlgoOrderTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT NewAlgoOrderTypeEnum
tag_invoke(boost::json::value_to_tag<NewAlgoOrderTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv, NewAlgoOrderTypeEnum value);

enum class NewAlgoOrderTimeInForceEnum {
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
    Stop,
    StopMarket,
    TakeProfit,
    TakeProfitMarket,
    TrailingStopMarket,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(NewOrderTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT NewOrderTypeEnum
tag_invoke(boost::json::value_to_tag<NewOrderTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv, NewOrderTypeEnum value);

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

enum class ChangeMarginTypeMarginTypeEnum {
    Isolated,
    Crossed,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(ChangeMarginTypeMarginTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT ChangeMarginTypeMarginTypeEnum
tag_invoke(boost::json::value_to_tag<ChangeMarginTypeMarginTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           ChangeMarginTypeMarginTypeEnum value);

enum class TestOrderSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(TestOrderSideEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT TestOrderSideEnum
tag_invoke(boost::json::value_to_tag<TestOrderSideEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv, TestOrderSideEnum value);

enum class TestOrderTypeEnum {
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
to_string(TestOrderTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT TestOrderTypeEnum
tag_invoke(boost::json::value_to_tag<TestOrderTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv, TestOrderTypeEnum value);

enum class TestOrderPositionSideEnum {
    Both,
    Long,
    Short,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(TestOrderPositionSideEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT TestOrderPositionSideEnum tag_invoke(
    boost::json::value_to_tag<TestOrderPositionSideEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                                boost::json::value& jv,
                                                                TestOrderPositionSideEnum value);

enum class TestOrderReduceOnlyEnum {
    True_,
    False_,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(TestOrderReduceOnlyEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT TestOrderReduceOnlyEnum tag_invoke(
    boost::json::value_to_tag<TestOrderReduceOnlyEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                                boost::json::value& jv,
                                                                TestOrderReduceOnlyEnum value);

enum class TestOrderClosePositionEnum {
    True_,
    False_,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(TestOrderClosePositionEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT TestOrderClosePositionEnum tag_invoke(
    boost::json::value_to_tag<TestOrderClosePositionEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                                boost::json::value& jv,
                                                                TestOrderClosePositionEnum value);

enum class TestOrderTimeInForceEnum {
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
to_string(TestOrderTimeInForceEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT TestOrderTimeInForceEnum tag_invoke(
    boost::json::value_to_tag<TestOrderTimeInForceEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                                boost::json::value& jv,
                                                                TestOrderTimeInForceEnum value);

enum class TestOrderWorkingTypeEnum {
    MarkPrice,
    ContractPrice,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(TestOrderWorkingTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT TestOrderWorkingTypeEnum tag_invoke(
    boost::json::value_to_tag<TestOrderWorkingTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                                boost::json::value& jv,
                                                                TestOrderWorkingTypeEnum value);

enum class TestOrderPriceProtectEnum {
    True_,
    False_,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(TestOrderPriceProtectEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT TestOrderPriceProtectEnum tag_invoke(
    boost::json::value_to_tag<TestOrderPriceProtectEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                                boost::json::value& jv,
                                                                TestOrderPriceProtectEnum value);

enum class TestOrderNewOrderRespTypeEnum {
    Ack,
    Result,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(TestOrderNewOrderRespTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT TestOrderNewOrderRespTypeEnum tag_invoke(
    boost::json::value_to_tag<TestOrderNewOrderRespTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           TestOrderNewOrderRespTypeEnum value);

enum class TestOrderPriceMatchEnum {
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
to_string(TestOrderPriceMatchEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT TestOrderPriceMatchEnum tag_invoke(
    boost::json::value_to_tag<TestOrderPriceMatchEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                                boost::json::value& jv,
                                                                TestOrderPriceMatchEnum value);

enum class TestOrderSelfTradePreventionModeEnum {
    None_,
    ExpireTaker,
    ExpireBoth,
    ExpireMaker,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(TestOrderSelfTradePreventionModeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT TestOrderSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<TestOrderSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           TestOrderSelfTradePreventionModeEnum value);

enum class UsersForceOrdersAutoCloseTypeEnum {
    Liquidation,
    Adl,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(UsersForceOrdersAutoCloseTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT UsersForceOrdersAutoCloseTypeEnum
tag_invoke(boost::json::value_to_tag<UsersForceOrdersAutoCloseTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           UsersForceOrdersAutoCloseTypeEnum value);

struct AccountTradeListParams {
    common::Required<std::string> symbol;
    /// Must be used together with parameter `symbol`.
    std::optional<std::int64_t> order_id = std::nullopt;
    /// Start time
    std::optional<std::int64_t> start_time = std::nullopt;
    /// End time
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Trade id to fetch from. Default gets most recent trades.
    std::optional<std::int64_t> from_id = std::nullopt;
    std::optional<std::int64_t> limit = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct AllOrdersParams {
    std::optional<std::string> symbol = std::nullopt;
    std::optional<std::int64_t> order_id = std::nullopt;
    /// Start time
    std::optional<std::int64_t> start_time = std::nullopt;
    /// End time
    std::optional<std::int64_t> end_time = std::nullopt;
    std::optional<std::int64_t> limit = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct AutoCancelAllOpenOrdersParams {
    common::Required<std::string> symbol;
    /// Countdown in milliseconds. `1000` means 1 second; `0` disables countdown cancel-all.
    common::Required<std::int64_t> countdown_time;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct CancelAlgoOrderParams {
    std::optional<std::int64_t> algo_id = std::nullopt;
    std::optional<std::string> client_algo_id = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct NewAlgoOrderParams {
    common::Required<NewAlgoOrderAlgoTypeEnum> algo_type;
    common::Required<std::string> symbol;
    common::Required<NewAlgoOrderSideEnum> side;
    common::Required<NewAlgoOrderTypeEnum> type;
    /// Default `BOTH` for One-way Mode ; `LONG` or `SHORT` for Hedge Mode. It must be sent in Hedge
    /// Mode.
    std::optional<std::string> position_side = std::nullopt;
    std::optional<NewAlgoOrderTimeInForceEnum> time_in_force = std::nullopt;
    /// Cannot be sent with `closePosition`=`true`(Close-All)
    std::optional<common::Decimal> quantity = std::nullopt;
    std::optional<common::Decimal> price = std::nullopt;
    /// Trigger price
    std::optional<common::Decimal> trigger_price = std::nullopt;
    std::optional<NewAlgoOrderWorkingTypeEnum> working_type = std::nullopt;
    /// only avaliable for `LIMIT`/`STOP`/`TAKE_PROFIT` order; Can't be passed together with `price`
    std::optional<NewAlgoOrderPriceMatchEnum> price_match = std::nullopt;
    /// Close-All，used with `STOP_MARKET` or `TAKE_PROFIT_MARKET`.
    std::optional<NewAlgoOrderClosePositionEnum> close_position = std::nullopt;
    /// Used with `STOP_MARKET` or `TAKE_PROFIT_MARKET` order. when price reaches the triggerPrice
    /// ，the difference rate between "MARK_PRICE" and "CONTRACT_PRICE" cannot be larger than the
    /// Price Protection Threshold of the symbol.'
    std::optional<NewAlgoOrderPriceProtectEnum> price_protect = std::nullopt;
    /// Cannot be sent in Hedge Mode; cannot be sent with `closePosition`=`true`'
    std::optional<NewAlgoOrderReduceOnlyEnum> reduce_only = std::nullopt;
    /// Used with `TRAILING_STOP_MARKET` orders, default as the latest price(supporting different
    /// `workingType`)
    std::optional<common::Decimal> activate_price = std::nullopt;
    /// Used with `TRAILING_STOP_MARKET` orders
    std::optional<common::Decimal> callback_rate = std::nullopt;
    /// A unique id among open orders. Automatically generated if not sent. Can only be string
    /// following the rule: `^[\.A-Z\:/a-z0-9_-]{1,36}$`
    std::optional<std::string> client_algo_id = std::nullopt;
    std::optional<NewAlgoOrderNewOrderRespTypeEnum> new_order_resp_type = std::nullopt;
    /// `EXPIRE_TAKER`: expire taker order when STP triggers / `EXPIRE_MAKER`: expire taker order
    /// when STP triggers/ `EXPIRE_BOTH`: expire both orders when STP triggers; default `NONE`
    std::optional<NewAlgoOrderSelfTradePreventionModeEnum> self_trade_prevention_mode =
        std::nullopt;
    /// order cancel time for timeInForce `GTD`, mandatory when `timeInforce` set to `GTD`; order
    /// the timestamp only retains second-level precision, ms part will be ignored; The goodTillDate
    /// timestamp must be greater than the current time plus 600 seconds and smaller than
    /// 253402300799000
    std::optional<std::int64_t> good_till_date = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryAlgoOrderParams {
    /// Order ID
    std::optional<std::int64_t> algo_id = std::nullopt;
    /// Client order ID
    std::optional<std::string> client_algo_id = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct CancelAllAlgoOpenOrdersParams {
    common::Required<std::string> symbol;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct CancelAllOpenOrdersParams {
    common::Required<std::string> symbol;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct CancelMultipleOrdersParams {
    common::Required<std::string> symbol;
    std::optional<std::vector<std::int64_t>> order_id_list = std::nullopt;
    std::optional<std::vector<std::string>> orig_client_order_id_list = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct ModifyMultipleOrdersParams {
    /// order list. Max 5 orders
    common::Required<std::vector<ModifyMultipleOrdersBatchOrdersParameterInner>> batch_orders;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct PlaceMultipleOrdersParams {
    /// order list. Max 5 orders
    common::Required<std::vector<PlaceMultipleOrdersBatchOrdersParameterInner>> batch_orders;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct CancelOrderParams {
    common::Required<std::string> symbol;
    std::optional<std::int64_t> order_id = std::nullopt;
    std::optional<std::string> orig_client_order_id = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct ModifyOrderParams {
    common::Required<std::string> symbol;
    common::Required<ModifyOrderSideEnum> side;
    /// Order quantity, cannot be sent with `closePosition=true`
    common::Required<common::Decimal> quantity;
    common::Required<common::Decimal> price;
    std::optional<std::int64_t> order_id = std::nullopt;
    std::optional<std::string> orig_client_order_id = std::nullopt;
    /// only avaliable for `LIMIT`/`STOP`/`TAKE_PROFIT` order; Can't be passed together with `price`
    std::optional<ModifyOrderPriceMatchEnum> price_match = std::nullopt;
    /// User-defined modification identifier, returned as-is in the response. Optional; not
    /// validated for uniqueness.
    std::optional<std::int64_t> modify_id = std::nullopt;
    /// See notes below for behavior.
    std::optional<ModifyOrderReduceOnlyEnum> reduce_only = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct NewOrderParams {
    common::Required<std::string> symbol;
    common::Required<NewOrderSideEnum> side;
    /// Order type
    common::Required<NewOrderTypeEnum> type;
    /// Default `BOTH` for One-way Mode ; `LONG` or `SHORT` for Hedge Mode. It must be sent in Hedge
    /// Mode.
    std::optional<std::string> position_side = std::nullopt;
    std::optional<NewOrderTimeInForceEnum> time_in_force = std::nullopt;
    /// Cannot be sent in Hedge Mode
    std::optional<NewOrderReduceOnlyEnum> reduce_only = std::nullopt;
    std::optional<common::Decimal> quantity = std::nullopt;
    std::optional<common::Decimal> price = std::nullopt;
    /// A unique id among open orders. Automatically generated if not sent. Can only be string
    /// following the rule: `^[\.A-Z\:/a-z0-9_-]{1,36}$`
    std::optional<std::string> new_client_order_id = std::nullopt;
    std::optional<NewOrderNewOrderRespTypeEnum> new_order_resp_type = std::nullopt;
    /// only avaliable for `LIMIT`/`STOP`/`TAKE_PROFIT` order; Can't be passed together with `price`
    std::optional<NewOrderPriceMatchEnum> price_match = std::nullopt;
    /// `EXPIRE_TAKER`: expire taker order when STP triggers/ `EXPIRE_MAKER`: expire taker order
    /// when STP triggers/ `EXPIRE_BOTH`: expire both orders when STP triggers; default
    /// `EXPIRE_MAKER`
    std::optional<NewOrderSelfTradePreventionModeEnum> self_trade_prevention_mode = std::nullopt;
    /// order cancel time for timeInForce `GTD`, mandatory when `timeInforce` set to `GTD`; order
    /// the timestamp only retains second-level precision, ms part will be ignored; The goodTillDate
    /// timestamp must be greater than the current time plus 600 seconds and smaller than
    /// 253402300799000
    std::optional<std::int64_t> good_till_date = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryOrderParams {
    common::Required<std::string> symbol;
    std::optional<std::int64_t> order_id = std::nullopt;
    std::optional<std::string> orig_client_order_id = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct ChangeInitialLeverageParams {
    common::Required<std::string> symbol;
    /// Target initial leverage. The maximum is symbol-specific: use `initialLeverage` of bracket 1
    /// from `GET /fapi/v1/leverageBracket`.
    common::Required<std::int64_t> leverage;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct ChangeMarginTypeParams {
    common::Required<std::string> symbol;
    common::Required<ChangeMarginTypeMarginTypeEnum> margin_type;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct ChangeMultiAssetsModeParams {
    /// "true": Multi-Assets Mode; "false": Single-Asset Mode
    common::Required<std::string> multi_assets_margin;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct ChangePositionModeParams {
    /// "true": Hedge Mode; "false": One-way Mode
    common::Required<std::string> dual_side_position;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct CurrentAllAlgoOpenOrdersParams {
    std::optional<std::string> algo_type = std::nullopt;
    std::optional<std::string> symbol = std::nullopt;
    std::optional<std::int64_t> algo_id = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct CurrentAllOpenOrdersParams {
    std::optional<std::string> symbol = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct FuturesTradfiPerpsContractParams {
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetOrderModifyHistoryParams {
    common::Required<std::string> symbol;
    std::optional<std::int64_t> order_id = std::nullopt;
    std::optional<std::string> orig_client_order_id = std::nullopt;
    /// Timestamp in ms to get modification history from INCLUSIVE
    std::optional<std::int64_t> start_time = std::nullopt;
    /// Timestamp in ms to get modification history until INCLUSIVE
    std::optional<std::int64_t> end_time = std::nullopt;
    std::optional<std::int64_t> limit = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetPositionMarginChangeHistoryParams {
    common::Required<std::string> symbol;
    /// 1: Add position margin，2: Reduce position margin
    std::optional<std::string> type = std::nullopt;
    /// Start time
    std::optional<std::int64_t> start_time = std::nullopt;
    /// time if not pass
    std::optional<std::int64_t> end_time = std::nullopt;
    std::optional<std::int64_t> limit = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct ModifyIsolatedPositionMarginParams {
    common::Required<std::string> symbol;
    /// Margin asset
    common::Required<common::Decimal> amount;
    /// 1: Add position margin，2: Reduce position margin
    common::Required<std::int64_t> type;
    /// Default `BOTH` for One-way Mode ; `LONG` or `SHORT` for Hedge Mode. It must be sent with
    /// Hedge Mode.
    std::optional<std::string> position_side = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct PositionAdlQuantileEstimationParams {
    std::optional<std::string> symbol = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct PositionInformationV2Params {
    std::optional<std::string> symbol = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct PositionInformationV3Params {
    std::optional<std::string> symbol = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryAllAlgoOrdersParams {
    /// Symbol
    common::Required<std::string> symbol;
    std::optional<std::int64_t> algo_id = std::nullopt;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    std::optional<std::int64_t> limit = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryCurrentOpenOrderParams {
    common::Required<std::string> symbol;
    std::optional<std::int64_t> order_id = std::nullopt;
    std::optional<std::string> orig_client_order_id = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct TestOrderParams {
    common::Required<std::string> symbol;
    common::Required<TestOrderSideEnum> side;
    common::Required<TestOrderTypeEnum> type;
    /// Default `BOTH` for One-way Mode ; `LONG` or `SHORT` for Hedge Mode. It must be sent in Hedge
    /// Mode.
    std::optional<TestOrderPositionSideEnum> position_side = std::nullopt;
    /// Cannot be sent in Hedge Mode; cannot be sent with `closePosition`=`true`
    std::optional<TestOrderReduceOnlyEnum> reduce_only = std::nullopt;
    /// Cannot be sent with `closePosition`=`true`(Close-All)
    std::optional<common::Decimal> quantity = std::nullopt;
    std::optional<common::Decimal> price = std::nullopt;
    /// A unique id among open orders. Automatically generated if not sent. Can only be string
    /// following the rule: `^[\.A-Z\:/a-z0-9_-]{1,36}$`
    std::optional<std::string> new_client_order_id = std::nullopt;
    /// Used with `STOP/STOP_MARKET` or `TAKE_PROFIT/TAKE_PROFIT_MARKET` orders.
    std::optional<common::Decimal> stop_price = std::nullopt;
    /// Close-All，used with `STOP_MARKET` or `TAKE_PROFIT_MARKET`."
    std::optional<TestOrderClosePositionEnum> close_position = std::nullopt;
    /// Used with `TRAILING_STOP_MARKET` orders, default as the latest price(supporting different
    /// `workingType`)
    std::optional<common::Decimal> activation_price = std::nullopt;
    /// Used with `TRAILING_STOP_MARKET` orders
    std::optional<common::Decimal> callback_rate = std::nullopt;
    std::optional<TestOrderTimeInForceEnum> time_in_force = std::nullopt;
    std::optional<TestOrderWorkingTypeEnum> working_type = std::nullopt;
    std::optional<TestOrderPriceProtectEnum> price_protect = std::nullopt;
    std::optional<TestOrderNewOrderRespTypeEnum> new_order_resp_type = std::nullopt;
    /// only avaliable for `LIMIT`/`STOP`/`TAKE_PROFIT` order; Can't be passed together with `price`
    std::optional<TestOrderPriceMatchEnum> price_match = std::nullopt;
    /// `NONE`: No STP / `EXPIRE_TAKER`: expire taker order when STP triggers/ `EXPIRE_MAKER`:
    /// expire taker order when STP triggers/ `EXPIRE_BOTH`: expire both orders when STP triggers;
    /// default `NONE`
    std::optional<TestOrderSelfTradePreventionModeEnum> self_trade_prevention_mode = std::nullopt;
    /// order cancel time for timeInForce `GTD`, mandatory when `timeInforce` set to `GTD`; order
    /// the timestamp only retains second-level precision, ms part will be ignored; The goodTillDate
    /// timestamp must be greater than the current time plus 600 seconds and smaller than
    /// 253402300799000
    std::optional<std::int64_t> good_till_date = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct UsersForceOrdersParams {
    std::optional<std::string> symbol = std::nullopt;
    /// "LIQUIDATION" for liquidation orders, "ADL" for ADL orders.
    std::optional<UsersForceOrdersAutoCloseTypeEnum> auto_close_type = std::nullopt;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    std::optional<std::int64_t> limit = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT TradeApi {
public:
    explicit TradeApi(std::shared_ptr<common::RestClient> client);

    /// Account Trade List (USER_DATA)
    ///
    /// GET /fapi/v1/userTrades.
    ///
    /// Get trades for a specific account and symbol.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If `startTime` and `endTime` are both not sent, then the last 7 days' data will be
    /// returned.
    /// - The time between `startTime` and `endTime` cannot be longer than 7 days.
    /// - The parameter `fromId` cannot be sent with `startTime` or `endTime`.
    /// - Only support querying trade in the past 3 months
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/trade#account-trade-list
    [[nodiscard]] common::RestApiResponse<std::vector<AccountTradeListResponseInner>>
    account_trade_list(const AccountTradeListParams& params) const;

    /// Asynchronous `account_trade_list()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<AccountTradeListResponseInner>>)`.
    template <class CompletionToken>
    auto async_account_trade_list(const AccountTradeListParams& params,
                                  CompletionToken&& token) const {
        return common::async_send<std::vector<AccountTradeListResponseInner>>(
            client_, account_trade_list_request(params), std::forward<CompletionToken>(token));
    }

    /// All Orders (USER_DATA)
    ///
    /// GET /fapi/v1/allOrders.
    ///
    /// Get all account orders; active, canceled, or filled.
    ///
    /// - These orders will not be found:
    ///   - order status is `CANCELED` or `EXPIRED` **AND** order has NO filled trade **AND**
    ///   created time + 3 days < current time
    ///   - order create time + 90 days < current time
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If `orderId` is set, it will get orders >= that `orderId`. Otherwise most recent orders
    /// are returned.
    /// - The query time period must be less then 7 days( default as the recent 7 days).
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/trade#all-orders
    [[nodiscard]] common::RestApiResponse<std::vector<AllOrdersResponseInner>>
    all_orders(const AllOrdersParams& params = {}) const;

    /// Asynchronous `all_orders()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<std::vector<AllOrdersResponseInner>>)`.
    template <class CompletionToken>
    auto async_all_orders(const AllOrdersParams& params, CompletionToken&& token) const {
        return common::async_send<std::vector<AllOrdersResponseInner>>(
            client_, all_orders_request(params), std::forward<CompletionToken>(token));
    }

    /// Auto-Cancel All Open Orders (TRADE)
    ///
    /// POST /fapi/v1/countdownCancelAll.
    ///
    /// Cancel all open orders of the specified symbol at the end of the specified countdown.
    ///
    /// The endpoint should be called repeatedly as heartbeats so that the existing countdown time
    /// can be canceled and replaced by a new one.
    ///
    /// Example usage:
    ///
    /// Call this endpoint at 30s intervals with an countdownTime of 120000 (120s).
    /// If this endpoint is not called within 120 seconds, all your orders of the specified symbol
    /// will be automatically canceled. If this endpoint is called with an countdownTime of 0, the
    /// countdown timer will be stopped.
    ///
    /// The system will check all countdowns **approximately every 10 milliseconds**, so please note
    /// that sufficient redundancy should be considered when using this function. We do not
    /// recommend setting the countdown time to be too precise or too small.
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/trade#auto-cancel-all-open-orders
    [[nodiscard]] common::RestApiResponse<AutoCancelAllOpenOrdersResponse>
    auto_cancel_all_open_orders(const AutoCancelAllOpenOrdersParams& params) const;

    /// Asynchronous `auto_cancel_all_open_orders()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<AutoCancelAllOpenOrdersResponse>)`.
    template <class CompletionToken>
    auto async_auto_cancel_all_open_orders(const AutoCancelAllOpenOrdersParams& params,
                                           CompletionToken&& token) const {
        return common::async_send<AutoCancelAllOpenOrdersResponse>(
            client_, auto_cancel_all_open_orders_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Cancel Algo Order (TRADE)
    ///
    /// DELETE /fapi/v1/algoOrder.
    ///
    /// Cancel an active algo (conditional) order, including TP/SL (Take Profit / Stop Loss) and
    /// trailing stop orders on USD-M Futures.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Either `algoId` or `clientAlgoId` must be sent.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/trade#cancel-algo-order
    [[nodiscard]] common::RestApiResponse<CancelAlgoOrderResponse>
    cancel_algo_order(const CancelAlgoOrderParams& params = {}) const;

    /// Asynchronous `cancel_algo_order()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<CancelAlgoOrderResponse>)`.
    template <class CompletionToken>
    auto async_cancel_algo_order(const CancelAlgoOrderParams& params,
                                 CompletionToken&& token) const {
        return common::async_send<CancelAlgoOrderResponse>(
            client_, cancel_algo_order_request(params), std::forward<CompletionToken>(token));
    }

    /// New Algo Order (TRADE)
    ///
    /// POST /fapi/v1/algoOrder.
    ///
    /// Send in a new algo (conditional) order. Use this endpoint to place **TP/SL (Take Profit /
    /// Stop Loss)** and trailing stop orders on USD-M Futures. Supported order types under
    /// `algoType=CONDITIONAL` are `STOP_MARKET`, `TAKE_PROFIT_MARKET`, `STOP`, `TAKE_PROFIT`, and
    /// `TRAILING_STOP_MARKET`.
    ///
    /// Weight: 1 on 10s order rate limit(X-MBX-ORDER-COUNT-10S);
    /// 1 on 1min order rate limit(X-MBX-ORDER-COUNT-1M);
    /// 0 on IP rate limit(x-mbx-used-weight-1m)
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Algo order with type `STOP`, parameter `timeInForce` can be sent (default `GTC`).
    /// - Algo order with type `TAKE_PROFIT`, parameter `timeInForce` can be sent ( default `GTC`).
    /// - Condition orders will be triggered when:
    ///   - If parameter`priceProtect`is sent as true:
    ///     - when price reaches the `triggerPrice` ，the difference rate between "MARK_PRICE" and
    ///     "CONTRACT_PRICE" cannot be larger than the "triggerProtect" of the symbol
    ///     - "triggerProtect" of a symbol can be got from `GET /fapi/v1/exchangeInfo`
    ///   - `STOP`, `STOP_MARKET`:
    ///     - BUY: latest price ("MARK_PRICE" or "CONTRACT_PRICE") >= `triggerPrice`
    ///     - SELL: latest price ("MARK_PRICE" or "CONTRACT_PRICE") <= `triggerPrice`
    ///   - `TAKE_PROFIT`, `TAKE_PROFIT_MARKET`:
    ///     - BUY: latest price ("MARK_PRICE" or "CONTRACT_PRICE") <= `triggerPrice`
    ///     - SELL: latest price ("MARK_PRICE" or "CONTRACT_PRICE") >= `triggerPrice`
    ///   - `TRAILING_STOP_MARKET`:
    ///     - BUY: the lowest price after order placed <= `activatePrice`, and the latest price >=
    ///     the lowest price * (1 + `callbackRate`)
    ///     - SELL: the highest price after order placed >= `activatePrice`, and the latest price <=
    ///     the highest price * (1 - `callbackRate`)
    /// - For `TRAILING_STOP_MARKET`, if you got such error code. > `{"code": -2021, "msg": "Order
    /// would immediately trigger."}` > means that the parameters you send do not meet the following
    /// requirements:
    ///   - BUY: `activatePrice` should be smaller than latest price.
    ///   - SELL: `activatePrice` should be larger than latest price.
    /// - `STOP_MARKET`, `TAKE_PROFIT_MARKET` with `closePosition`=`true`:
    ///   - Follow the same rules for condition orders.
    ///   - If triggered，**close all** current long position( if `SELL`) or current short position(
    ///   if `BUY`).
    ///   - Cannot be used with `quantity` paremeter
    ///   - Cannot be used with `reduceOnly` parameter
    ///   - In Hedge Mode,cannot be used with `BUY` orders in `LONG` position side. and cannot be
    ///   used with `SELL` orders in `SHORT` position side
    /// - `selfTradePreventionMode` is only effective when `timeInForce` set to `IOC` or `GTC` or
    /// `GTD`.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/trade#new-algo-order
    [[nodiscard]] common::RestApiResponse<NewAlgoOrderResponse>
    new_algo_order(const NewAlgoOrderParams& params) const;

    /// Asynchronous `new_algo_order()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<NewAlgoOrderResponse>)`.
    template <class CompletionToken>
    auto async_new_algo_order(const NewAlgoOrderParams& params, CompletionToken&& token) const {
        return common::async_send<NewAlgoOrderResponse>(client_, new_algo_order_request(params),
                                                        std::forward<CompletionToken>(token));
    }

    /// Query Algo Order (USER_DATA)
    ///
    /// GET /fapi/v1/algoOrder.
    ///
    /// Check the status of an algo (conditional) order, such as TP/SL (Take Profit / Stop Loss) or
    /// trailing stop orders on USD-M Futures.
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
    /// - Either `algoId` or `clientAlgoId` must be sent.
    /// - `algoId` is self-increment for each specific `symbol`
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/trade#query-algo-order
    [[nodiscard]] common::RestApiResponse<QueryAlgoOrderResponse>
    query_algo_order(const QueryAlgoOrderParams& params = {}) const;

    /// Asynchronous `query_algo_order()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<QueryAlgoOrderResponse>)`.
    template <class CompletionToken>
    auto async_query_algo_order(const QueryAlgoOrderParams& params, CompletionToken&& token) const {
        return common::async_send<QueryAlgoOrderResponse>(client_, query_algo_order_request(params),
                                                          std::forward<CompletionToken>(token));
    }

    /// Cancel All Algo Open Orders (TRADE)
    ///
    /// DELETE /fapi/v1/algoOpenOrders.
    ///
    /// Cancel all open algo (conditional) orders on a symbol, including TP/SL (Take Profit / Stop
    /// Loss) and trailing stop orders on USD-M Futures.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/trade#cancel-all-algo-open-orders
    [[nodiscard]] common::RestApiResponse<CancelAllAlgoOpenOrdersResponse>
    cancel_all_algo_open_orders(const CancelAllAlgoOpenOrdersParams& params) const;

    /// Asynchronous `cancel_all_algo_open_orders()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<CancelAllAlgoOpenOrdersResponse>)`.
    template <class CompletionToken>
    auto async_cancel_all_algo_open_orders(const CancelAllAlgoOpenOrdersParams& params,
                                           CompletionToken&& token) const {
        return common::async_send<CancelAllAlgoOpenOrdersResponse>(
            client_, cancel_all_algo_open_orders_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Cancel All Open Orders (TRADE)
    ///
    /// DELETE /fapi/v1/allOpenOrders.
    ///
    /// Cancel All Open Orders
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/trade#cancel-all-open-orders
    [[nodiscard]] common::RestApiResponse<CancelAllOpenOrdersResponse>
    cancel_all_open_orders(const CancelAllOpenOrdersParams& params) const;

    /// Asynchronous `cancel_all_open_orders()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<CancelAllOpenOrdersResponse>)`.
    template <class CompletionToken>
    auto async_cancel_all_open_orders(const CancelAllOpenOrdersParams& params,
                                      CompletionToken&& token) const {
        return common::async_send<CancelAllOpenOrdersResponse>(
            client_, cancel_all_open_orders_request(params), std::forward<CompletionToken>(token));
    }

    /// Cancel Multiple Orders (TRADE)
    ///
    /// DELETE /fapi/v1/batchOrders.
    ///
    /// Cancel Multiple Orders
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Either `orderIdList` or `origClientOrderIdList ` must be sent.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/trade#cancel-multiple-orders
    [[nodiscard]] common::RestApiResponse<std::vector<CancelMultipleOrdersResponseInner>>
    cancel_multiple_orders(const CancelMultipleOrdersParams& params) const;

    /// Asynchronous `cancel_multiple_orders()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<CancelMultipleOrdersResponseInner>>)`.
    template <class CompletionToken>
    auto async_cancel_multiple_orders(const CancelMultipleOrdersParams& params,
                                      CompletionToken&& token) const {
        return common::async_send<std::vector<CancelMultipleOrdersResponseInner>>(
            client_, cancel_multiple_orders_request(params), std::forward<CompletionToken>(token));
    }

    /// Modify Multiple Orders (TRADE)
    ///
    /// PUT /fapi/v1/batchOrders.
    ///
    /// Modify Multiple Orders (TRADE)
    ///
    /// Weight: 5 on 10s order rate limit(X-MBX-ORDER-COUNT-10S);
    /// 1 on 1min order rate limit(X-MBX-ORDER-COUNT-1M);
    /// 5 on IP rate limit(x-mbx-used-weight-1m);
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Parameter rules are same with `Modify Order`
    /// - Batch modify orders are processed concurrently, and the order of matching is not
    /// guaranteed.
    /// - The order of returned contents for batch modify orders is the same as the order of the
    /// order list.
    /// - One order can only be modfied for less than 10000 times
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/trade#modify-multiple-orders
    [[nodiscard]] common::RestApiResponse<std::vector<ModifyMultipleOrdersResponseInner>>
    modify_multiple_orders(const ModifyMultipleOrdersParams& params) const;

    /// Asynchronous `modify_multiple_orders()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<ModifyMultipleOrdersResponseInner>>)`.
    template <class CompletionToken>
    auto async_modify_multiple_orders(const ModifyMultipleOrdersParams& params,
                                      CompletionToken&& token) const {
        return common::async_send<std::vector<ModifyMultipleOrdersResponseInner>>(
            client_, modify_multiple_orders_request(params), std::forward<CompletionToken>(token));
    }

    /// Place Multiple Orders (TRADE)
    ///
    /// POST /fapi/v1/batchOrders.
    ///
    /// Place Multiple Orders
    ///
    /// Weight: 5 on 10s order rate limit(X-MBX-ORDER-COUNT-10S);
    /// 1 on 1min order rate limit(X-MBX-ORDER-COUNT-1M);
    /// 5 on IP rate limit(x-mbx-used-weight-1m);
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Paremeter rules are same with `New Order`
    /// - Batch orders are processed concurrently, and the order of matching is not guaranteed.
    /// - The order of returned contents for batch orders is the same as the order of the order
    /// list.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/trade#place-multiple-orders
    [[nodiscard]] common::RestApiResponse<std::vector<PlaceMultipleOrdersResponseInner>>
    place_multiple_orders(const PlaceMultipleOrdersParams& params) const;

    /// Asynchronous `place_multiple_orders()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<PlaceMultipleOrdersResponseInner>>)`.
    template <class CompletionToken>
    auto async_place_multiple_orders(const PlaceMultipleOrdersParams& params,
                                     CompletionToken&& token) const {
        return common::async_send<std::vector<PlaceMultipleOrdersResponseInner>>(
            client_, place_multiple_orders_request(params), std::forward<CompletionToken>(token));
    }

    /// Cancel Order (TRADE)
    ///
    /// DELETE /fapi/v1/order.
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
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/trade#cancel-order
    [[nodiscard]] common::RestApiResponse<CancelOrderResponse>
    cancel_order(const CancelOrderParams& params) const;

    /// Asynchronous `cancel_order()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<CancelOrderResponse>)`.
    template <class CompletionToken>
    auto async_cancel_order(const CancelOrderParams& params, CompletionToken&& token) const {
        return common::async_send<CancelOrderResponse>(client_, cancel_order_request(params),
                                                       std::forward<CompletionToken>(token));
    }

    /// Modify Order (TRADE)
    ///
    /// PUT /fapi/v1/order.
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
    /// - Either `orderId` or `origClientOrderId` must be sent, and the `orderId` will prevail if
    /// both are sent.
    /// - Both `quantity` and `price` must be sent, which is different from dapi modify order
    /// endpoint.
    /// - When the new `quantity` or `price` doesn't satisfy PRICE_FILTER / PERCENT_FILTER /
    /// LOT_SIZE, amendment will be rejected and the order will stay as it is.
    /// - However the order will be cancelled by the amendment in the following situations:
    ///   - when the order is in partially filled status and the new `quantity` <= `executedQty`
    ///   - When the order is `GTX` and the new price will cause it to be executed immediately
    /// - One order can only be modfied for less than 10000 times
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
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/trade#modify-order
    [[nodiscard]] common::RestApiResponse<ModifyOrderResponse>
    modify_order(const ModifyOrderParams& params) const;

    /// Asynchronous `modify_order()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<ModifyOrderResponse>)`.
    template <class CompletionToken>
    auto async_modify_order(const ModifyOrderParams& params, CompletionToken&& token) const {
        return common::async_send<ModifyOrderResponse>(client_, modify_order_request(params),
                                                       std::forward<CompletionToken>(token));
    }

    /// New Order (TRADE)
    ///
    /// POST /fapi/v1/order.
    ///
    /// Send in a new order.
    ///
    /// Weight: 1 on 10s order rate limit(X-MBX-ORDER-COUNT-10S);
    /// 1 on 1min order rate limit(X-MBX-ORDER-COUNT-1M);
    /// 0 on IP rate limit(x-mbx-used-weight-1m)
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// Additional mandatory parameters based on `type`:
    ///
    /// | Type | Additional mandatory parameters |
    /// |------|----------------------------------|
    /// | `LIMIT` | `timeInForce`, `quantity`, `price` |
    /// | `MARKET` | `quantity` |
    ///
    /// - If `newOrderRespType` is sent as `RESULT`:
    ///   - `MARKET` order: the final FILLED result of the order will be returned directly.
    ///   - `LIMIT` order with special `timeInForce`: the final status result of the order (FILLED
    ///   or EXPIRED) will be returned directly.
    /// - `selfTradePreventionMode` is only effective when `timeInForce` is set to `IOC`, `GTC`, or
    /// `GTD`.
    /// - In extreme market conditions, `timeInForce` `GTD` order auto-cancel time might be delayed
    /// compared to `goodTillDate`.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/trade#new-order
    [[nodiscard]] common::RestApiResponse<NewOrderResponse>
    new_order(const NewOrderParams& params) const;

    /// Asynchronous `new_order()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<NewOrderResponse>)`.
    template <class CompletionToken>
    auto async_new_order(const NewOrderParams& params, CompletionToken&& token) const {
        return common::async_send<NewOrderResponse>(client_, new_order_request(params),
                                                    std::forward<CompletionToken>(token));
    }

    /// Query Order (USER_DATA)
    ///
    /// GET /fapi/v1/order.
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
    /// - Either `orderId` or `origClientOrderId` must be sent.
    /// - `orderId` is self-increment for each specific `symbol`
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/trade#query-order
    [[nodiscard]] common::RestApiResponse<QueryOrderResponse>
    query_order(const QueryOrderParams& params) const;

    /// Asynchronous `query_order()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<QueryOrderResponse>)`.
    template <class CompletionToken>
    auto async_query_order(const QueryOrderParams& params, CompletionToken&& token) const {
        return common::async_send<QueryOrderResponse>(client_, query_order_request(params),
                                                      std::forward<CompletionToken>(token));
    }

    /// Change Initial Leverage (TRADE)
    ///
    /// POST /fapi/v1/leverage.
    ///
    /// Change user's initial leverage of specific symbol market.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/trade#change-initial-leverage
    [[nodiscard]] common::RestApiResponse<ChangeInitialLeverageResponse>
    change_initial_leverage(const ChangeInitialLeverageParams& params) const;

    /// Asynchronous `change_initial_leverage()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<ChangeInitialLeverageResponse>)`.
    template <class CompletionToken>
    auto async_change_initial_leverage(const ChangeInitialLeverageParams& params,
                                       CompletionToken&& token) const {
        return common::async_send<ChangeInitialLeverageResponse>(
            client_, change_initial_leverage_request(params), std::forward<CompletionToken>(token));
    }

    /// Change Margin Type (TRADE)
    ///
    /// POST /fapi/v1/marginType.
    ///
    /// Change symbol level margin type
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/trade#change-margin-type
    [[nodiscard]] common::RestApiResponse<ChangeMarginTypeResponse>
    change_margin_type(const ChangeMarginTypeParams& params) const;

    /// Asynchronous `change_margin_type()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<ChangeMarginTypeResponse>)`.
    template <class CompletionToken>
    auto async_change_margin_type(const ChangeMarginTypeParams& params,
                                  CompletionToken&& token) const {
        return common::async_send<ChangeMarginTypeResponse>(
            client_, change_margin_type_request(params), std::forward<CompletionToken>(token));
    }

    /// Change Multi-Assets Mode (TRADE)
    ///
    /// POST /fapi/v1/multiAssetsMargin.
    ///
    /// Change user's Multi-Assets mode (Multi-Assets Mode or Single-Asset Mode) on ***Every
    /// symbol***
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/trade#change-multi-assets-mode
    [[nodiscard]] common::RestApiResponse<ChangeMultiAssetsModeResponse>
    change_multi_assets_mode(const ChangeMultiAssetsModeParams& params) const;

    /// Asynchronous `change_multi_assets_mode()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<ChangeMultiAssetsModeResponse>)`.
    template <class CompletionToken>
    auto async_change_multi_assets_mode(const ChangeMultiAssetsModeParams& params,
                                        CompletionToken&& token) const {
        return common::async_send<ChangeMultiAssetsModeResponse>(
            client_, change_multi_assets_mode_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Change Position Mode (TRADE)
    ///
    /// POST /fapi/v1/positionSide/dual.
    ///
    /// Change user's position mode (Hedge Mode or One-way Mode ) on ***EVERY symbol***.
    ///
    /// **After CM migration**, UM and CM share the **same** `dualSidePosition` setting. Calling
    /// this endpoint flips both UM and CM at once. If either side has any open order or open
    /// position, the change is rejected:
    /// - `-4067` (open orders exist)
    /// - `-4068` (open position exists)
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/trade#change-position-mode
    [[nodiscard]] common::RestApiResponse<ChangePositionModeResponse>
    change_position_mode(const ChangePositionModeParams& params) const;

    /// Asynchronous `change_position_mode()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<ChangePositionModeResponse>)`.
    template <class CompletionToken>
    auto async_change_position_mode(const ChangePositionModeParams& params,
                                    CompletionToken&& token) const {
        return common::async_send<ChangePositionModeResponse>(
            client_, change_position_mode_request(params), std::forward<CompletionToken>(token));
    }

    /// Current All Algo Open Orders (USER_DATA)
    ///
    /// GET /fapi/v1/openAlgoOrders.
    ///
    /// Get all open algo (conditional) orders on a symbol, including TP/SL (Take Profit / Stop
    /// Loss) and trailing stop orders on USD-M Futures.
    ///
    /// Weight: **1** for a single symbol; **40** when the symbol parameter is omitted
    ///
    /// **Careful** when accessing this with no symbol.
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If the symbol is not sent, orders for all symbols will be returned in an array.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/trade#current-all-algo-open-orders
    [[nodiscard]] common::RestApiResponse<std::vector<CurrentAllAlgoOpenOrdersResponseInner>>
    current_all_algo_open_orders(const CurrentAllAlgoOpenOrdersParams& params = {}) const;

    /// Asynchronous `current_all_algo_open_orders()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<CurrentAllAlgoOpenOrdersResponseInner>>)`.
    template <class CompletionToken>
    auto async_current_all_algo_open_orders(const CurrentAllAlgoOpenOrdersParams& params,
                                            CompletionToken&& token) const {
        return common::async_send<std::vector<CurrentAllAlgoOpenOrdersResponseInner>>(
            client_, current_all_algo_open_orders_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Current All Open Orders (USER_DATA)
    ///
    /// GET /fapi/v1/openOrders.
    ///
    /// Get all open orders on a symbol.
    ///
    /// Weight: **1** for a single symbol; **40** when the symbol parameter is omitted
    ///
    /// **Careful** when accessing this with no symbol.
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If the symbol is not sent, orders for all symbols will be returned in an array.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/trade#current-all-open-orders
    [[nodiscard]] common::RestApiResponse<std::vector<CurrentAllOpenOrdersResponseInner>>
    current_all_open_orders(const CurrentAllOpenOrdersParams& params = {}) const;

    /// Asynchronous `current_all_open_orders()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<CurrentAllOpenOrdersResponseInner>>)`.
    template <class CompletionToken>
    auto async_current_all_open_orders(const CurrentAllOpenOrdersParams& params,
                                       CompletionToken&& token) const {
        return common::async_send<std::vector<CurrentAllOpenOrdersResponseInner>>(
            client_, current_all_open_orders_request(params), std::forward<CompletionToken>(token));
    }

    /// Futures TradFi Perps Contract (USER_DATA)
    ///
    /// POST /fapi/v1/stock/contract.
    ///
    /// Sign TradFi-Perps agreement contract
    ///
    /// Weight(IP): 50
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/trade#futures-tradfi-perps-contract
    [[nodiscard]] common::RestApiResponse<FuturesTradfiPerpsContractResponse>
    futures_tradfi_perps_contract(const FuturesTradfiPerpsContractParams& params = {}) const;

    /// Asynchronous `futures_tradfi_perps_contract()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<FuturesTradfiPerpsContractResponse>)`.
    template <class CompletionToken>
    auto async_futures_tradfi_perps_contract(const FuturesTradfiPerpsContractParams& params,
                                             CompletionToken&& token) const {
        return common::async_send<FuturesTradfiPerpsContractResponse>(
            client_, futures_tradfi_perps_contract_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Order Modify History (USER_DATA)
    ///
    /// GET /fapi/v1/orderAmendment.
    ///
    /// Get order modification history
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Either `orderId` or `origClientOrderId` must be sent, and the
    /// `orderId` will prevail if both are sent.
    ///
    /// - Order modify history longer than 3 month is not avaliable
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/trade#get-order-modify-history
    [[nodiscard]] common::RestApiResponse<std::vector<GetOrderModifyHistoryResponseInner>>
    get_order_modify_history(const GetOrderModifyHistoryParams& params) const;

    /// Asynchronous `get_order_modify_history()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<GetOrderModifyHistoryResponseInner>>)`.
    template <class CompletionToken>
    auto async_get_order_modify_history(const GetOrderModifyHistoryParams& params,
                                        CompletionToken&& token) const {
        return common::async_send<std::vector<GetOrderModifyHistoryResponseInner>>(
            client_, get_order_modify_history_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Position Margin Change History (TRADE)
    ///
    /// GET /fapi/v1/positionMargin/history.
    ///
    /// Get Position Margin Change History
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Support querying future histories that are not older than 30 days
    /// - The time between `startTime` and `endTime`can't be more than 30 days
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/trade#get-position-margin-change-history
    [[nodiscard]] common::RestApiResponse<std::vector<GetPositionMarginChangeHistoryResponseInner>>
    get_position_margin_change_history(const GetPositionMarginChangeHistoryParams& params) const;

    /// Asynchronous `get_position_margin_change_history()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<GetPositionMarginChangeHistoryResponseInner>>)`.
    template <class CompletionToken>
    auto
    async_get_position_margin_change_history(const GetPositionMarginChangeHistoryParams& params,
                                             CompletionToken&& token) const {
        return common::async_send<std::vector<GetPositionMarginChangeHistoryResponseInner>>(
            client_, get_position_margin_change_history_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Modify Isolated Position Margin (TRADE)
    ///
    /// POST /fapi/v1/positionMargin.
    ///
    /// Modify Isolated Position Margin
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Only for isolated symbol
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/trade#modify-isolated-position-margin
    [[nodiscard]] common::RestApiResponse<ModifyIsolatedPositionMarginResponse>
    modify_isolated_position_margin(const ModifyIsolatedPositionMarginParams& params) const;

    /// Asynchronous `modify_isolated_position_margin()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<ModifyIsolatedPositionMarginResponse>)`.
    template <class CompletionToken>
    auto async_modify_isolated_position_margin(const ModifyIsolatedPositionMarginParams& params,
                                               CompletionToken&& token) const {
        return common::async_send<ModifyIsolatedPositionMarginResponse>(
            client_, modify_isolated_position_margin_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Position ADL Quantile Estimation (USER_DATA)
    ///
    /// GET /fapi/v1/adlQuantile.
    ///
    /// Position ADL Quantile Estimation
    ///
    /// * Values update every 30s.
    /// * Values 0, 1, 2, 3, 4 shows the queue position and possibility of ADL from low to high.
    /// * For positions of the symbol are in One-way Mode or isolated margined in Hedge Mode,
    /// "LONG", "SHORT", and "BOTH" will be returned to show the positions' adl quantiles of
    /// different position sides.
    /// * If the positions of the symbol are crossed margined in Hedge Mode:
    ///   * "HEDGE" as a sign will be returned instead of "BOTH";
    ///   * A same value caculated on unrealized pnls on long and short sides' positions will be
    ///   shown for "LONG" and "SHORT" when there are positions in both of long and short sides.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/trade#position-adl-quantile-estimation
    [[nodiscard]] common::RestApiResponse<std::vector<PositionAdlQuantileEstimationResponseInner>>
    position_adl_quantile_estimation(const PositionAdlQuantileEstimationParams& params = {}) const;

    /// Asynchronous `position_adl_quantile_estimation()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<PositionAdlQuantileEstimationResponseInner>>)`.
    template <class CompletionToken>
    auto async_position_adl_quantile_estimation(const PositionAdlQuantileEstimationParams& params,
                                                CompletionToken&& token) const {
        return common::async_send<std::vector<PositionAdlQuantileEstimationResponseInner>>(
            client_, position_adl_quantile_estimation_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Position Information V2 (USER_DATA)
    ///
    /// GET /fapi/v2/positionRisk.
    ///
    /// Get current position information.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Please use with user data stream `ACCOUNT_UPDATE` to meet your timeliness and accuracy
    /// needs.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/trade#position-information-v2
    [[nodiscard]] common::RestApiResponse<std::vector<PositionInformationV2ResponseInner>>
    position_information_v2(const PositionInformationV2Params& params = {}) const;

    /// Asynchronous `position_information_v2()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<PositionInformationV2ResponseInner>>)`.
    template <class CompletionToken>
    auto async_position_information_v2(const PositionInformationV2Params& params,
                                       CompletionToken&& token) const {
        return common::async_send<std::vector<PositionInformationV2ResponseInner>>(
            client_, position_information_v2_request(params), std::forward<CompletionToken>(token));
    }

    /// Position Information V3 (USER_DATA)
    ///
    /// GET /fapi/v3/positionRisk.
    ///
    /// Get current position information(only symbol that has position or open
    /// orders will be returned).
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Please use with user data stream `ACCOUNT_UPDATE` to meet your timeliness and accuracy
    /// needs.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/trade#position-information-v3
    [[nodiscard]] common::RestApiResponse<std::vector<PositionInformationV3ResponseInner>>
    position_information_v3(const PositionInformationV3Params& params = {}) const;

    /// Asynchronous `position_information_v3()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<PositionInformationV3ResponseInner>>)`.
    template <class CompletionToken>
    auto async_position_information_v3(const PositionInformationV3Params& params,
                                       CompletionToken&& token) const {
        return common::async_send<std::vector<PositionInformationV3ResponseInner>>(
            client_, position_information_v3_request(params), std::forward<CompletionToken>(token));
    }

    /// Query All Algo Orders (USER_DATA)
    ///
    /// GET /fapi/v1/allAlgoOrders.
    ///
    /// Get all algo (conditional) orders — active, CANCELED, TRIGGERED, or FINISHED — including
    /// TP/SL (Take Profit / Stop Loss) and trailing stop orders on USD-M Futures.
    ///
    /// * These orders will not be found:
    ///   * order status is `CANCELED` or `EXPIRED` **AND** order has NO filled trade **AND**
    ///   created time + 3 days < current time
    ///   * order create time + 90 days < current time
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If `algoId` is set, it will get orders >= that `algoId`. Otherwise most recent orders are
    /// returned.
    /// - The query time period must be less then 7 days( default as the recent 7 days).
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/trade#query-all-algo-orders
    [[nodiscard]] common::RestApiResponse<std::vector<QueryAllAlgoOrdersResponseInner>>
    query_all_algo_orders(const QueryAllAlgoOrdersParams& params) const;

    /// Asynchronous `query_all_algo_orders()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<QueryAllAlgoOrdersResponseInner>>)`.
    template <class CompletionToken>
    auto async_query_all_algo_orders(const QueryAllAlgoOrdersParams& params,
                                     CompletionToken&& token) const {
        return common::async_send<std::vector<QueryAllAlgoOrdersResponseInner>>(
            client_, query_all_algo_orders_request(params), std::forward<CompletionToken>(token));
    }

    /// Query Current Open Order (USER_DATA)
    ///
    /// GET /fapi/v1/openOrder.
    ///
    /// Query open order
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Either`orderId` or `origClientOrderId` must be sent
    /// - If the queried order has been filled or cancelled, the error message "Order does not
    /// exist" will be returned.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/trade#query-current-open-order
    [[nodiscard]] common::RestApiResponse<QueryCurrentOpenOrderResponse>
    query_current_open_order(const QueryCurrentOpenOrderParams& params) const;

    /// Asynchronous `query_current_open_order()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<QueryCurrentOpenOrderResponse>)`.
    template <class CompletionToken>
    auto async_query_current_open_order(const QueryCurrentOpenOrderParams& params,
                                        CompletionToken&& token) const {
        return common::async_send<QueryCurrentOpenOrderResponse>(
            client_, query_current_open_order_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Test Order (TRADE)
    ///
    /// POST /fapi/v1/order/test.
    ///
    /// Testing order request, this order will not be submitted to matching engine
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// Additional mandatory parameters based on `type`:
    ///
    /// | Type                             | Additional mandatory parameters    |
    /// | -------------------------------- | ---------------------------------- |
    /// | `LIMIT`                          | `timeInForce`, `quantity`, `price` |
    /// | `MARKET`                         | `quantity`                         |
    /// | `STOP/TAKE_PROFIT`               | `quantity`,  `price`, `stopPrice`  |
    /// | `STOP_MARKET/TAKE_PROFIT_MARKET` | `stopPrice`                        |
    /// | `TRAILING_STOP_MARKET`           | `callbackRate`                     |
    ///
    /// - Order with type `STOP`, parameter `timeInForce` can be sent ( default `GTC`).
    /// - Order with type `TAKE_PROFIT`, parameter `timeInForce` can be sent (default `GTC`).
    /// - Condition orders will be triggered when:
    ///   - If parameter`priceProtect`is sent as true:
    ///     - when price reaches the `stopPrice` ，the difference rate between "MARK_PRICE" and
    ///     "CONTRACT_PRICE" cannot be larger than the "triggerProtect" of the symbol
    ///     - "triggerProtect" of a symbol can be got from `GET /fapi/v1/exchangeInfo`
    ///   - `STOP`, `STOP_MARKET`:
    ///     - BUY: latest price ("MARK_PRICE" or "CONTRACT_PRICE") >= `stopPrice`
    ///     - SELL: latest price ("MARK_PRICE" or "CONTRACT_PRICE") <= `stopPrice`
    ///   - `TAKE_PROFIT`, `TAKE_PROFIT_MARKET`:
    ///     - BUY: latest price ("MARK_PRICE" or "CONTRACT_PRICE") <= `stopPrice`
    ///     - SELL: latest price ("MARK_PRICE" or "CONTRACT_PRICE") >= `stopPrice`
    ///   - `TRAILING_STOP_MARKET`:
    ///     - BUY: the lowest price after order placed <= `activationPrice`, and the latest price >=
    ///     the lowest price * (1 + `callbackRate`)
    ///     - SELL: the highest price after order placed >= `activationPrice`, and the latest price
    ///     <= the highest price * (1 - `callbackRate`)
    /// - For `TRAILING_STOP_MARKET`, if you got such error code. > `{"code": -2021, "msg": "Order
    /// would immediately trigger."}` > means that the parameters you send do not meet the following
    /// requirements:
    ///   - BUY: `activationPrice` should be smaller than latest price.
    ///   - SELL: `activationPrice` should be larger than latest price.
    /// - If `newOrderRespType ` is sent as `RESULT` :
    ///   - `MARKET` order: the final FILLED result of the order will be return directly.
    ///   - `LIMIT` order with special `timeInForce`: the final status result of the order(FILLED or
    ///   EXPIRED) will be returned directly.
    /// - `STOP_MARKET`, `TAKE_PROFIT_MARKET` with `closePosition`=`true`:
    ///   - Follow the same rules for condition orders.
    ///   - If triggered，**close all** current long position( if `SELL`) or current short position(
    ///   if `BUY`).
    ///   - Cannot be used with `quantity` paremeter
    ///   - Cannot be used with `reduceOnly` parameter
    ///   - In Hedge Mode,cannot be used with `BUY` orders in `LONG` position side. and cannot be
    ///   used with `SELL` orders in `SHORT` position side
    /// - `selfTradePreventionMode` is only effective when `timeInForce` set to `IOC` or `GTC` or
    /// `GTD`.
    /// - In extreme market conditions, timeInForce `GTD` order auto cancel time might be delayed
    /// comparing to `goodTillDate`
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/trade#test-order
    [[nodiscard]] common::RestApiResponse<TestOrderResponse>
    test_order(const TestOrderParams& params) const;

    /// Asynchronous `test_order()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<TestOrderResponse>)`.
    template <class CompletionToken>
    auto async_test_order(const TestOrderParams& params, CompletionToken&& token) const {
        return common::async_send<TestOrderResponse>(client_, test_order_request(params),
                                                     std::forward<CompletionToken>(token));
    }

    /// User's Force Orders (USER_DATA)
    ///
    /// GET /fapi/v1/forceOrders.
    ///
    /// Query user's Force Orders
    ///
    /// Weight: **20** with symbol, **50** without symbol
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If "autoCloseType" is not sent, orders with both of the types will be returned
    /// - If "startTime" is not sent, data within 7 days before "endTime" can be queried
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/trade#users-force-orders
    [[nodiscard]] common::RestApiResponse<std::vector<UsersForceOrdersResponseInner>>
    users_force_orders(const UsersForceOrdersParams& params = {}) const;

    /// Asynchronous `users_force_orders()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<UsersForceOrdersResponseInner>>)`.
    template <class CompletionToken>
    auto async_users_force_orders(const UsersForceOrdersParams& params,
                                  CompletionToken&& token) const {
        return common::async_send<std::vector<UsersForceOrdersResponseInner>>(
            client_, users_force_orders_request(params), std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest
    account_trade_list_request(const AccountTradeListParams& params) const;
    [[nodiscard]] common::RestRequest all_orders_request(const AllOrdersParams& params) const;
    [[nodiscard]] common::RestRequest
    auto_cancel_all_open_orders_request(const AutoCancelAllOpenOrdersParams& params) const;
    [[nodiscard]] common::RestRequest
    cancel_algo_order_request(const CancelAlgoOrderParams& params) const;
    [[nodiscard]] common::RestRequest
    new_algo_order_request(const NewAlgoOrderParams& params) const;
    [[nodiscard]] common::RestRequest
    query_algo_order_request(const QueryAlgoOrderParams& params) const;
    [[nodiscard]] common::RestRequest
    cancel_all_algo_open_orders_request(const CancelAllAlgoOpenOrdersParams& params) const;
    [[nodiscard]] common::RestRequest
    cancel_all_open_orders_request(const CancelAllOpenOrdersParams& params) const;
    [[nodiscard]] common::RestRequest
    cancel_multiple_orders_request(const CancelMultipleOrdersParams& params) const;
    [[nodiscard]] common::RestRequest
    modify_multiple_orders_request(const ModifyMultipleOrdersParams& params) const;
    [[nodiscard]] common::RestRequest
    place_multiple_orders_request(const PlaceMultipleOrdersParams& params) const;
    [[nodiscard]] common::RestRequest cancel_order_request(const CancelOrderParams& params) const;
    [[nodiscard]] common::RestRequest modify_order_request(const ModifyOrderParams& params) const;
    [[nodiscard]] common::RestRequest new_order_request(const NewOrderParams& params) const;
    [[nodiscard]] common::RestRequest query_order_request(const QueryOrderParams& params) const;
    [[nodiscard]] common::RestRequest
    change_initial_leverage_request(const ChangeInitialLeverageParams& params) const;
    [[nodiscard]] common::RestRequest
    change_margin_type_request(const ChangeMarginTypeParams& params) const;
    [[nodiscard]] common::RestRequest
    change_multi_assets_mode_request(const ChangeMultiAssetsModeParams& params) const;
    [[nodiscard]] common::RestRequest
    change_position_mode_request(const ChangePositionModeParams& params) const;
    [[nodiscard]] common::RestRequest
    current_all_algo_open_orders_request(const CurrentAllAlgoOpenOrdersParams& params) const;
    [[nodiscard]] common::RestRequest
    current_all_open_orders_request(const CurrentAllOpenOrdersParams& params) const;
    [[nodiscard]] common::RestRequest
    futures_tradfi_perps_contract_request(const FuturesTradfiPerpsContractParams& params) const;
    [[nodiscard]] common::RestRequest
    get_order_modify_history_request(const GetOrderModifyHistoryParams& params) const;
    [[nodiscard]] common::RestRequest get_position_margin_change_history_request(
        const GetPositionMarginChangeHistoryParams& params) const;
    [[nodiscard]] common::RestRequest
    modify_isolated_position_margin_request(const ModifyIsolatedPositionMarginParams& params) const;
    [[nodiscard]] common::RestRequest position_adl_quantile_estimation_request(
        const PositionAdlQuantileEstimationParams& params) const;
    [[nodiscard]] common::RestRequest
    position_information_v2_request(const PositionInformationV2Params& params) const;
    [[nodiscard]] common::RestRequest
    position_information_v3_request(const PositionInformationV3Params& params) const;
    [[nodiscard]] common::RestRequest
    query_all_algo_orders_request(const QueryAllAlgoOrdersParams& params) const;
    [[nodiscard]] common::RestRequest
    query_current_open_order_request(const QueryCurrentOpenOrderParams& params) const;
    [[nodiscard]] common::RestRequest test_order_request(const TestOrderParams& params) const;
    [[nodiscard]] common::RestRequest
    users_force_orders_request(const UsersForceOrdersParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::derivatives_trading_usds_futures::rest_api
