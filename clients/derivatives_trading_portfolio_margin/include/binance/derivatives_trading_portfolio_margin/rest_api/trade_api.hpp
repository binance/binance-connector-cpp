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
#include <binance/derivatives_trading_portfolio_margin/export.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/cancel_all_cm_open_conditional_orders_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/cancel_all_cm_open_orders_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/cancel_all_um_algo_open_orders_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/cancel_all_um_open_orders_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/cancel_cm_conditional_order_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/cancel_cm_order_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/cancel_margin_account_all_open_orders_on_a_symbol_response_inner.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/cancel_margin_account_oco_orders_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/cancel_margin_account_order_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/cancel_um_algo_order_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/cancel_um_order_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/cm_account_trade_list_response_inner.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/cm_position_adl_quantile_estimation_response_inner.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/futures_tradfi_perps_contract_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/get_um_futures_bnb_burn_status_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/margin_account_borrow_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/margin_account_new_oco_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/margin_account_repay_debt_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/margin_account_repay_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/margin_account_trade_list_response_inner.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/modify_cm_order_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/modify_um_order_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/new_cm_conditional_order_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/new_cm_order_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/new_margin_order_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/new_um_algo_order_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/new_um_order_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/query_all_cm_conditional_orders_response_inner.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/query_all_cm_orders_response_inner.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/query_all_current_cm_open_conditional_orders_response_inner.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/query_all_current_um_open_algo_orders_response_inner.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/query_all_current_um_open_orders_response_inner.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/query_all_margin_account_orders_response_inner.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/query_cm_conditional_order_history_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/query_cm_modify_order_history_response_inner.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/query_cm_order_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/query_current_cm_open_conditional_order_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/query_current_margin_open_order_response_inner.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/query_current_um_open_algo_order_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/query_current_um_open_order_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/query_margin_account_order_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/query_margin_accounts_all_oco_response_inner.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/query_margin_accounts_oco_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/query_margin_accounts_open_oco_response_inner.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/query_um_algo_order_history_response_inner.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/query_um_modify_order_history_response_inner.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/query_um_order_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/query_users_cm_force_orders_response_inner.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/query_users_margin_force_orders_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/query_users_um_force_orders_response_inner.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/toggle_bnb_burn_on_um_futures_trade_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/um_account_trade_list_response_inner.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/um_position_adl_quantile_estimation_response_inner.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

enum class NewCmConditionalOrderSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(NewCmConditionalOrderSideEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT NewCmConditionalOrderSideEnum tag_invoke(
    boost::json::value_to_tag<NewCmConditionalOrderSideEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           NewCmConditionalOrderSideEnum value);

enum class NewCmConditionalOrderStrategyTypeEnum {
    Stop,
    StopMarket,
    TakeProfit,
    TakeProfitMarket,
    TrailingStopMarket,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(NewCmConditionalOrderStrategyTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT NewCmConditionalOrderStrategyTypeEnum
tag_invoke(boost::json::value_to_tag<NewCmConditionalOrderStrategyTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           NewCmConditionalOrderStrategyTypeEnum value);

enum class NewCmConditionalOrderPositionSideEnum {
    Both,
    Long,
    Short,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(NewCmConditionalOrderPositionSideEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT NewCmConditionalOrderPositionSideEnum
tag_invoke(boost::json::value_to_tag<NewCmConditionalOrderPositionSideEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           NewCmConditionalOrderPositionSideEnum value);

enum class NewCmConditionalOrderTimeInForceEnum {
    Gtc,
    Ioc,
    Fok,
    Gtx,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(NewCmConditionalOrderTimeInForceEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT NewCmConditionalOrderTimeInForceEnum
tag_invoke(boost::json::value_to_tag<NewCmConditionalOrderTimeInForceEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           NewCmConditionalOrderTimeInForceEnum value);

enum class NewCmConditionalOrderWorkingTypeEnum {
    MarkPrice,
    ContractPrice,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(NewCmConditionalOrderWorkingTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT NewCmConditionalOrderWorkingTypeEnum
tag_invoke(boost::json::value_to_tag<NewCmConditionalOrderWorkingTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           NewCmConditionalOrderWorkingTypeEnum value);

enum class NewCmConditionalOrderPriceProtectEnum {
    True_,
    False_,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(NewCmConditionalOrderPriceProtectEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT NewCmConditionalOrderPriceProtectEnum
tag_invoke(boost::json::value_to_tag<NewCmConditionalOrderPriceProtectEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           NewCmConditionalOrderPriceProtectEnum value);

enum class ModifyCmOrderSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(ModifyCmOrderSideEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT ModifyCmOrderSideEnum
tag_invoke(boost::json::value_to_tag<ModifyCmOrderSideEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           ModifyCmOrderSideEnum value);

enum class ModifyCmOrderPriceMatchEnum {
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

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(ModifyCmOrderPriceMatchEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT ModifyCmOrderPriceMatchEnum tag_invoke(
    boost::json::value_to_tag<ModifyCmOrderPriceMatchEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           ModifyCmOrderPriceMatchEnum value);

enum class NewCmOrderSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(NewCmOrderSideEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT NewCmOrderSideEnum
tag_invoke(boost::json::value_to_tag<NewCmOrderSideEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv, NewCmOrderSideEnum value);

enum class NewCmOrderTypeEnum {
    Limit,
    Market,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(NewCmOrderTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT NewCmOrderTypeEnum
tag_invoke(boost::json::value_to_tag<NewCmOrderTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv, NewCmOrderTypeEnum value);

enum class NewCmOrderPositionSideEnum {
    Both,
    Long,
    Short,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(NewCmOrderPositionSideEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT NewCmOrderPositionSideEnum tag_invoke(
    boost::json::value_to_tag<NewCmOrderPositionSideEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           NewCmOrderPositionSideEnum value);

enum class NewCmOrderTimeInForceEnum {
    Gtc,
    Ioc,
    Fok,
    Gtx,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(NewCmOrderTimeInForceEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT NewCmOrderTimeInForceEnum tag_invoke(
    boost::json::value_to_tag<NewCmOrderTimeInForceEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           NewCmOrderTimeInForceEnum value);

enum class NewCmOrderReduceOnlyEnum {
    True_,
    False_,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(NewCmOrderReduceOnlyEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT NewCmOrderReduceOnlyEnum tag_invoke(
    boost::json::value_to_tag<NewCmOrderReduceOnlyEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           NewCmOrderReduceOnlyEnum value);

enum class NewCmOrderPriceMatchEnum {
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

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(NewCmOrderPriceMatchEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT NewCmOrderPriceMatchEnum tag_invoke(
    boost::json::value_to_tag<NewCmOrderPriceMatchEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           NewCmOrderPriceMatchEnum value);

enum class NewCmOrderNewOrderRespTypeEnum {
    Ack,
    Result,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(NewCmOrderNewOrderRespTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT NewCmOrderNewOrderRespTypeEnum
tag_invoke(boost::json::value_to_tag<NewCmOrderNewOrderRespTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           NewCmOrderNewOrderRespTypeEnum value);

enum class NewMarginOrderSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(NewMarginOrderSideEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT NewMarginOrderSideEnum
tag_invoke(boost::json::value_to_tag<NewMarginOrderSideEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           NewMarginOrderSideEnum value);

enum class NewMarginOrderTypeEnum {
    Limit,
    Market,
    StopLoss,
    StopLossLimit,
    TakeProfit,
    TakeProfitLimit,
    LimitMaker,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(NewMarginOrderTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT NewMarginOrderTypeEnum
tag_invoke(boost::json::value_to_tag<NewMarginOrderTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           NewMarginOrderTypeEnum value);

enum class NewMarginOrderNewOrderRespTypeEnum {
    Ack,
    Result,
    Full,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(NewMarginOrderNewOrderRespTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT NewMarginOrderNewOrderRespTypeEnum
tag_invoke(boost::json::value_to_tag<NewMarginOrderNewOrderRespTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           NewMarginOrderNewOrderRespTypeEnum value);

enum class NewMarginOrderSideEffectTypeEnum {
    NoSideEffect,
    MarginBuy,
    AutoRepay,
    AutoBorrowRepay,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(NewMarginOrderSideEffectTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT NewMarginOrderSideEffectTypeEnum
tag_invoke(boost::json::value_to_tag<NewMarginOrderSideEffectTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           NewMarginOrderSideEffectTypeEnum value);

enum class NewMarginOrderTimeInForceEnum {
    Gtc,
    Ioc,
    Fok,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(NewMarginOrderTimeInForceEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT NewMarginOrderTimeInForceEnum tag_invoke(
    boost::json::value_to_tag<NewMarginOrderTimeInForceEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           NewMarginOrderTimeInForceEnum value);

enum class NewMarginOrderSelfTradePreventionModeEnum {
    None_,
    ExpireTaker,
    ExpireBoth,
    ExpireMaker,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(NewMarginOrderSelfTradePreventionModeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT NewMarginOrderSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<NewMarginOrderSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           NewMarginOrderSelfTradePreventionModeEnum value);

enum class NewUmAlgoOrderAlgoTypeEnum {
    Conditional,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(NewUmAlgoOrderAlgoTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT NewUmAlgoOrderAlgoTypeEnum tag_invoke(
    boost::json::value_to_tag<NewUmAlgoOrderAlgoTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           NewUmAlgoOrderAlgoTypeEnum value);

enum class NewUmAlgoOrderSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(NewUmAlgoOrderSideEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT NewUmAlgoOrderSideEnum
tag_invoke(boost::json::value_to_tag<NewUmAlgoOrderSideEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           NewUmAlgoOrderSideEnum value);

enum class NewUmAlgoOrderTypeEnum {
    Stop,
    TakeProfit,
    StopMarket,
    TakeProfitMarket,
    TrailingStopMarket,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(NewUmAlgoOrderTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT NewUmAlgoOrderTypeEnum
tag_invoke(boost::json::value_to_tag<NewUmAlgoOrderTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           NewUmAlgoOrderTypeEnum value);

enum class NewUmAlgoOrderPositionSideEnum {
    Both,
    Long,
    Short,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(NewUmAlgoOrderPositionSideEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT NewUmAlgoOrderPositionSideEnum
tag_invoke(boost::json::value_to_tag<NewUmAlgoOrderPositionSideEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           NewUmAlgoOrderPositionSideEnum value);

enum class NewUmAlgoOrderTimeInForceEnum {
    Ioc,
    Gtc,
    Fok,
    Gtx,
    Gtd,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(NewUmAlgoOrderTimeInForceEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT NewUmAlgoOrderTimeInForceEnum tag_invoke(
    boost::json::value_to_tag<NewUmAlgoOrderTimeInForceEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           NewUmAlgoOrderTimeInForceEnum value);

enum class NewUmAlgoOrderWorkingTypeEnum {
    MarkPrice,
    ContractPrice,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(NewUmAlgoOrderWorkingTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT NewUmAlgoOrderWorkingTypeEnum tag_invoke(
    boost::json::value_to_tag<NewUmAlgoOrderWorkingTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           NewUmAlgoOrderWorkingTypeEnum value);

enum class NewUmAlgoOrderPriceMatchEnum {
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

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(NewUmAlgoOrderPriceMatchEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT NewUmAlgoOrderPriceMatchEnum tag_invoke(
    boost::json::value_to_tag<NewUmAlgoOrderPriceMatchEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           NewUmAlgoOrderPriceMatchEnum value);

enum class NewUmAlgoOrderClosePositionEnum {
    True_,
    False_,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(NewUmAlgoOrderClosePositionEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT NewUmAlgoOrderClosePositionEnum
tag_invoke(boost::json::value_to_tag<NewUmAlgoOrderClosePositionEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           NewUmAlgoOrderClosePositionEnum value);

enum class NewUmAlgoOrderPriceProtectEnum {
    True_,
    False_,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(NewUmAlgoOrderPriceProtectEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT NewUmAlgoOrderPriceProtectEnum
tag_invoke(boost::json::value_to_tag<NewUmAlgoOrderPriceProtectEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           NewUmAlgoOrderPriceProtectEnum value);

enum class NewUmAlgoOrderReduceOnlyEnum {
    True_,
    False_,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(NewUmAlgoOrderReduceOnlyEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT NewUmAlgoOrderReduceOnlyEnum tag_invoke(
    boost::json::value_to_tag<NewUmAlgoOrderReduceOnlyEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           NewUmAlgoOrderReduceOnlyEnum value);

enum class NewUmAlgoOrderNewOrderRespTypeEnum {
    Ack,
    Result,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(NewUmAlgoOrderNewOrderRespTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT NewUmAlgoOrderNewOrderRespTypeEnum
tag_invoke(boost::json::value_to_tag<NewUmAlgoOrderNewOrderRespTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           NewUmAlgoOrderNewOrderRespTypeEnum value);

enum class NewUmAlgoOrderSelfTradePreventionModeEnum {
    None_,
    ExpireTaker,
    ExpireMaker,
    ExpireBoth,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(NewUmAlgoOrderSelfTradePreventionModeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT NewUmAlgoOrderSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<NewUmAlgoOrderSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           NewUmAlgoOrderSelfTradePreventionModeEnum value);

enum class ModifyUmOrderSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(ModifyUmOrderSideEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT ModifyUmOrderSideEnum
tag_invoke(boost::json::value_to_tag<ModifyUmOrderSideEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           ModifyUmOrderSideEnum value);

enum class ModifyUmOrderPriceMatchEnum {
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

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(ModifyUmOrderPriceMatchEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT ModifyUmOrderPriceMatchEnum tag_invoke(
    boost::json::value_to_tag<ModifyUmOrderPriceMatchEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           ModifyUmOrderPriceMatchEnum value);

enum class NewUmOrderSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(NewUmOrderSideEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT NewUmOrderSideEnum
tag_invoke(boost::json::value_to_tag<NewUmOrderSideEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv, NewUmOrderSideEnum value);

enum class NewUmOrderTypeEnum {
    Limit,
    Market,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(NewUmOrderTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT NewUmOrderTypeEnum
tag_invoke(boost::json::value_to_tag<NewUmOrderTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv, NewUmOrderTypeEnum value);

enum class NewUmOrderPositionSideEnum {
    Both,
    Long,
    Short,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(NewUmOrderPositionSideEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT NewUmOrderPositionSideEnum tag_invoke(
    boost::json::value_to_tag<NewUmOrderPositionSideEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           NewUmOrderPositionSideEnum value);

enum class NewUmOrderTimeInForceEnum {
    Gtc,
    Ioc,
    Fok,
    Gtx,
    Gtd,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(NewUmOrderTimeInForceEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT NewUmOrderTimeInForceEnum tag_invoke(
    boost::json::value_to_tag<NewUmOrderTimeInForceEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           NewUmOrderTimeInForceEnum value);

enum class NewUmOrderReduceOnlyEnum {
    True_,
    False_,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(NewUmOrderReduceOnlyEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT NewUmOrderReduceOnlyEnum tag_invoke(
    boost::json::value_to_tag<NewUmOrderReduceOnlyEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           NewUmOrderReduceOnlyEnum value);

enum class NewUmOrderNewOrderRespTypeEnum {
    Ack,
    Result,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(NewUmOrderNewOrderRespTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT NewUmOrderNewOrderRespTypeEnum
tag_invoke(boost::json::value_to_tag<NewUmOrderNewOrderRespTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           NewUmOrderNewOrderRespTypeEnum value);

enum class NewUmOrderPriceMatchEnum {
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

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(NewUmOrderPriceMatchEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT NewUmOrderPriceMatchEnum tag_invoke(
    boost::json::value_to_tag<NewUmOrderPriceMatchEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           NewUmOrderPriceMatchEnum value);

enum class NewUmOrderSelfTradePreventionModeEnum {
    ExpireTaker,
    ExpireBoth,
    ExpireMaker,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(NewUmOrderSelfTradePreventionModeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT NewUmOrderSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<NewUmOrderSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           NewUmOrderSelfTradePreventionModeEnum value);

enum class ToggleBnbBurnOnUmFuturesTradeFeeBurnEnum {
    True_,
    False_,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(ToggleBnbBurnOnUmFuturesTradeFeeBurnEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT ToggleBnbBurnOnUmFuturesTradeFeeBurnEnum
tag_invoke(boost::json::value_to_tag<ToggleBnbBurnOnUmFuturesTradeFeeBurnEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           ToggleBnbBurnOnUmFuturesTradeFeeBurnEnum value);

enum class MarginAccountNewOcoSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(MarginAccountNewOcoSideEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT MarginAccountNewOcoSideEnum tag_invoke(
    boost::json::value_to_tag<MarginAccountNewOcoSideEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           MarginAccountNewOcoSideEnum value);

enum class MarginAccountNewOcoStopLimitTimeInForceEnum {
    Gtc,
    Ioc,
    Fok,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(MarginAccountNewOcoStopLimitTimeInForceEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT MarginAccountNewOcoStopLimitTimeInForceEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOcoStopLimitTimeInForceEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           MarginAccountNewOcoStopLimitTimeInForceEnum value);

enum class MarginAccountNewOcoNewOrderRespTypeEnum {
    Ack,
    Result,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(MarginAccountNewOcoNewOrderRespTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT MarginAccountNewOcoNewOrderRespTypeEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOcoNewOrderRespTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           MarginAccountNewOcoNewOrderRespTypeEnum value);

enum class MarginAccountNewOcoSideEffectTypeEnum {
    NoSideEffect,
    MarginBuy,
    AutoRepay,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(MarginAccountNewOcoSideEffectTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT MarginAccountNewOcoSideEffectTypeEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOcoSideEffectTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           MarginAccountNewOcoSideEffectTypeEnum value);

enum class QueryUsersCmForceOrdersAutoCloseTypeEnum {
    Liquidation,
    Adl,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(QueryUsersCmForceOrdersAutoCloseTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT QueryUsersCmForceOrdersAutoCloseTypeEnum
tag_invoke(boost::json::value_to_tag<QueryUsersCmForceOrdersAutoCloseTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           QueryUsersCmForceOrdersAutoCloseTypeEnum value);

enum class QueryUsersUmForceOrdersAutoCloseTypeEnum {
    Liquidation,
    Adl,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(QueryUsersUmForceOrdersAutoCloseTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT QueryUsersUmForceOrdersAutoCloseTypeEnum
tag_invoke(boost::json::value_to_tag<QueryUsersUmForceOrdersAutoCloseTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           QueryUsersUmForceOrdersAutoCloseTypeEnum value);

struct CancelAllCmOpenConditionalOrdersParams {
    /// Symbol
    common::Required<std::string> symbol;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct CancelAllCmOpenOrdersParams {
    /// Symbol
    common::Required<std::string> symbol;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct CancelAllUmAlgoOpenOrdersParams {
    /// Symbol
    common::Required<std::string> symbol;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct CancelAllUmOpenOrdersParams {
    /// Symbol
    common::Required<std::string> symbol;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct CancelCmConditionalOrderParams {
    /// Symbol
    common::Required<std::string> symbol;
    std::optional<std::int64_t> strategy_id = std::nullopt;
    std::optional<std::string> new_client_strategy_id = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct NewCmConditionalOrderParams {
    /// Symbol
    common::Required<std::string> symbol;
    /// Side
    common::Required<NewCmConditionalOrderSideEnum> side;
    common::Required<NewCmConditionalOrderStrategyTypeEnum> strategy_type;
    /// Default `BOTH` for One-way Mode ; `LONG` or `SHORT` for Hedge Mode. It must be sent in Hedge
    /// Mode.
    std::optional<NewCmConditionalOrderPositionSideEnum> position_side = std::nullopt;
    std::optional<NewCmConditionalOrderTimeInForceEnum> time_in_force = std::nullopt;
    std::optional<common::Decimal> quantity = std::nullopt;
    /// "true" or "false". default "false". Cannot be sent in Hedge Mode
    std::optional<std::string> reduce_only = std::nullopt;
    std::optional<common::Decimal> price = std::nullopt;
    /// stopPrice triggered by: "MARK_PRICE", "CONTRACT_PRICE". Default "CONTRACT_PRICE"
    std::optional<NewCmConditionalOrderWorkingTypeEnum> working_type = std::nullopt;
    /// "true" or "false", default "false". Used with `STOP`/`STOP_MARKET` or
    /// `TAKE_PROFIT`/`TAKE_PROFIT_MARKET` orders
    std::optional<NewCmConditionalOrderPriceProtectEnum> price_protect = std::nullopt;
    /// A unique id among open orders. Automatically generated if not sent. Can only be string
    /// following the rule: `^[\.A-Z\:/a-z0-9_-]{1,36}$`
    std::optional<std::string> new_client_strategy_id = std::nullopt;
    /// Used with `STOP/STOP_MARKET` or `TAKE_PROFIT/TAKE_PROFIT_MARKET` orders.
    std::optional<common::Decimal> stop_price = std::nullopt;
    /// Used with `TRAILING_STOP_MARKET` orders.
    std::optional<common::Decimal> activation_price = std::nullopt;
    /// Used with `TRAILING_STOP_MARKET` orders.
    std::optional<common::Decimal> callback_rate = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct CancelCmOrderParams {
    /// Symbol
    common::Required<std::string> symbol;
    std::optional<std::int64_t> order_id = std::nullopt;
    std::optional<std::string> orig_client_order_id = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct ModifyCmOrderParams {
    /// Symbol
    common::Required<std::string> symbol;
    common::Required<ModifyCmOrderSideEnum> side;
    /// Order quantity
    common::Required<common::Decimal> quantity;
    /// Order price
    common::Required<common::Decimal> price;
    /// Order ID
    std::optional<std::int64_t> order_id = std::nullopt;
    /// Client order ID
    std::optional<std::string> orig_client_order_id = std::nullopt;
    /// only avaliable for `LIMIT`/`STOP`/`TAKE_PROFIT` order; can be set to `OPPONENT`/
    /// `OPPONENT_5`/ `OPPONENT_10`/ `OPPONENT_20`: /`QUEUE`/ `QUEUE_5`/ `QUEUE_10`/ `QUEUE_20`;
    /// Can't be passed together with `price`
    std::optional<ModifyCmOrderPriceMatchEnum> price_match = std::nullopt;
    /// User-defined modification identifier, returned as-is in the response. Optional; not
    /// validated for uniqueness.
    std::optional<std::int64_t> modify_id = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct NewCmOrderParams {
    /// Symbol
    common::Required<std::string> symbol;
    /// Side
    common::Required<NewCmOrderSideEnum> side;
    common::Required<NewCmOrderTypeEnum> type;
    /// Default `BOTH` for One-way Mode ; `LONG` or `SHORT` for Hedge Mode. It must be sent in Hedge
    /// Mode.
    std::optional<NewCmOrderPositionSideEnum> position_side = std::nullopt;
    std::optional<NewCmOrderTimeInForceEnum> time_in_force = std::nullopt;
    /// Place amount
    std::optional<common::Decimal> quantity = std::nullopt;
    /// "true" or "false". Cannot be sent in Hedge Mode.
    std::optional<NewCmOrderReduceOnlyEnum> reduce_only = std::nullopt;
    /// Order price
    std::optional<common::Decimal> price = std::nullopt;
    /// only avaliable for `LIMIT`/`STOP`/`TAKE_PROFIT` order; can be set to `OPPONENT`/
    /// `OPPONENT_5`/ `OPPONENT_10`/ `OPPONENT_20`: /`QUEUE`/ `QUEUE_5`/ `QUEUE_10`/ `QUEUE_20`;
    /// Can't be passed together with `price`
    std::optional<NewCmOrderPriceMatchEnum> price_match = std::nullopt;
    /// A unique id among open orders. Automatically generated if not sent. Can only be string
    /// following the rule: `^[\.A-Z\:/a-z0-9_-]{1,32}$`
    std::optional<std::string> new_client_order_id = std::nullopt;
    /// "ACK", "RESULT", default "ACK"
    std::optional<NewCmOrderNewOrderRespTypeEnum> new_order_resp_type = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryCmOrderParams {
    /// Symbol
    common::Required<std::string> symbol;
    std::optional<std::int64_t> order_id = std::nullopt;
    std::optional<std::string> orig_client_order_id = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct CancelMarginAccountAllOpenOrdersOnASymbolParams {
    /// Symbol
    common::Required<std::string> symbol;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct CancelMarginAccountOcoOrdersParams {
    /// Symbol
    common::Required<std::string> symbol;
    /// Either `orderListId` or `listClientOrderId` must be provided
    std::optional<std::int64_t> order_list_id = std::nullopt;
    /// Either `orderListId` or `listClientOrderId` must be provided
    std::optional<std::string> list_client_order_id = std::nullopt;
    /// Used to uniquely identify this cancel request.
    std::optional<std::string> new_client_order_id = std::nullopt;
    /// The value cannot be greater than 60000
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryMarginAccountsOcoParams {
    /// Either `orderListId` or `listClientOrderId` must be provided
    std::optional<std::int64_t> order_list_id = std::nullopt;
    /// `orderListId` or `listClientOrderId` must be provided.
    std::optional<std::string> orig_client_order_id = std::nullopt;
    /// Value cannot be greater than 60000
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct CancelMarginAccountOrderParams {
    /// Symbol
    common::Required<std::string> symbol;
    std::optional<std::int64_t> order_id = std::nullopt;
    std::optional<std::string> orig_client_order_id = std::nullopt;
    /// Used to uniquely identify this cancel request.
    std::optional<std::string> new_client_order_id = std::nullopt;
    /// The value cannot be greater than `60000`
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct NewMarginOrderParams {
    common::Required<std::string> symbol;
    common::Required<NewMarginOrderSideEnum> side;
    common::Required<NewMarginOrderTypeEnum> type;
    std::optional<common::Decimal> quantity = std::nullopt;
    std::optional<common::Decimal> quote_order_qty = std::nullopt;
    std::optional<common::Decimal> price = std::nullopt;
    /// Used with `STOP_LOSS`, `STOP_LOSS_LIMIT`, `TAKE_PROFIT`, and `TAKE_PROFIT_LIMIT` orders.
    std::optional<common::Decimal> stop_price = std::nullopt;
    /// A unique id among open orders. Automatically generated if not sent.
    std::optional<std::string> new_client_order_id = std::nullopt;
    /// Set the response JSON. ACK, RESULT, or FULL.
    std::optional<NewMarginOrderNewOrderRespTypeEnum> new_order_resp_type = std::nullopt;
    /// Used with `LIMIT`, `STOP_LOSS_LIMIT`, and `TAKE_PROFIT_LIMIT` to create an iceberg order
    std::optional<common::Decimal> iceberg_qty = std::nullopt;
    std::optional<NewMarginOrderSideEffectTypeEnum> side_effect_type = std::nullopt;
    std::optional<NewMarginOrderTimeInForceEnum> time_in_force = std::nullopt;
    /// `NONE`: No STP / `EXPIRE_TAKER`: expire taker order when STP triggers/ `EXPIRE_MAKER`:
    /// expire taker order when STP triggers/ `EXPIRE_BOTH`: expire both orders when STP triggers
    std::optional<NewMarginOrderSelfTradePreventionModeEnum> self_trade_prevention_mode =
        std::nullopt;
    /// Only when MARGIN_BUY or AUTO_BORROW_REPAY order takes effect, true means that the debt
    /// generated by the order needs to be repaid after the order is cancelled.
    std::optional<bool> auto_repay_at_cancel = std::nullopt;
    /// The value cannot be greater than `60000`
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryMarginAccountOrderParams {
    /// Symbol
    common::Required<std::string> symbol;
    std::optional<std::int64_t> order_id = std::nullopt;
    std::optional<std::string> orig_client_order_id = std::nullopt;
    /// Value cannot be greater than 60000
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct CancelUmAlgoOrderParams {
    /// Algo order ID
    std::optional<std::int64_t> algo_id = std::nullopt;
    /// Client algo order ID
    std::optional<std::string> client_algo_id = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct NewUmAlgoOrderParams {
    /// Only support `CONDITIONAL`
    common::Required<NewUmAlgoOrderAlgoTypeEnum> algo_type;
    common::Required<std::string> symbol;
    common::Required<NewUmAlgoOrderSideEnum> side;
    /// Conditional order type
    common::Required<NewUmAlgoOrderTypeEnum> type;
    /// Default `BOTH` for One-way Mode; `LONG` or `SHORT` for Hedge Mode
    std::optional<NewUmAlgoOrderPositionSideEnum> position_side = std::nullopt;
    std::optional<NewUmAlgoOrderTimeInForceEnum> time_in_force = std::nullopt;
    /// Order quantity. Cannot be sent with `closePosition`=`true`(Close-All)
    std::optional<common::Decimal> quantity = std::nullopt;
    /// Order price
    std::optional<common::Decimal> price = std::nullopt;
    /// Trigger price
    std::optional<common::Decimal> trigger_price = std::nullopt;
    /// Trigger price type. Default `CONTRACT_PRICE`
    std::optional<NewUmAlgoOrderWorkingTypeEnum> working_type = std::nullopt;
    /// Can't be passed together with `price`
    std::optional<NewUmAlgoOrderPriceMatchEnum> price_match = std::nullopt;
    /// Close-All, used with `STOP_MARKET` or `TAKE_PROFIT_MARKET`.
    std::optional<NewUmAlgoOrderClosePositionEnum> close_position = std::nullopt;
    /// Price protection. Default `false`
    std::optional<NewUmAlgoOrderPriceProtectEnum> price_protect = std::nullopt;
    /// Cannot be sent in Hedge Mode; cannot be sent with `closePosition`=`true`
    std::optional<NewUmAlgoOrderReduceOnlyEnum> reduce_only = std::nullopt;
    /// Used with `TRAILING_STOP_MARKET`, default as latest price
    std::optional<common::Decimal> activate_price = std::nullopt;
    /// Used with `TRAILING_STOP_MARKET`, min 0.1, max 20 (1 = 1%)
    std::optional<common::Decimal> callback_rate = std::nullopt;
    /// Unique id among open orders. Auto-generated if not sent
    std::optional<std::string> client_algo_id = std::nullopt;
    std::optional<NewUmAlgoOrderNewOrderRespTypeEnum> new_order_resp_type = std::nullopt;
    std::optional<NewUmAlgoOrderSelfTradePreventionModeEnum> self_trade_prevention_mode =
        std::nullopt;
    /// Order cancel time for `GTD` timeInForce, mandatory when timeInForce is `GTD`
    std::optional<std::int64_t> good_till_date = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct CancelUmOrderParams {
    /// Symbol
    common::Required<std::string> symbol;
    std::optional<std::int64_t> order_id = std::nullopt;
    std::optional<std::string> orig_client_order_id = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct ModifyUmOrderParams {
    /// Symbol
    common::Required<std::string> symbol;
    common::Required<ModifyUmOrderSideEnum> side;
    /// Order quantity
    common::Required<common::Decimal> quantity;
    /// Order price
    common::Required<common::Decimal> price;
    /// Order ID
    std::optional<std::int64_t> order_id = std::nullopt;
    /// Client order ID
    std::optional<std::string> orig_client_order_id = std::nullopt;
    /// only avaliable for `LIMIT`/`STOP`/`TAKE_PROFIT` order; can be set to `OPPONENT`/
    /// `OPPONENT_5`/ `OPPONENT_10`/ `OPPONENT_20`: /`QUEUE`/ `QUEUE_5`/ `QUEUE_10`/ `QUEUE_20`;
    /// Can't be passed together with `price`
    std::optional<ModifyUmOrderPriceMatchEnum> price_match = std::nullopt;
    /// User-defined modification identifier, returned as-is in the response. Optional; not
    /// validated for uniqueness.
    std::optional<std::int64_t> modify_id = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct NewUmOrderParams {
    /// Symbol
    common::Required<std::string> symbol;
    common::Required<NewUmOrderSideEnum> side;
    common::Required<NewUmOrderTypeEnum> type;
    /// Default `BOTH` for One-way Mode ; `LONG` or `SHORT` for Hedge Mode. It must be sent in Hedge
    /// Mode.
    std::optional<NewUmOrderPositionSideEnum> position_side = std::nullopt;
    /// Valid values
    std::optional<NewUmOrderTimeInForceEnum> time_in_force = std::nullopt;
    /// Place amount
    std::optional<common::Decimal> quantity = std::nullopt;
    /// "true" or "false". default "false". Cannot be sent in Hedge Mode .
    std::optional<NewUmOrderReduceOnlyEnum> reduce_only = std::nullopt;
    /// Order price
    std::optional<common::Decimal> price = std::nullopt;
    /// A unique id among open orders. Automatically generated if not sent. Can only be string
    /// following the rule: `^[\.A-Z\:/a-z0-9_-]{1,32}$`
    std::optional<std::string> new_client_order_id = std::nullopt;
    /// `ACK`, `RESULT`, default `ACK`
    std::optional<NewUmOrderNewOrderRespTypeEnum> new_order_resp_type = std::nullopt;
    /// only avaliable for `LIMIT`/`STOP`/`TAKE_PROFIT` order; can be set to `OPPONENT`/
    /// `OPPONENT_5`/ `OPPONENT_10`/ `OPPONENT_20`: /`QUEUE`/ `QUEUE_5`/ `QUEUE_10`/ `QUEUE_20`;
    /// Can't be passed together with `price`
    std::optional<NewUmOrderPriceMatchEnum> price_match = std::nullopt;
    /// `EXPIRE_TAKER`: expire taker order when STP triggers/ `EXPIRE_MAKER`: expire taker order
    /// when STP triggers/ `EXPIRE_BOTH`: expire both orders when STP triggers
    std::optional<NewUmOrderSelfTradePreventionModeEnum> self_trade_prevention_mode = std::nullopt;
    /// order cancel time for timeInForce `GTD`, mandatory when `timeInforce` set to `GTD`; order
    /// the timestamp only retains second-level precision, ms part will be ignored; The goodTillDate
    /// timestamp must be greater than the current time plus 600 seconds and smaller than
    /// 253402300799000Mode. It must be sent in Hedge Mode.
    std::optional<std::int64_t> good_till_date = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryUmOrderParams {
    /// Symbol
    common::Required<std::string> symbol;
    std::optional<std::int64_t> order_id = std::nullopt;
    std::optional<std::string> orig_client_order_id = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct CmAccountTradeListParams {
    std::optional<std::string> symbol = std::nullopt;
    std::optional<std::string> pair = std::nullopt;
    /// Timestamp in ms to get funding from INCLUSIVE.
    std::optional<std::int64_t> start_time = std::nullopt;
    /// Timestamp in ms to get funding until INCLUSIVE.
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Trade ID to fetch from.
    std::optional<std::int64_t> from_id = std::nullopt;
    /// Number of results returned.
    std::optional<std::int64_t> limit = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct CmPositionAdlQuantileEstimationParams {
    std::optional<std::string> symbol = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct FuturesTradfiPerpsContractParams {
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetUmFuturesBnbBurnStatusParams {
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct ToggleBnbBurnOnUmFuturesTradeParams {
    /// "true": Fee Discount On; "false": Fee Discount Off
    common::Required<ToggleBnbBurnOnUmFuturesTradeFeeBurnEnum> fee_burn;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct MarginAccountBorrowParams {
    common::Required<std::string> asset;
    common::Required<common::Decimal> amount;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct MarginAccountNewOcoParams {
    common::Required<std::string> symbol;
    /// See enum definitions: order side
    common::Required<MarginAccountNewOcoSideEnum> side;
    common::Required<common::Decimal> quantity;
    common::Required<common::Decimal> price;
    common::Required<common::Decimal> stop_price;
    /// A unique Id for the entire orderList
    std::optional<std::string> list_client_order_id = std::nullopt;
    /// A unique Id for the limit order
    std::optional<std::string> limit_client_order_id = std::nullopt;
    std::optional<common::Decimal> limit_iceberg_qty = std::nullopt;
    /// A unique Id for the stop loss/stop loss limit leg
    std::optional<std::string> stop_client_order_id = std::nullopt;
    /// If provided, stopLimitTimeInForce is required.
    std::optional<common::Decimal> stop_limit_price = std::nullopt;
    std::optional<common::Decimal> stop_iceberg_qty = std::nullopt;
    /// Valid values are `GTC/FOK/IOC`
    std::optional<MarginAccountNewOcoStopLimitTimeInForceEnum> stop_limit_time_in_force =
        std::nullopt;
    /// Set the response JSON.
    std::optional<MarginAccountNewOcoNewOrderRespTypeEnum> new_order_resp_type = std::nullopt;
    /// NO_SIDE_EFFECT, MARGIN_BUY, AUTO_REPAY; default NO_SIDE_EFFECT.
    std::optional<MarginAccountNewOcoSideEffectTypeEnum> side_effect_type = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct MarginAccountRepayParams {
    common::Required<std::string> asset;
    common::Required<common::Decimal> amount;
    /// The value cannot be greater than 60000
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct MarginAccountRepayDebtParams {
    common::Required<std::string> asset;
    std::optional<std::string> amount = std::nullopt;
    /// Specific asset list to repay debt; Can be added in batch, separated by commas
    std::optional<std::string> specify_repay_assets = std::nullopt;
    /// The value cannot be greater than 60000
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct MarginAccountTradeListParams {
    /// Symbol
    common::Required<std::string> symbol;
    std::optional<std::int64_t> order_id = std::nullopt;
    /// Timestamp in ms to get funding from INCLUSIVE.
    std::optional<std::int64_t> start_time = std::nullopt;
    /// Timestamp in ms to get funding until INCLUSIVE.
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Trade ID to fetch from.
    std::optional<std::int64_t> from_id = std::nullopt;
    /// Number of results returned.
    std::optional<std::int64_t> limit = std::nullopt;
    /// Value cannot be greater than 60000
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryAllCmConditionalOrdersParams {
    std::optional<std::string> symbol = std::nullopt;
    std::optional<std::int64_t> strategy_id = std::nullopt;
    /// Timestamp in ms to get funding from INCLUSIVE.
    std::optional<std::int64_t> start_time = std::nullopt;
    /// Timestamp in ms to get funding until INCLUSIVE.
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Number of results returned.
    std::optional<std::int64_t> limit = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryAllCmOrdersParams {
    /// Symbol
    std::optional<std::string> symbol = std::nullopt;
    std::optional<std::string> pair = std::nullopt;
    std::optional<std::int64_t> order_id = std::nullopt;
    /// Timestamp in ms to get funding from INCLUSIVE.
    std::optional<std::int64_t> start_time = std::nullopt;
    /// Timestamp in ms to get funding until INCLUSIVE.
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Number of results returned.
    std::optional<std::int64_t> limit = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryAllCurrentCmOpenConditionalOrdersParams {
    std::optional<std::string> symbol = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryAllCurrentCmOpenOrdersParams {
    std::optional<std::string> symbol = std::nullopt;
    std::optional<std::string> pair = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryAllCurrentUmOpenAlgoOrdersParams {
    std::optional<std::string> algo_type = std::nullopt;
    std::optional<std::string> symbol = std::nullopt;
    std::optional<std::int64_t> algo_id = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryAllCurrentUmOpenOrdersParams {
    std::optional<std::string> symbol = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryAllMarginAccountOrdersParams {
    /// Symbol
    common::Required<std::string> symbol;
    std::optional<std::int64_t> order_id = std::nullopt;
    /// Timestamp in ms to get funding from INCLUSIVE.
    std::optional<std::int64_t> start_time = std::nullopt;
    /// Timestamp in ms to get funding until INCLUSIVE.
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Number of results returned.
    std::optional<std::int64_t> limit = std::nullopt;
    /// Value cannot be greater than 60000
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryAllUmOrdersParams {
    /// Symbol
    common::Required<std::string> symbol;
    std::optional<std::int64_t> order_id = std::nullopt;
    /// Timestamp in ms to get funding from INCLUSIVE.
    std::optional<std::int64_t> start_time = std::nullopt;
    /// Timestamp in ms to get funding until INCLUSIVE.
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Number of results returned.
    std::optional<std::int64_t> limit = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryCmConditionalOrderHistoryParams {
    /// Symbol
    common::Required<std::string> symbol;
    std::optional<std::int64_t> strategy_id = std::nullopt;
    std::optional<std::string> new_client_strategy_id = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryCmModifyOrderHistoryParams {
    /// Symbol
    common::Required<std::string> symbol;
    /// Order ID
    std::optional<std::int64_t> order_id = std::nullopt;
    /// Client order ID
    std::optional<std::string> orig_client_order_id = std::nullopt;
    /// Timestamp in ms to get funding from INCLUSIVE.
    std::optional<std::int64_t> start_time = std::nullopt;
    /// Timestamp in ms to get funding until INCLUSIVE.
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Number of results returned.
    std::optional<std::int64_t> limit = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryCurrentCmOpenConditionalOrderParams {
    /// Symbol
    common::Required<std::string> symbol;
    std::optional<std::int64_t> strategy_id = std::nullopt;
    std::optional<std::string> new_client_strategy_id = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryCurrentCmOpenOrderParams {
    /// Trading pair.
    common::Required<std::string> symbol;
    /// Order ID.
    std::optional<std::int64_t> order_id = std::nullopt;
    /// User-defined order ID.
    std::optional<std::string> orig_client_order_id = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryCurrentMarginOpenOrderParams {
    /// Symbol
    common::Required<std::string> symbol;
    /// Value cannot be greater than 60000
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryCurrentUmOpenAlgoOrderParams {
    /// Algo order ID
    std::optional<std::int64_t> algo_id = std::nullopt;
    /// Client algo order ID
    std::optional<std::string> client_algo_id = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryCurrentUmOpenOrderParams {
    /// Symbol
    common::Required<std::string> symbol;
    std::optional<std::int64_t> order_id = std::nullopt;
    std::optional<std::string> orig_client_order_id = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryMarginAccountsAllOcoParams {
    /// Trade ID to fetch from.
    std::optional<std::int64_t> from_id = std::nullopt;
    /// Timestamp in ms to get funding from INCLUSIVE.
    std::optional<std::int64_t> start_time = std::nullopt;
    /// Timestamp in ms to get funding until INCLUSIVE.
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Number of results returned.
    std::optional<std::int64_t> limit = std::nullopt;
    /// Value cannot be greater than 60000
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryMarginAccountsOpenOcoParams {
    /// Value cannot be greater than 60000
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryUmAlgoOrderHistoryParams {
    common::Required<std::string> symbol;
    /// Only return orders >= this algoId
    std::optional<std::int64_t> algo_id = std::nullopt;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Default 500; max 1000
    std::optional<std::int64_t> limit = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryUmModifyOrderHistoryParams {
    /// Symbol
    common::Required<std::string> symbol;
    /// Order ID
    std::optional<std::int64_t> order_id = std::nullopt;
    /// Client order ID
    std::optional<std::string> orig_client_order_id = std::nullopt;
    /// Timestamp in ms to get funding from INCLUSIVE.
    std::optional<std::int64_t> start_time = std::nullopt;
    /// Timestamp in ms to get funding until INCLUSIVE.
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Number of results returned.
    std::optional<std::int64_t> limit = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryUsersCmForceOrdersParams {
    std::optional<std::string> symbol = std::nullopt;
    /// `LIQUIDATION` for liquidation orders, `ADL` for ADL orders.
    std::optional<QueryUsersCmForceOrdersAutoCloseTypeEnum> auto_close_type = std::nullopt;
    /// Timestamp in ms to get funding from INCLUSIVE.
    std::optional<std::int64_t> start_time = std::nullopt;
    /// Timestamp in ms to get funding until INCLUSIVE.
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Number of results returned.
    std::optional<std::int64_t> limit = std::nullopt;
    /// The value cannot be greater than 60000
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryUsersMarginForceOrdersParams {
    /// Timestamp in ms to get funding from INCLUSIVE.
    std::optional<std::int64_t> start_time = std::nullopt;
    /// Timestamp in ms to get funding until INCLUSIVE.
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Current page number.
    std::optional<std::int64_t> current = std::nullopt;
    /// Number of results returned.
    std::optional<std::int64_t> size = std::nullopt;
    /// The value cannot be greater than 60000
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryUsersUmForceOrdersParams {
    std::optional<std::string> symbol = std::nullopt;
    /// `LIQUIDATION` for liquidation orders, `ADL` for ADL orders.
    std::optional<QueryUsersUmForceOrdersAutoCloseTypeEnum> auto_close_type = std::nullopt;
    /// Timestamp in ms to get funding from INCLUSIVE.
    std::optional<std::int64_t> start_time = std::nullopt;
    /// Timestamp in ms to get funding until INCLUSIVE.
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Number of results returned.
    std::optional<std::int64_t> limit = std::nullopt;
    /// The value cannot be greater than 60000
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct UmAccountTradeListParams {
    /// Symbol
    common::Required<std::string> symbol;
    /// Timestamp in ms to get funding from INCLUSIVE.
    std::optional<std::int64_t> start_time = std::nullopt;
    /// Timestamp in ms to get funding until INCLUSIVE.
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Trade ID to fetch from.
    std::optional<std::int64_t> from_id = std::nullopt;
    /// Number of results returned.
    std::optional<std::int64_t> limit = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct UmPositionAdlQuantileEstimationParams {
    std::optional<std::string> symbol = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT TradeApi {
public:
    explicit TradeApi(std::shared_ptr<common::RestClient> client);

    /// Cancel All CM Open Conditional Orders (TRADE)
    ///
    /// DELETE /papi/v1/cm/conditional/allOpenOrders.
    ///
    /// Cancel All CM Open Conditional Orders
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#cancel-all-cm-open-conditional-orders
    [[nodiscard]] common::RestApiResponse<CancelAllCmOpenConditionalOrdersResponse>
    cancel_all_cm_open_conditional_orders(
        const CancelAllCmOpenConditionalOrdersParams& params) const;

    /// Asynchronous `cancel_all_cm_open_conditional_orders()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<CancelAllCmOpenConditionalOrdersResponse>)`.
    template <class CompletionToken>
    auto async_cancel_all_cm_open_conditional_orders(
        const CancelAllCmOpenConditionalOrdersParams& params, CompletionToken&& token) const {
        return common::async_send<CancelAllCmOpenConditionalOrdersResponse>(
            client_, cancel_all_cm_open_conditional_orders_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Cancel All CM Open Orders (TRADE)
    ///
    /// DELETE /papi/v1/cm/allOpenOrders.
    ///
    /// Cancel all active LIMIT orders on specific symbol
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#cancel-all-cm-open-orders
    [[nodiscard]] common::RestApiResponse<CancelAllCmOpenOrdersResponse>
    cancel_all_cm_open_orders(const CancelAllCmOpenOrdersParams& params) const;

    /// Asynchronous `cancel_all_cm_open_orders()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<CancelAllCmOpenOrdersResponse>)`.
    template <class CompletionToken>
    auto async_cancel_all_cm_open_orders(const CancelAllCmOpenOrdersParams& params,
                                         CompletionToken&& token) const {
        return common::async_send<CancelAllCmOpenOrdersResponse>(
            client_, cancel_all_cm_open_orders_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Cancel All UM Algo Open Orders (TRADE)
    ///
    /// DELETE /papi/v1/um/algo/allOpenOrders.
    ///
    /// Cancel All UM Algo Open Orders
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#cancel-all-um-algo-open-orders
    [[nodiscard]] common::RestApiResponse<CancelAllUmAlgoOpenOrdersResponse>
    cancel_all_um_algo_open_orders(const CancelAllUmAlgoOpenOrdersParams& params) const;

    /// Asynchronous `cancel_all_um_algo_open_orders()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<CancelAllUmAlgoOpenOrdersResponse>)`.
    template <class CompletionToken>
    auto async_cancel_all_um_algo_open_orders(const CancelAllUmAlgoOpenOrdersParams& params,
                                              CompletionToken&& token) const {
        return common::async_send<CancelAllUmAlgoOpenOrdersResponse>(
            client_, cancel_all_um_algo_open_orders_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Cancel All UM Open Orders (TRADE)
    ///
    /// DELETE /papi/v1/um/allOpenOrders.
    ///
    /// Cancel all active LIMIT orders on specific symbol
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#cancel-all-um-open-orders
    [[nodiscard]] common::RestApiResponse<CancelAllUmOpenOrdersResponse>
    cancel_all_um_open_orders(const CancelAllUmOpenOrdersParams& params) const;

    /// Asynchronous `cancel_all_um_open_orders()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<CancelAllUmOpenOrdersResponse>)`.
    template <class CompletionToken>
    auto async_cancel_all_um_open_orders(const CancelAllUmOpenOrdersParams& params,
                                         CompletionToken&& token) const {
        return common::async_send<CancelAllUmOpenOrdersResponse>(
            client_, cancel_all_um_open_orders_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Cancel CM Conditional Order (TRADE)
    ///
    /// DELETE /papi/v1/cm/conditional/order.
    ///
    /// Cancel CM Conditional Order
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Either `strategyId` or `newClientStrategyId` must be sent.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#cancel-cm-conditional-order
    [[nodiscard]] common::RestApiResponse<CancelCmConditionalOrderResponse>
    cancel_cm_conditional_order(const CancelCmConditionalOrderParams& params) const;

    /// Asynchronous `cancel_cm_conditional_order()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<CancelCmConditionalOrderResponse>)`.
    template <class CompletionToken>
    auto async_cancel_cm_conditional_order(const CancelCmConditionalOrderParams& params,
                                           CompletionToken&& token) const {
        return common::async_send<CancelCmConditionalOrderResponse>(
            client_, cancel_cm_conditional_order_request(params),
            std::forward<CompletionToken>(token));
    }

    /// New CM Conditional Order (TRADE)
    ///
    /// POST /papi/v1/cm/conditional/order.
    ///
    /// New CM Conditional Order
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Additional mandatory parameters based on type:
    ///   - Order with type `STOP/TAKE_PROFIT`, parameter `timeInForce` can be sent ( default
    ///   `GTC`).
    ///   - Condition orders will be triggered when:
    ///   - `STOP`, `STOP_MARKET`:
    ///   - BUY: "MARK_PRICE" >= `stopPrice`
    ///   - SELL: "MARK_PRICE" <= `stopPrice`
    ///   - `TAKE_PROFIT`, `TAKE_PROFIT_MARKET`:
    ///   - BUY: "MARK_PRICE" <= `stopPrice`
    ///   - SELL: "MARK_PRICE" >= `stopPrice`
    ///   - `TRAILING_STOP_MARKET`:
    ///   - BUY: the lowest mark price after order placed <= `activationPrice`, and the latest mark
    ///   price >= the lowest mark price * (1 + `callbackRate`)
    ///   - SELL: the highest mark price after order placed >= `activationPrice`, and the latest
    ///   mark price <= the highest mark price * (1 - `callbackRate`)
    ///   - For `TRAILING_STOP_MARKET`, if you got such error code. `{"code": -2021, "msg": "Order
    ///   would immediately trigger."}` means that the parameters you send do not meet the following
    ///   requirements:
    ///   - BUY: `activationPrice` should be smaller than latest mark price.
    ///   - SELL: `activationPrice` should be larger than latest mark price.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#new-cm-conditional-order
    [[nodiscard]] common::RestApiResponse<NewCmConditionalOrderResponse>
    new_cm_conditional_order(const NewCmConditionalOrderParams& params) const;

    /// Asynchronous `new_cm_conditional_order()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<NewCmConditionalOrderResponse>)`.
    template <class CompletionToken>
    auto async_new_cm_conditional_order(const NewCmConditionalOrderParams& params,
                                        CompletionToken&& token) const {
        return common::async_send<NewCmConditionalOrderResponse>(
            client_, new_cm_conditional_order_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Cancel CM Order (TRADE)
    ///
    /// DELETE /papi/v1/cm/order.
    ///
    /// Cancel an active LIMIT order
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Either `orderId` or `origClientOrderId` must be sent.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#cancel-cm-order
    [[nodiscard]] common::RestApiResponse<CancelCmOrderResponse>
    cancel_cm_order(const CancelCmOrderParams& params) const;

    /// Asynchronous `cancel_cm_order()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<CancelCmOrderResponse>)`.
    template <class CompletionToken>
    auto async_cancel_cm_order(const CancelCmOrderParams& params, CompletionToken&& token) const {
        return common::async_send<CancelCmOrderResponse>(client_, cancel_cm_order_request(params),
                                                         std::forward<CompletionToken>(token));
    }

    /// Modify CM Order (TRADE)
    ///
    /// PUT /papi/v1/cm/order.
    ///
    /// Order modify function, currently only LIMIT order modification is supported, modified orders
    /// will be reordered in the match queue
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Either `orderId` or `origClientOrderId` must be sent, and the `orderId` will prevail if
    /// both are sent.
    /// - Both `quantity` and `price` must be sent
    /// - When the new `quantity` or `price` doesn't satisfy PRICE_FILTER / PERCENT_FILTER /
    /// LOT_SIZE, amendment will be rejected and the order will stay as it is.
    /// - However the order will be cancelled by the amendment in the following situations:
    ///   - when the order is in partially filled status and the new `quantity` <= `executedQty`
    ///   - When the order is `GTX` and the new price will cause it to be executed immediately
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#modify-cm-order
    [[nodiscard]] common::RestApiResponse<ModifyCmOrderResponse>
    modify_cm_order(const ModifyCmOrderParams& params) const;

    /// Asynchronous `modify_cm_order()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<ModifyCmOrderResponse>)`.
    template <class CompletionToken>
    auto async_modify_cm_order(const ModifyCmOrderParams& params, CompletionToken&& token) const {
        return common::async_send<ModifyCmOrderResponse>(client_, modify_cm_order_request(params),
                                                         std::forward<CompletionToken>(token));
    }

    /// New CM Order (TRADE)
    ///
    /// POST /papi/v1/cm/order.
    ///
    /// Place new CM order
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Additional mandatory parameters based on `type`:
    ///   - If `newOrderRespType` is sent as `RESULT` :
    ///   - `MARKET` order: the final FILLED result of the order will be return directly.
    ///   - `LIMIT` order with special `timeInForce`: the final status result of the order(FILLED or
    ///   EXPIRED) will be returned directly.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#new-cm-order
    [[nodiscard]] common::RestApiResponse<NewCmOrderResponse>
    new_cm_order(const NewCmOrderParams& params) const;

    /// Asynchronous `new_cm_order()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<NewCmOrderResponse>)`.
    template <class CompletionToken>
    auto async_new_cm_order(const NewCmOrderParams& params, CompletionToken&& token) const {
        return common::async_send<NewCmOrderResponse>(client_, new_cm_order_request(params),
                                                      std::forward<CompletionToken>(token));
    }

    /// Query CM Order (USER_DATA)
    ///
    /// GET /papi/v1/cm/order.
    ///
    /// Check an CM order's status.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Either `orderId` or `origClientOrderId` must be sent.
    /// - These orders will not be found:
    ///   - order status is `CANCELED` or `EXPIRED`, **AND**
    ///   - order has NO filled trade, **AND**
    ///   - created time + 3 days < current time
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#query-cm-order
    [[nodiscard]] common::RestApiResponse<QueryCmOrderResponse>
    query_cm_order(const QueryCmOrderParams& params) const;

    /// Asynchronous `query_cm_order()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<QueryCmOrderResponse>)`.
    template <class CompletionToken>
    auto async_query_cm_order(const QueryCmOrderParams& params, CompletionToken&& token) const {
        return common::async_send<QueryCmOrderResponse>(client_, query_cm_order_request(params),
                                                        std::forward<CompletionToken>(token));
    }

    /// Cancel Margin Account All Open Orders on a Symbol (TRADE)
    ///
    /// DELETE /papi/v1/margin/allOpenOrders.
    ///
    /// Cancel Margin Account All Open Orders on a Symbol
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#cancel-margin-account-all-open-orders-on-asymbol
    [[nodiscard]] common::RestApiResponse<
        std::vector<CancelMarginAccountAllOpenOrdersOnASymbolResponseInner>>
    cancel_margin_account_all_open_orders_on_a_symbol(
        const CancelMarginAccountAllOpenOrdersOnASymbolParams& params) const;

    /// Asynchronous `cancel_margin_account_all_open_orders_on_a_symbol()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<CancelMarginAccountAllOpenOrdersOnASymbolResponseInner>>)`.
    template <class CompletionToken>
    auto async_cancel_margin_account_all_open_orders_on_a_symbol(
        const CancelMarginAccountAllOpenOrdersOnASymbolParams& params,
        CompletionToken&& token) const {
        return common::async_send<
            std::vector<CancelMarginAccountAllOpenOrdersOnASymbolResponseInner>>(
            client_, cancel_margin_account_all_open_orders_on_a_symbol_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Cancel Margin Account OCO Orders (TRADE)
    ///
    /// DELETE /papi/v1/margin/orderList.
    ///
    /// Cancel Margin Account OCO Orders
    ///
    /// Weight(IP): 2
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Additional notes: Canceling an individual leg will cancel the entire OCO
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#cancel-margin-account-oco-orders
    [[nodiscard]] common::RestApiResponse<CancelMarginAccountOcoOrdersResponse>
    cancel_margin_account_oco_orders(const CancelMarginAccountOcoOrdersParams& params) const;

    /// Asynchronous `cancel_margin_account_oco_orders()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<CancelMarginAccountOcoOrdersResponse>)`.
    template <class CompletionToken>
    auto async_cancel_margin_account_oco_orders(const CancelMarginAccountOcoOrdersParams& params,
                                                CompletionToken&& token) const {
        return common::async_send<CancelMarginAccountOcoOrdersResponse>(
            client_, cancel_margin_account_oco_orders_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Query Margin Account's OCO (USER_DATA)
    ///
    /// GET /papi/v1/margin/orderList.
    ///
    /// Retrieves a specific OCO based on provided optional parameters
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#query-margin-accounts-oco
    [[nodiscard]] common::RestApiResponse<QueryMarginAccountsOcoResponse>
    query_margin_accounts_oco(const QueryMarginAccountsOcoParams& params = {}) const;

    /// Asynchronous `query_margin_accounts_oco()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<QueryMarginAccountsOcoResponse>)`.
    template <class CompletionToken>
    auto async_query_margin_accounts_oco(const QueryMarginAccountsOcoParams& params,
                                         CompletionToken&& token) const {
        return common::async_send<QueryMarginAccountsOcoResponse>(
            client_, query_margin_accounts_oco_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Cancel Margin Account Order (TRADE)
    ///
    /// DELETE /papi/v1/margin/order.
    ///
    /// Cancel Margin Account Order
    ///
    /// Weight(IP): 2
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Either `orderId` or `origClientOrderId` must be sent.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#cancel-margin-account-order
    [[nodiscard]] common::RestApiResponse<CancelMarginAccountOrderResponse>
    cancel_margin_account_order(const CancelMarginAccountOrderParams& params) const;

    /// Asynchronous `cancel_margin_account_order()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<CancelMarginAccountOrderResponse>)`.
    template <class CompletionToken>
    auto async_cancel_margin_account_order(const CancelMarginAccountOrderParams& params,
                                           CompletionToken&& token) const {
        return common::async_send<CancelMarginAccountOrderResponse>(
            client_, cancel_margin_account_order_request(params),
            std::forward<CompletionToken>(token));
    }

    /// New Margin Order (TRADE)
    ///
    /// POST /papi/v1/margin/order.
    ///
    /// New Margin Order
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#new-margin-order
    [[nodiscard]] common::RestApiResponse<NewMarginOrderResponse>
    new_margin_order(const NewMarginOrderParams& params) const;

    /// Asynchronous `new_margin_order()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<NewMarginOrderResponse>)`.
    template <class CompletionToken>
    auto async_new_margin_order(const NewMarginOrderParams& params, CompletionToken&& token) const {
        return common::async_send<NewMarginOrderResponse>(client_, new_margin_order_request(params),
                                                          std::forward<CompletionToken>(token));
    }

    /// Query Margin Account Order (USER_DATA)
    ///
    /// GET /papi/v1/margin/order.
    ///
    /// Query Margin Account Order
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Either `orderId` or `origClientOrderId` must be sent.
    /// - For some historical orders, `cummulativeQuoteQty < 0` means the data is unavailable at
    /// this time.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#query-margin-account-order
    [[nodiscard]] common::RestApiResponse<QueryMarginAccountOrderResponse>
    query_margin_account_order(const QueryMarginAccountOrderParams& params) const;

    /// Asynchronous `query_margin_account_order()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<QueryMarginAccountOrderResponse>)`.
    template <class CompletionToken>
    auto async_query_margin_account_order(const QueryMarginAccountOrderParams& params,
                                          CompletionToken&& token) const {
        return common::async_send<QueryMarginAccountOrderResponse>(
            client_, query_margin_account_order_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Cancel UM Algo Order (TRADE)
    ///
    /// DELETE /papi/v1/um/algo/order.
    ///
    /// Cancel an active UM algo order
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Either `algoId` or `clientAlgoId` must be sent.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#cancel-um-algo-order
    [[nodiscard]] common::RestApiResponse<CancelUmAlgoOrderResponse>
    cancel_um_algo_order(const CancelUmAlgoOrderParams& params = {}) const;

    /// Asynchronous `cancel_um_algo_order()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<CancelUmAlgoOrderResponse>)`.
    template <class CompletionToken>
    auto async_cancel_um_algo_order(const CancelUmAlgoOrderParams& params,
                                    CompletionToken&& token) const {
        return common::async_send<CancelUmAlgoOrderResponse>(
            client_, cancel_um_algo_order_request(params), std::forward<CompletionToken>(token));
    }

    /// New UM Algo Order (TRADE)
    ///
    /// POST /papi/v1/um/algo/order.
    ///
    /// Place new UM conditional order
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Algo order with type `STOP`, parameter `timeInForce` can be sent (default `GTC`).
    /// - Algo order with type `TAKE_PROFIT`, parameter `timeInForce` can be sent (default `GTC`).
    /// - Condition orders will be triggered when price reaches the `triggerPrice`.
    /// - `STOP`, `STOP_MARKET`: BUY: latest price >= `triggerPrice`; SELL: latest price <=
    /// `triggerPrice`.
    /// - `TAKE_PROFIT`, `TAKE_PROFIT_MARKET`: BUY: latest price <= `triggerPrice`; SELL: latest
    /// price >= `triggerPrice`.
    /// - `TRAILING_STOP_MARKET`: BUY: lowest price after order placed <= `activatePrice`, and
    /// latest price >= lowest price * (1 + `callbackRate`); SELL: highest price after order placed
    /// >= `activatePrice`, and latest price <= highest price * (1 - `callbackRate`).
    /// - `STOP_MARKET`, `TAKE_PROFIT_MARKET` with `closePosition`=`true`: follow the same rules for
    /// conditional orders; if triggered, close all current long position (if `SELL`) or current
    /// short position (if `BUY`); cannot be used with `quantity` parameter; cannot be used with
    /// `reduceOnly` parameter; in Hedge Mode, cannot be used with `BUY` orders in `LONG` position
    /// side, and cannot be used with `SELL` orders in `SHORT` position side.
    /// - `selfTradePreventionMode` is only effective when `timeInForce` set to `IOC` or `GTC` or
    /// `GTD`.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#new-um-algo-order
    [[nodiscard]] common::RestApiResponse<NewUmAlgoOrderResponse>
    new_um_algo_order(const NewUmAlgoOrderParams& params) const;

    /// Asynchronous `new_um_algo_order()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<NewUmAlgoOrderResponse>)`.
    template <class CompletionToken>
    auto async_new_um_algo_order(const NewUmAlgoOrderParams& params,
                                 CompletionToken&& token) const {
        return common::async_send<NewUmAlgoOrderResponse>(
            client_, new_um_algo_order_request(params), std::forward<CompletionToken>(token));
    }

    /// Cancel UM Order (TRADE)
    ///
    /// DELETE /papi/v1/um/order.
    ///
    /// Cancel an active UM LIMIT order
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Either `orderId` or `origClientOrderId` must be sent.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#cancel-um-order
    [[nodiscard]] common::RestApiResponse<CancelUmOrderResponse>
    cancel_um_order(const CancelUmOrderParams& params) const;

    /// Asynchronous `cancel_um_order()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<CancelUmOrderResponse>)`.
    template <class CompletionToken>
    auto async_cancel_um_order(const CancelUmOrderParams& params, CompletionToken&& token) const {
        return common::async_send<CancelUmOrderResponse>(client_, cancel_um_order_request(params),
                                                         std::forward<CompletionToken>(token));
    }

    /// Modify UM Order (TRADE)
    ///
    /// PUT /papi/v1/um/order.
    ///
    /// Order modify function, currently only LIMIT order modification is supported, modified orders
    /// will be reordered in the match queue
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Either orderId or origClientOrderId must be sent, and the orderId will prevail if both are
    /// sent.
    /// - Both quantity and price must be sent
    /// - When the new quantity or price doesn't satisfy PRICE_FILTER / PERCENT_FILTER / LOT_SIZE,
    /// amendment will be rejected and the order will stay as it is.
    /// - However the order will be cancelled by the amendment in the following situations:
    ///   - when the order is in partially filled status and the new quantity <= executedQty
    ///   - When the order is GTX and the new price will cause it to be executed immediately
    /// - The amendment keeps the order's original selfTradePreventionMode.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#modify-um-order
    [[nodiscard]] common::RestApiResponse<ModifyUmOrderResponse>
    modify_um_order(const ModifyUmOrderParams& params) const;

    /// Asynchronous `modify_um_order()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<ModifyUmOrderResponse>)`.
    template <class CompletionToken>
    auto async_modify_um_order(const ModifyUmOrderParams& params, CompletionToken&& token) const {
        return common::async_send<ModifyUmOrderResponse>(client_, modify_um_order_request(params),
                                                         std::forward<CompletionToken>(token));
    }

    /// New UM Order (TRADE)
    ///
    /// POST /papi/v1/um/order.
    ///
    /// Place new UM order
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Additional mandatory parameters based on type:
    ///   - If `newOrderRespType` is sent as `RESULT` :
    ///   - `MARKET` order: the final FILLED result of the order will be return directly.
    ///   - `LIMIT` order with special `timeInForce`: the final status result of the order(FILLED or
    ///   EXPIRED) will be returned directly.
    ///   - `selfTradePreventionMode` is only effective when `timeInForce` set to `IOC` or `GTC` or
    ///   `GTD`.
    ///   - In extreme market conditions, timeInForce `GTD` order auto cancel time might be delayed
    ///   comparing to `goodTillDate`
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#new-um-order
    [[nodiscard]] common::RestApiResponse<NewUmOrderResponse>
    new_um_order(const NewUmOrderParams& params) const;

    /// Asynchronous `new_um_order()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<NewUmOrderResponse>)`.
    template <class CompletionToken>
    auto async_new_um_order(const NewUmOrderParams& params, CompletionToken&& token) const {
        return common::async_send<NewUmOrderResponse>(client_, new_um_order_request(params),
                                                      std::forward<CompletionToken>(token));
    }

    /// Query UM Order (USER_DATA)
    ///
    /// GET /papi/v1/um/order.
    ///
    /// Check an UM order's status.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - These orders will not be found:
    ///   - Either `orderId` or `origClientOrderId` must be sent.
    ///   - order status is `CANCELED` or `EXPIRED`, **AND**
    ///   - order has NO filled trade, **AND**
    ///   - created time + 3 days < current time
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#query-um-order
    [[nodiscard]] common::RestApiResponse<QueryUmOrderResponse>
    query_um_order(const QueryUmOrderParams& params) const;

    /// Asynchronous `query_um_order()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<QueryUmOrderResponse>)`.
    template <class CompletionToken>
    auto async_query_um_order(const QueryUmOrderParams& params, CompletionToken&& token) const {
        return common::async_send<QueryUmOrderResponse>(client_, query_um_order_request(params),
                                                        std::forward<CompletionToken>(token));
    }

    /// CM Account Trade List (USER_DATA)
    ///
    /// GET /papi/v1/cm/userTrades.
    ///
    /// Get trades for a specific account and CM symbol.
    ///
    /// Weight: - 20 with `symbol`
    /// - 40 with `pair`
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Either `symbol` or `pair` must be sent
    /// - `symbol` and `pair` cannot be sent together
    /// - `pair` and `fromId` cannot be sent together
    /// - `OrderId` can only be sent together with symbol
    /// - If a `pair` is sent, tickers for all symbols of the `pair` will be returned
    /// - The parameter `fromId` cannot be sent with `startTime` or `endTime`
    /// - If `startTime` and `endTime` are both not sent, then the last '24 hours' data will be
    /// returned.
    /// - The time between `startTime` and `endTime` cannot be longer than 24 hours.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#cm-account-trade-list
    [[nodiscard]] common::RestApiResponse<std::vector<CmAccountTradeListResponseInner>>
    cm_account_trade_list(const CmAccountTradeListParams& params = {}) const;

    /// Asynchronous `cm_account_trade_list()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<CmAccountTradeListResponseInner>>)`.
    template <class CompletionToken>
    auto async_cm_account_trade_list(const CmAccountTradeListParams& params,
                                     CompletionToken&& token) const {
        return common::async_send<std::vector<CmAccountTradeListResponseInner>>(
            client_, cm_account_trade_list_request(params), std::forward<CompletionToken>(token));
    }

    /// CM Position ADL Quantile Estimation (USER_DATA)
    ///
    /// GET /papi/v1/cm/adlQuantile.
    ///
    /// Query CM Position ADL Quantile Estimation
    /// * Values update every 30s.
    /// * Values 0, 1, 2, 3, 4 shows the queue position and possibility of ADL from low to high.
    /// * For positions of the symbol are in One-way Mode or isolated margined in Hedge Mode,
    /// "LONG", "SHORT", and "BOTH" will be returned to show the positions' adl quantiles of
    /// different position sides.
    /// * If the positions of the symbol are crossed margined in Hedge Mode:
    /// * "HEDGE" as a sign will be returned instead of "BOTH";
    /// * A same value caculated on unrealized pnls on long and short sides' positions will be shown
    /// for "LONG" and "SHORT" when there are positions in both of long and short sides.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#cm-position-adl-quantile-estimation
    [[nodiscard]] common::RestApiResponse<std::vector<CmPositionAdlQuantileEstimationResponseInner>>
    cm_position_adl_quantile_estimation(
        const CmPositionAdlQuantileEstimationParams& params = {}) const;

    /// Asynchronous `cm_position_adl_quantile_estimation()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<CmPositionAdlQuantileEstimationResponseInner>>)`.
    template <class CompletionToken>
    auto
    async_cm_position_adl_quantile_estimation(const CmPositionAdlQuantileEstimationParams& params,
                                              CompletionToken&& token) const {
        return common::async_send<std::vector<CmPositionAdlQuantileEstimationResponseInner>>(
            client_, cm_position_adl_quantile_estimation_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Futures TradFi Perps Contract (USER_DATA)
    ///
    /// POST /papi/v1/um/stock/contract.
    ///
    /// Sign TradFi-Perps agreement contract
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#futures-tradfi-perps-contract
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

    /// Get UM Futures BNB Burn Status (USER_DATA)
    ///
    /// GET /papi/v1/um/feeBurn.
    ///
    /// Get user's BNB Fee Discount for UM Futures (Fee Discount On or Fee Discount Off )
    ///
    /// Weight(IP): 30
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#get-um-futures-bnb-burn-status
    [[nodiscard]] common::RestApiResponse<GetUmFuturesBnbBurnStatusResponse>
    get_um_futures_bnb_burn_status(const GetUmFuturesBnbBurnStatusParams& params = {}) const;

    /// Asynchronous `get_um_futures_bnb_burn_status()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetUmFuturesBnbBurnStatusResponse>)`.
    template <class CompletionToken>
    auto async_get_um_futures_bnb_burn_status(const GetUmFuturesBnbBurnStatusParams& params,
                                              CompletionToken&& token) const {
        return common::async_send<GetUmFuturesBnbBurnStatusResponse>(
            client_, get_um_futures_bnb_burn_status_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Toggle BNB Burn On UM Futures Trade (TRADE)
    ///
    /// POST /papi/v1/um/feeBurn.
    ///
    /// Change user's BNB Fee Discount for UM Futures (Fee Discount On or Fee Discount Off ) on
    /// ***EVERY symbol***
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - The BNB would not be collected from UM-PM account to the Portfolio Margin account.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#toggle-bnb-burn-on-um-futures-trade
    [[nodiscard]] common::RestApiResponse<ToggleBnbBurnOnUmFuturesTradeResponse>
    toggle_bnb_burn_on_um_futures_trade(const ToggleBnbBurnOnUmFuturesTradeParams& params) const;

    /// Asynchronous `toggle_bnb_burn_on_um_futures_trade()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<ToggleBnbBurnOnUmFuturesTradeResponse>)`.
    template <class CompletionToken>
    auto
    async_toggle_bnb_burn_on_um_futures_trade(const ToggleBnbBurnOnUmFuturesTradeParams& params,
                                              CompletionToken&& token) const {
        return common::async_send<ToggleBnbBurnOnUmFuturesTradeResponse>(
            client_, toggle_bnb_burn_on_um_futures_trade_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Margin Account Borrow (MARGIN)
    ///
    /// POST /papi/v1/marginLoan.
    ///
    /// Apply for a margin loan.
    ///
    /// Weight(IP): 100
    ///
    /// Security Type: MARGIN
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#margin-account-borrow
    [[nodiscard]] common::RestApiResponse<MarginAccountBorrowResponse>
    margin_account_borrow(const MarginAccountBorrowParams& params) const;

    /// Asynchronous `margin_account_borrow()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<MarginAccountBorrowResponse>)`.
    template <class CompletionToken>
    auto async_margin_account_borrow(const MarginAccountBorrowParams& params,
                                     CompletionToken&& token) const {
        return common::async_send<MarginAccountBorrowResponse>(
            client_, margin_account_borrow_request(params), std::forward<CompletionToken>(token));
    }

    /// Margin Account New OCO (TRADE)
    ///
    /// POST /papi/v1/margin/order/oco.
    ///
    /// Send in a new OCO for a margin account
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Other Info:
    ///   - Price Restrictions:
    ///   - `SELL`: Limit Price > Last Price > Stop Price
    ///   - `BUY`: Limit Price  * Quantity Restrictions:
    ///   - Both legs must have the same quantity
    ///   - `ICEBERG` quantities however do not have to be the same.
    ///   - Order Rate Limit
    ///   - `OCO` counts as 2 orders against the order rate limit.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#margin-account-new-oco
    [[nodiscard]] common::RestApiResponse<MarginAccountNewOcoResponse>
    margin_account_new_oco(const MarginAccountNewOcoParams& params) const;

    /// Asynchronous `margin_account_new_oco()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<MarginAccountNewOcoResponse>)`.
    template <class CompletionToken>
    auto async_margin_account_new_oco(const MarginAccountNewOcoParams& params,
                                      CompletionToken&& token) const {
        return common::async_send<MarginAccountNewOcoResponse>(
            client_, margin_account_new_oco_request(params), std::forward<CompletionToken>(token));
    }

    /// Margin Account Repay (MARGIN)
    ///
    /// POST /papi/v1/repayLoan.
    ///
    /// Repay for a margin loan.
    ///
    /// Weight(IP): 100
    ///
    /// Security Type: MARGIN
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#margin-account-repay
    [[nodiscard]] common::RestApiResponse<MarginAccountRepayResponse>
    margin_account_repay(const MarginAccountRepayParams& params) const;

    /// Asynchronous `margin_account_repay()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<MarginAccountRepayResponse>)`.
    template <class CompletionToken>
    auto async_margin_account_repay(const MarginAccountRepayParams& params,
                                    CompletionToken&& token) const {
        return common::async_send<MarginAccountRepayResponse>(
            client_, margin_account_repay_request(params), std::forward<CompletionToken>(token));
    }

    /// Margin Account Repay Debt (TRADE)
    ///
    /// POST /papi/v1/margin/repay-debt.
    ///
    /// Repay debt for a margin loan.
    ///
    /// Weight(IP): 3000
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - The repay asset amount cannot exceed 50000 USD equivalent value for a single request.
    /// - If `amount` is not sent, all the asset loan will be repaid if having enough specific repay
    /// assets.
    /// - If `amount` is sent, only the certain amount of the asset loan will be repaid if having
    /// enough specific repay assets.
    /// - The system will use the same asset to repay the loan first (if have) no matter whether put
    /// the asset in `specifyRepayAssets`
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#margin-account-repay-debt
    [[nodiscard]] common::RestApiResponse<MarginAccountRepayDebtResponse>
    margin_account_repay_debt(const MarginAccountRepayDebtParams& params) const;

    /// Asynchronous `margin_account_repay_debt()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<MarginAccountRepayDebtResponse>)`.
    template <class CompletionToken>
    auto async_margin_account_repay_debt(const MarginAccountRepayDebtParams& params,
                                         CompletionToken&& token) const {
        return common::async_send<MarginAccountRepayDebtResponse>(
            client_, margin_account_repay_debt_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Margin Account Trade List (USER_DATA)
    ///
    /// GET /papi/v1/margin/myTrades.
    ///
    /// Margin Account Trade List
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - **Note:** * If `fromId` is set, returns orders with id >= `fromId`; otherwise returns
    /// recent order history.
    /// - The interval between `startTime` and `endTime` must be less than 24 hours.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#margin-account-trade-list
    [[nodiscard]] common::RestApiResponse<std::vector<MarginAccountTradeListResponseInner>>
    margin_account_trade_list(const MarginAccountTradeListParams& params) const;

    /// Asynchronous `margin_account_trade_list()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<MarginAccountTradeListResponseInner>>)`.
    template <class CompletionToken>
    auto async_margin_account_trade_list(const MarginAccountTradeListParams& params,
                                         CompletionToken&& token) const {
        return common::async_send<std::vector<MarginAccountTradeListResponseInner>>(
            client_, margin_account_trade_list_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Query All CM Conditional Orders (USER_DATA)
    ///
    /// GET /papi/v1/cm/conditional/allOrders.
    ///
    /// Query All CM Conditional Orders
    ///
    /// Weight: - 1 for a single `symbol`
    /// - 40 when `symbol` is omitted
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - These orders will not be found:
    ///   - order strategyStatus is `CANCELED` or `EXPIRED`, **AND**
    ///   - order has NO filled trade, **AND**
    ///   - created time + 7 days  * The query time period must be less than 7 days( default as the
    ///   recent 7 days).
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#query-all-cm-conditional-orders
    [[nodiscard]] common::RestApiResponse<std::vector<QueryAllCmConditionalOrdersResponseInner>>
    query_all_cm_conditional_orders(const QueryAllCmConditionalOrdersParams& params = {}) const;

    /// Asynchronous `query_all_cm_conditional_orders()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<QueryAllCmConditionalOrdersResponseInner>>)`.
    template <class CompletionToken>
    auto async_query_all_cm_conditional_orders(const QueryAllCmConditionalOrdersParams& params,
                                               CompletionToken&& token) const {
        return common::async_send<std::vector<QueryAllCmConditionalOrdersResponseInner>>(
            client_, query_all_cm_conditional_orders_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Query All CM Orders (USER_DATA)
    ///
    /// GET /papi/v1/cm/allOrders.
    ///
    /// Get all account CM orders; active, canceled, or filled.
    ///
    /// Weight: - 20 with `symbol`
    /// - 40 with `pair`
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Either `symbol` or `pair` must be sent.
    /// - If `orderId` is set, it will get orders >= that orderId. Otherwise most recent orders are
    /// returned.
    /// - These orders will not be found:
    ///   - order status is `CANCELED` or `EXPIRED`, **AND**
    ///   - order has NO filled trade, **AND**
    ///   - created time + 3 days < current time
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#query-all-cm-orders
    [[nodiscard]] common::RestApiResponse<std::vector<QueryAllCmOrdersResponseInner>>
    query_all_cm_orders(const QueryAllCmOrdersParams& params = {}) const;

    /// Asynchronous `query_all_cm_orders()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<QueryAllCmOrdersResponseInner>>)`.
    template <class CompletionToken>
    auto async_query_all_cm_orders(const QueryAllCmOrdersParams& params,
                                   CompletionToken&& token) const {
        return common::async_send<std::vector<QueryAllCmOrdersResponseInner>>(
            client_, query_all_cm_orders_request(params), std::forward<CompletionToken>(token));
    }

    /// Query All Current CM Open Conditional Orders (USER_DATA)
    ///
    /// GET /papi/v1/cm/conditional/openOrders.
    ///
    /// Get all open conditional orders on a symbol. **Careful** when accessing this with no symbol.
    ///
    /// Weight: - 1 for a single `symbol`
    /// - 40 when `symbol` is omitted
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If the symbol is not sent, orders for all symbols will be returned in an array.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#query-all-current-cm-open-conditional-orders
    [[nodiscard]] common::RestApiResponse<
        std::vector<QueryAllCurrentCmOpenConditionalOrdersResponseInner>>
    query_all_current_cm_open_conditional_orders(
        const QueryAllCurrentCmOpenConditionalOrdersParams& params = {}) const;

    /// Asynchronous `query_all_current_cm_open_conditional_orders()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<QueryAllCurrentCmOpenConditionalOrdersResponseInner>>)`.
    template <class CompletionToken>
    auto async_query_all_current_cm_open_conditional_orders(
        const QueryAllCurrentCmOpenConditionalOrdersParams& params, CompletionToken&& token) const {
        return common::async_send<std::vector<QueryAllCurrentCmOpenConditionalOrdersResponseInner>>(
            client_, query_all_current_cm_open_conditional_orders_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Query All Current CM Open Orders (USER_DATA)
    ///
    /// GET /papi/v1/cm/openOrders.
    ///
    /// Get all open orders on a symbol.
    ///
    /// * If the symbol is not sent, orders for all symbols will be returned in an array.
    ///
    /// Weight: - 1 for a single `symbol`
    /// - 40 when `symbol` is omitted
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#query-all-current-cm-open-orders
    [[nodiscard]] common::RestApiResponse<std::vector<QueryAllCmOrdersResponseInner>>
    query_all_current_cm_open_orders(const QueryAllCurrentCmOpenOrdersParams& params = {}) const;

    /// Asynchronous `query_all_current_cm_open_orders()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<QueryAllCmOrdersResponseInner>>)`.
    template <class CompletionToken>
    auto async_query_all_current_cm_open_orders(const QueryAllCurrentCmOpenOrdersParams& params,
                                                CompletionToken&& token) const {
        return common::async_send<std::vector<QueryAllCmOrdersResponseInner>>(
            client_, query_all_current_cm_open_orders_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Query All Current UM Open Algo Orders (USER_DATA)
    ///
    /// GET /papi/v1/um/algo/openAlgoOrders.
    ///
    /// Get all UM open algo orders on a symbol. If the symbol is not sent, orders for all symbols
    /// will be returned.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Weight: 1 for a single symbol; 40 when the symbol parameter is omitted.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#query-all-current-um-open-algo-orders
    [[nodiscard]] common::RestApiResponse<std::vector<QueryAllCurrentUmOpenAlgoOrdersResponseInner>>
    query_all_current_um_open_algo_orders(
        const QueryAllCurrentUmOpenAlgoOrdersParams& params = {}) const;

    /// Asynchronous `query_all_current_um_open_algo_orders()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<QueryAllCurrentUmOpenAlgoOrdersResponseInner>>)`.
    template <class CompletionToken>
    auto
    async_query_all_current_um_open_algo_orders(const QueryAllCurrentUmOpenAlgoOrdersParams& params,
                                                CompletionToken&& token) const {
        return common::async_send<std::vector<QueryAllCurrentUmOpenAlgoOrdersResponseInner>>(
            client_, query_all_current_um_open_algo_orders_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Query All Current UM Open Orders (USER_DATA)
    ///
    /// GET /papi/v1/um/openOrders.
    ///
    /// Get all open orders on a symbol.
    ///
    /// Weight: - 1 for a single `symbol`
    /// - 40 when `symbol` is omitted
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If the symbol is not sent, orders for all symbols will be returned in an array.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#query-all-current-um-open-orders
    [[nodiscard]] common::RestApiResponse<std::vector<QueryAllCurrentUmOpenOrdersResponseInner>>
    query_all_current_um_open_orders(const QueryAllCurrentUmOpenOrdersParams& params = {}) const;

    /// Asynchronous `query_all_current_um_open_orders()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<QueryAllCurrentUmOpenOrdersResponseInner>>)`.
    template <class CompletionToken>
    auto async_query_all_current_um_open_orders(const QueryAllCurrentUmOpenOrdersParams& params,
                                                CompletionToken&& token) const {
        return common::async_send<std::vector<QueryAllCurrentUmOpenOrdersResponseInner>>(
            client_, query_all_current_um_open_orders_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Query All Margin Account Orders (USER_DATA)
    ///
    /// GET /papi/v1/margin/allOrders.
    ///
    /// Query All Margin Account Orders
    ///
    /// Weight(IP): 100
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If `orderId` is set, returns orders with id >= `orderId`; otherwise returns recent order
    /// history.
    /// - For some historical orders, `cummulativeQuoteQty < 0` means the data is unavailable at
    /// this time.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#query-all-margin-account-orders
    [[nodiscard]] common::RestApiResponse<std::vector<QueryAllMarginAccountOrdersResponseInner>>
    query_all_margin_account_orders(const QueryAllMarginAccountOrdersParams& params) const;

    /// Asynchronous `query_all_margin_account_orders()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<QueryAllMarginAccountOrdersResponseInner>>)`.
    template <class CompletionToken>
    auto async_query_all_margin_account_orders(const QueryAllMarginAccountOrdersParams& params,
                                               CompletionToken&& token) const {
        return common::async_send<std::vector<QueryAllMarginAccountOrdersResponseInner>>(
            client_, query_all_margin_account_orders_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Query All UM Orders (USER_DATA)
    ///
    /// GET /papi/v1/um/allOrders.
    ///
    /// Get all account UM orders; active, canceled, or filled.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If `orderId` is set, it will get orders >= that orderId. Otherwise most recent orders are
    /// returned.
    /// - The query time period must be less then 7 days( default as the recent 7 days).
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#query-all-um-orders
    [[nodiscard]] common::RestApiResponse<std::vector<QueryAllCurrentUmOpenOrdersResponseInner>>
    query_all_um_orders(const QueryAllUmOrdersParams& params) const;

    /// Asynchronous `query_all_um_orders()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<QueryAllCurrentUmOpenOrdersResponseInner>>)`.
    template <class CompletionToken>
    auto async_query_all_um_orders(const QueryAllUmOrdersParams& params,
                                   CompletionToken&& token) const {
        return common::async_send<std::vector<QueryAllCurrentUmOpenOrdersResponseInner>>(
            client_, query_all_um_orders_request(params), std::forward<CompletionToken>(token));
    }

    /// Query CM Conditional Order History (USER_DATA)
    ///
    /// GET /papi/v1/cm/conditional/orderHistory.
    ///
    /// Query CM Conditional Order History
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Either `strategyId` or `newClientStrategyId` must be sent.
    /// - `NEW` orders will not be found.
    /// - These orders will not be found:
    ///   - order status is `CANCELED` or `EXPIRED`, **AND**
    ///   - order has NO filled trade, **AND**
    ///   - created time + 7 days < current time
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#query-cm-conditional-order-history
    [[nodiscard]] common::RestApiResponse<QueryCmConditionalOrderHistoryResponse>
    query_cm_conditional_order_history(const QueryCmConditionalOrderHistoryParams& params) const;

    /// Asynchronous `query_cm_conditional_order_history()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<QueryCmConditionalOrderHistoryResponse>)`.
    template <class CompletionToken>
    auto
    async_query_cm_conditional_order_history(const QueryCmConditionalOrderHistoryParams& params,
                                             CompletionToken&& token) const {
        return common::async_send<QueryCmConditionalOrderHistoryResponse>(
            client_, query_cm_conditional_order_history_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Query CM Modify Order History (TRADE)
    ///
    /// GET /papi/v1/cm/orderAmendment.
    ///
    /// Get order modification history
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Either `orderId` or `origClientOrderId` must be sent, and the `orderId` will prevail if
    /// both are sent.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#query-cm-modify-order-history
    [[nodiscard]] common::RestApiResponse<std::vector<QueryCmModifyOrderHistoryResponseInner>>
    query_cm_modify_order_history(const QueryCmModifyOrderHistoryParams& params) const;

    /// Asynchronous `query_cm_modify_order_history()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<QueryCmModifyOrderHistoryResponseInner>>)`.
    template <class CompletionToken>
    auto async_query_cm_modify_order_history(const QueryCmModifyOrderHistoryParams& params,
                                             CompletionToken&& token) const {
        return common::async_send<std::vector<QueryCmModifyOrderHistoryResponseInner>>(
            client_, query_cm_modify_order_history_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Query Current CM Open Conditional Order (USER_DATA)
    ///
    /// GET /papi/v1/cm/conditional/openOrder.
    ///
    /// Query Current CM Open Conditional Order
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Either `strategyId` or `newClientStrategyId` must be sent.
    /// - If the queried order has been triggered, cancelled or expired, the error message "Order
    /// does not exist" will be returned.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#query-current-cm-open-conditional-order
    [[nodiscard]] common::RestApiResponse<QueryCurrentCmOpenConditionalOrderResponse>
    query_current_cm_open_conditional_order(
        const QueryCurrentCmOpenConditionalOrderParams& params) const;

    /// Asynchronous `query_current_cm_open_conditional_order()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<QueryCurrentCmOpenConditionalOrderResponse>)`.
    template <class CompletionToken>
    auto async_query_current_cm_open_conditional_order(
        const QueryCurrentCmOpenConditionalOrderParams& params, CompletionToken&& token) const {
        return common::async_send<QueryCurrentCmOpenConditionalOrderResponse>(
            client_, query_current_cm_open_conditional_order_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Query Current CM Open Order (USER_DATA)
    ///
    /// GET /papi/v1/cm/openOrder.
    ///
    /// Query current CM open order
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Either `orderId` or `origClientOrderId` must be sent.
    /// - If the queried order has been filled or cancelled, the error message "Order does not
    /// exist" will be returned.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#query-current-cm-open-order
    [[nodiscard]] common::RestApiResponse<std::vector<QueryAllCmOrdersResponseInner>>
    query_current_cm_open_order(const QueryCurrentCmOpenOrderParams& params) const;

    /// Asynchronous `query_current_cm_open_order()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<QueryAllCmOrdersResponseInner>>)`.
    template <class CompletionToken>
    auto async_query_current_cm_open_order(const QueryCurrentCmOpenOrderParams& params,
                                           CompletionToken&& token) const {
        return common::async_send<std::vector<QueryAllCmOrdersResponseInner>>(
            client_, query_current_cm_open_order_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Query Current Margin Open Order (USER_DATA)
    ///
    /// GET /papi/v1/margin/openOrders.
    ///
    /// Query Current Margin Open Order
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If `symbol` is not sent, order records for all symbols are returned.
    /// - When returning all symbols, the request count charged to the rate limiter equals the
    /// number of symbols currently trading on the exchange.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#query-current-margin-open-order
    [[nodiscard]] common::RestApiResponse<std::vector<QueryCurrentMarginOpenOrderResponseInner>>
    query_current_margin_open_order(const QueryCurrentMarginOpenOrderParams& params) const;

    /// Asynchronous `query_current_margin_open_order()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<QueryCurrentMarginOpenOrderResponseInner>>)`.
    template <class CompletionToken>
    auto async_query_current_margin_open_order(const QueryCurrentMarginOpenOrderParams& params,
                                               CompletionToken&& token) const {
        return common::async_send<std::vector<QueryCurrentMarginOpenOrderResponseInner>>(
            client_, query_current_margin_open_order_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Query Current UM Open Algo Order (USER_DATA)
    ///
    /// GET /papi/v1/um/algo/algoOrder.
    ///
    /// Check an UM algo order's status. Orders will not be found if: status is CANCELED/EXPIRED
    /// with no fills and created 3+ days ago; or created 90+ days ago.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Either `algoId` or `clientAlgoId` must be sent. `algoId` is self-increment for each
    /// specific `symbol`.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#query-current-um-open-algo-order
    [[nodiscard]] common::RestApiResponse<QueryCurrentUmOpenAlgoOrderResponse>
    query_current_um_open_algo_order(const QueryCurrentUmOpenAlgoOrderParams& params = {}) const;

    /// Asynchronous `query_current_um_open_algo_order()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<QueryCurrentUmOpenAlgoOrderResponse>)`.
    template <class CompletionToken>
    auto async_query_current_um_open_algo_order(const QueryCurrentUmOpenAlgoOrderParams& params,
                                                CompletionToken&& token) const {
        return common::async_send<QueryCurrentUmOpenAlgoOrderResponse>(
            client_, query_current_um_open_algo_order_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Query Current UM Open Order (USER_DATA)
    ///
    /// GET /papi/v1/um/openOrder.
    ///
    /// Query current UM open order
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Either `orderId` or `origClientOrderId` must be sent.
    /// - If the queried order has been filled or cancelled, the error message "Order does not
    /// exist" will be returned.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#query-current-um-open-order
    [[nodiscard]] common::RestApiResponse<QueryCurrentUmOpenOrderResponse>
    query_current_um_open_order(const QueryCurrentUmOpenOrderParams& params) const;

    /// Asynchronous `query_current_um_open_order()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<QueryCurrentUmOpenOrderResponse>)`.
    template <class CompletionToken>
    auto async_query_current_um_open_order(const QueryCurrentUmOpenOrderParams& params,
                                           CompletionToken&& token) const {
        return common::async_send<QueryCurrentUmOpenOrderResponse>(
            client_, query_current_um_open_order_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Query Margin Account's all OCO (USER_DATA)
    ///
    /// GET /papi/v1/margin/allOrderList.
    ///
    /// Query all OCO for a specific margin account based on provided optional parameters
    ///
    /// Weight(IP): 100
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#query-margin-accounts-all-oco
    [[nodiscard]] common::RestApiResponse<std::vector<QueryMarginAccountsAllOcoResponseInner>>
    query_margin_accounts_all_oco(const QueryMarginAccountsAllOcoParams& params = {}) const;

    /// Asynchronous `query_margin_accounts_all_oco()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<QueryMarginAccountsAllOcoResponseInner>>)`.
    template <class CompletionToken>
    auto async_query_margin_accounts_all_oco(const QueryMarginAccountsAllOcoParams& params,
                                             CompletionToken&& token) const {
        return common::async_send<std::vector<QueryMarginAccountsAllOcoResponseInner>>(
            client_, query_margin_accounts_all_oco_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Query Margin Account's Open OCO (USER_DATA)
    ///
    /// GET /papi/v1/margin/openOrderList.
    ///
    /// Query Margin Account's Open OCO
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#query-margin-accounts-open-oco
    [[nodiscard]] common::RestApiResponse<std::vector<QueryMarginAccountsOpenOcoResponseInner>>
    query_margin_accounts_open_oco(const QueryMarginAccountsOpenOcoParams& params = {}) const;

    /// Asynchronous `query_margin_accounts_open_oco()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<QueryMarginAccountsOpenOcoResponseInner>>)`.
    template <class CompletionToken>
    auto async_query_margin_accounts_open_oco(const QueryMarginAccountsOpenOcoParams& params,
                                              CompletionToken&& token) const {
        return common::async_send<std::vector<QueryMarginAccountsOpenOcoResponseInner>>(
            client_, query_margin_accounts_open_oco_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Query UM Algo Order History (USER_DATA)
    ///
    /// GET /papi/v1/um/algo/allAlgoOrders.
    ///
    /// Get all algo orders: ACTIVE, CANCELED, TRIGGERED or FINISHED.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If `algoId` is set, it will get orders >= that `algoId`. Otherwise most recent orders are
    /// returned.
    /// - The query time period must be less than 7 days (default as the recent 7 days).
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#query-um-algo-order-history
    [[nodiscard]] common::RestApiResponse<std::vector<QueryUmAlgoOrderHistoryResponseInner>>
    query_um_algo_order_history(const QueryUmAlgoOrderHistoryParams& params) const;

    /// Asynchronous `query_um_algo_order_history()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<QueryUmAlgoOrderHistoryResponseInner>>)`.
    template <class CompletionToken>
    auto async_query_um_algo_order_history(const QueryUmAlgoOrderHistoryParams& params,
                                           CompletionToken&& token) const {
        return common::async_send<std::vector<QueryUmAlgoOrderHistoryResponseInner>>(
            client_, query_um_algo_order_history_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Query UM Modify Order History (TRADE)
    ///
    /// GET /papi/v1/um/orderAmendment.
    ///
    /// Get order modification history
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Either `orderId` or `origClientOrderId` must be sent, and the `orderId` will prevail if
    /// both are sent.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#query-um-modify-order-history
    [[nodiscard]] common::RestApiResponse<std::vector<QueryUmModifyOrderHistoryResponseInner>>
    query_um_modify_order_history(const QueryUmModifyOrderHistoryParams& params) const;

    /// Asynchronous `query_um_modify_order_history()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<QueryUmModifyOrderHistoryResponseInner>>)`.
    template <class CompletionToken>
    auto async_query_um_modify_order_history(const QueryUmModifyOrderHistoryParams& params,
                                             CompletionToken&& token) const {
        return common::async_send<std::vector<QueryUmModifyOrderHistoryResponseInner>>(
            client_, query_um_modify_order_history_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Query User's CM Force Orders (USER_DATA)
    ///
    /// GET /papi/v1/cm/forceOrders.
    ///
    /// Query User's CM Force Orders
    ///
    /// Weight: - 20 with `symbol`
    /// - 50 without `symbol`
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If "autoCloseType" is not sent, orders with both of the types will be returned
    /// - If "startTime" is not sent, data within 7 days before "endTime" can be queried
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#query-users-cm-force-orders
    [[nodiscard]] common::RestApiResponse<std::vector<QueryUsersCmForceOrdersResponseInner>>
    query_users_cm_force_orders(const QueryUsersCmForceOrdersParams& params = {}) const;

    /// Asynchronous `query_users_cm_force_orders()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<QueryUsersCmForceOrdersResponseInner>>)`.
    template <class CompletionToken>
    auto async_query_users_cm_force_orders(const QueryUsersCmForceOrdersParams& params,
                                           CompletionToken&& token) const {
        return common::async_send<std::vector<QueryUsersCmForceOrdersResponseInner>>(
            client_, query_users_cm_force_orders_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Query User's Margin Force Orders (USER_DATA)
    ///
    /// GET /papi/v1/margin/forceOrders.
    ///
    /// Query user's margin force orders
    ///
    /// > **Note:** Portfolio Margin accounts liquidated through the Risk-Based Liquidation
    /// Adjustment flow will not have any order or trade records returned by this endpoint. Query
    /// the capital flow endpoint instead: Query Cross Isolated Margin Capital Flow.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#query-users-margin-force-orders
    [[nodiscard]] common::RestApiResponse<QueryUsersMarginForceOrdersResponse>
    query_users_margin_force_orders(const QueryUsersMarginForceOrdersParams& params = {}) const;

    /// Asynchronous `query_users_margin_force_orders()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<QueryUsersMarginForceOrdersResponse>)`.
    template <class CompletionToken>
    auto async_query_users_margin_force_orders(const QueryUsersMarginForceOrdersParams& params,
                                               CompletionToken&& token) const {
        return common::async_send<QueryUsersMarginForceOrdersResponse>(
            client_, query_users_margin_force_orders_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Query User's UM Force Orders (USER_DATA)
    ///
    /// GET /papi/v1/um/forceOrders.
    ///
    /// Query User's UM Force Orders
    ///
    /// Weight: - 20 with `symbol`
    /// - 50 without `symbol`
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If `autoCloseType` is not sent, orders with both of the types will be returned
    /// - If `startTime` is not sent, data within 7 days before `endTime` can be queried
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#query-users-um-force-orders
    [[nodiscard]] common::RestApiResponse<std::vector<QueryUsersUmForceOrdersResponseInner>>
    query_users_um_force_orders(const QueryUsersUmForceOrdersParams& params = {}) const;

    /// Asynchronous `query_users_um_force_orders()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<QueryUsersUmForceOrdersResponseInner>>)`.
    template <class CompletionToken>
    auto async_query_users_um_force_orders(const QueryUsersUmForceOrdersParams& params,
                                           CompletionToken&& token) const {
        return common::async_send<std::vector<QueryUsersUmForceOrdersResponseInner>>(
            client_, query_users_um_force_orders_request(params),
            std::forward<CompletionToken>(token));
    }

    /// UM Account Trade List (USER_DATA)
    ///
    /// GET /papi/v1/um/userTrades.
    ///
    /// Get trades for a specific account and UM symbol.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If `startTime` and `endTime` are both not sent, then the last '7 days' data will be
    /// returned.
    /// - The time between `startTime` and `endTime` cannot be longer than 7 days.
    /// - The parameter `fromId` cannot be sent with `startTime` or `endTime`.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#um-account-trade-list
    [[nodiscard]] common::RestApiResponse<std::vector<UmAccountTradeListResponseInner>>
    um_account_trade_list(const UmAccountTradeListParams& params) const;

    /// Asynchronous `um_account_trade_list()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<UmAccountTradeListResponseInner>>)`.
    template <class CompletionToken>
    auto async_um_account_trade_list(const UmAccountTradeListParams& params,
                                     CompletionToken&& token) const {
        return common::async_send<std::vector<UmAccountTradeListResponseInner>>(
            client_, um_account_trade_list_request(params), std::forward<CompletionToken>(token));
    }

    /// UM Position ADL Quantile Estimation (USER_DATA)
    ///
    /// GET /papi/v1/um/adlQuantile.
    ///
    /// Query UM Position ADL Quantile Estimation
    ///
    /// * Values update every 30s.
    /// * Values 0, 1, 2, 3, 4 shows the queue position and possibility of ADL from low to high.
    /// * For positions of the symbol are in One-way Mode or isolated margined in Hedge Mode,
    /// "LONG", "SHORT", and "BOTH" will be returned to show the positions' adl quantiles of
    /// different position sides.
    /// * If the positions of the symbol are crossed margined in Hedge Mode:
    /// * "HEDGE" as a sign will be returned instead of "BOTH";
    /// * A same value caculated on unrealized pnls on long and short sides' positions will be shown
    /// for "LONG" and "SHORT" when there are positions in both of long and short sides.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#um-position-adl-quantile-estimation
    [[nodiscard]] common::RestApiResponse<std::vector<UmPositionAdlQuantileEstimationResponseInner>>
    um_position_adl_quantile_estimation(
        const UmPositionAdlQuantileEstimationParams& params = {}) const;

    /// Asynchronous `um_position_adl_quantile_estimation()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<UmPositionAdlQuantileEstimationResponseInner>>)`.
    template <class CompletionToken>
    auto
    async_um_position_adl_quantile_estimation(const UmPositionAdlQuantileEstimationParams& params,
                                              CompletionToken&& token) const {
        return common::async_send<std::vector<UmPositionAdlQuantileEstimationResponseInner>>(
            client_, um_position_adl_quantile_estimation_request(params),
            std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest cancel_all_cm_open_conditional_orders_request(
        const CancelAllCmOpenConditionalOrdersParams& params) const;
    [[nodiscard]] common::RestRequest
    cancel_all_cm_open_orders_request(const CancelAllCmOpenOrdersParams& params) const;
    [[nodiscard]] common::RestRequest
    cancel_all_um_algo_open_orders_request(const CancelAllUmAlgoOpenOrdersParams& params) const;
    [[nodiscard]] common::RestRequest
    cancel_all_um_open_orders_request(const CancelAllUmOpenOrdersParams& params) const;
    [[nodiscard]] common::RestRequest
    cancel_cm_conditional_order_request(const CancelCmConditionalOrderParams& params) const;
    [[nodiscard]] common::RestRequest
    new_cm_conditional_order_request(const NewCmConditionalOrderParams& params) const;
    [[nodiscard]] common::RestRequest
    cancel_cm_order_request(const CancelCmOrderParams& params) const;
    [[nodiscard]] common::RestRequest
    modify_cm_order_request(const ModifyCmOrderParams& params) const;
    [[nodiscard]] common::RestRequest new_cm_order_request(const NewCmOrderParams& params) const;
    [[nodiscard]] common::RestRequest
    query_cm_order_request(const QueryCmOrderParams& params) const;
    [[nodiscard]] common::RestRequest cancel_margin_account_all_open_orders_on_a_symbol_request(
        const CancelMarginAccountAllOpenOrdersOnASymbolParams& params) const;
    [[nodiscard]] common::RestRequest cancel_margin_account_oco_orders_request(
        const CancelMarginAccountOcoOrdersParams& params) const;
    [[nodiscard]] common::RestRequest
    query_margin_accounts_oco_request(const QueryMarginAccountsOcoParams& params) const;
    [[nodiscard]] common::RestRequest
    cancel_margin_account_order_request(const CancelMarginAccountOrderParams& params) const;
    [[nodiscard]] common::RestRequest
    new_margin_order_request(const NewMarginOrderParams& params) const;
    [[nodiscard]] common::RestRequest
    query_margin_account_order_request(const QueryMarginAccountOrderParams& params) const;
    [[nodiscard]] common::RestRequest
    cancel_um_algo_order_request(const CancelUmAlgoOrderParams& params) const;
    [[nodiscard]] common::RestRequest
    new_um_algo_order_request(const NewUmAlgoOrderParams& params) const;
    [[nodiscard]] common::RestRequest
    cancel_um_order_request(const CancelUmOrderParams& params) const;
    [[nodiscard]] common::RestRequest
    modify_um_order_request(const ModifyUmOrderParams& params) const;
    [[nodiscard]] common::RestRequest new_um_order_request(const NewUmOrderParams& params) const;
    [[nodiscard]] common::RestRequest
    query_um_order_request(const QueryUmOrderParams& params) const;
    [[nodiscard]] common::RestRequest
    cm_account_trade_list_request(const CmAccountTradeListParams& params) const;
    [[nodiscard]] common::RestRequest cm_position_adl_quantile_estimation_request(
        const CmPositionAdlQuantileEstimationParams& params) const;
    [[nodiscard]] common::RestRequest
    futures_tradfi_perps_contract_request(const FuturesTradfiPerpsContractParams& params) const;
    [[nodiscard]] common::RestRequest
    get_um_futures_bnb_burn_status_request(const GetUmFuturesBnbBurnStatusParams& params) const;
    [[nodiscard]] common::RestRequest toggle_bnb_burn_on_um_futures_trade_request(
        const ToggleBnbBurnOnUmFuturesTradeParams& params) const;
    [[nodiscard]] common::RestRequest
    margin_account_borrow_request(const MarginAccountBorrowParams& params) const;
    [[nodiscard]] common::RestRequest
    margin_account_new_oco_request(const MarginAccountNewOcoParams& params) const;
    [[nodiscard]] common::RestRequest
    margin_account_repay_request(const MarginAccountRepayParams& params) const;
    [[nodiscard]] common::RestRequest
    margin_account_repay_debt_request(const MarginAccountRepayDebtParams& params) const;
    [[nodiscard]] common::RestRequest
    margin_account_trade_list_request(const MarginAccountTradeListParams& params) const;
    [[nodiscard]] common::RestRequest
    query_all_cm_conditional_orders_request(const QueryAllCmConditionalOrdersParams& params) const;
    [[nodiscard]] common::RestRequest
    query_all_cm_orders_request(const QueryAllCmOrdersParams& params) const;
    [[nodiscard]] common::RestRequest query_all_current_cm_open_conditional_orders_request(
        const QueryAllCurrentCmOpenConditionalOrdersParams& params) const;
    [[nodiscard]] common::RestRequest
    query_all_current_cm_open_orders_request(const QueryAllCurrentCmOpenOrdersParams& params) const;
    [[nodiscard]] common::RestRequest query_all_current_um_open_algo_orders_request(
        const QueryAllCurrentUmOpenAlgoOrdersParams& params) const;
    [[nodiscard]] common::RestRequest
    query_all_current_um_open_orders_request(const QueryAllCurrentUmOpenOrdersParams& params) const;
    [[nodiscard]] common::RestRequest
    query_all_margin_account_orders_request(const QueryAllMarginAccountOrdersParams& params) const;
    [[nodiscard]] common::RestRequest
    query_all_um_orders_request(const QueryAllUmOrdersParams& params) const;
    [[nodiscard]] common::RestRequest query_cm_conditional_order_history_request(
        const QueryCmConditionalOrderHistoryParams& params) const;
    [[nodiscard]] common::RestRequest
    query_cm_modify_order_history_request(const QueryCmModifyOrderHistoryParams& params) const;
    [[nodiscard]] common::RestRequest query_current_cm_open_conditional_order_request(
        const QueryCurrentCmOpenConditionalOrderParams& params) const;
    [[nodiscard]] common::RestRequest
    query_current_cm_open_order_request(const QueryCurrentCmOpenOrderParams& params) const;
    [[nodiscard]] common::RestRequest
    query_current_margin_open_order_request(const QueryCurrentMarginOpenOrderParams& params) const;
    [[nodiscard]] common::RestRequest
    query_current_um_open_algo_order_request(const QueryCurrentUmOpenAlgoOrderParams& params) const;
    [[nodiscard]] common::RestRequest
    query_current_um_open_order_request(const QueryCurrentUmOpenOrderParams& params) const;
    [[nodiscard]] common::RestRequest
    query_margin_accounts_all_oco_request(const QueryMarginAccountsAllOcoParams& params) const;
    [[nodiscard]] common::RestRequest
    query_margin_accounts_open_oco_request(const QueryMarginAccountsOpenOcoParams& params) const;
    [[nodiscard]] common::RestRequest
    query_um_algo_order_history_request(const QueryUmAlgoOrderHistoryParams& params) const;
    [[nodiscard]] common::RestRequest
    query_um_modify_order_history_request(const QueryUmModifyOrderHistoryParams& params) const;
    [[nodiscard]] common::RestRequest
    query_users_cm_force_orders_request(const QueryUsersCmForceOrdersParams& params) const;
    [[nodiscard]] common::RestRequest
    query_users_margin_force_orders_request(const QueryUsersMarginForceOrdersParams& params) const;
    [[nodiscard]] common::RestRequest
    query_users_um_force_orders_request(const QueryUsersUmForceOrdersParams& params) const;
    [[nodiscard]] common::RestRequest
    um_account_trade_list_request(const UmAccountTradeListParams& params) const;
    [[nodiscard]] common::RestRequest um_position_adl_quantile_estimation_request(
        const UmPositionAdlQuantileEstimationParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
