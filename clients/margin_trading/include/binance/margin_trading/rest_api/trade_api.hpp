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
#include <binance/margin_trading/export.hpp>
#include <binance/margin_trading/rest_api/models/create_special_key_response.hpp>
#include <binance/margin_trading/rest_api/models/get_force_liquidation_record_response.hpp>
#include <binance/margin_trading/rest_api/models/get_small_liability_exchange_coin_list_response_inner.hpp>
#include <binance/margin_trading/rest_api/models/get_small_liability_exchange_history_response.hpp>
#include <binance/margin_trading/rest_api/models/liquidation_loan_repay_response.hpp>
#include <binance/margin_trading/rest_api/models/margin_account_cancel_all_open_orders_on_a_symbol_response_inner.hpp>
#include <binance/margin_trading/rest_api/models/margin_account_cancel_oco_response.hpp>
#include <binance/margin_trading/rest_api/models/margin_account_cancel_order_response.hpp>
#include <binance/margin_trading/rest_api/models/margin_account_new_oco_response.hpp>
#include <binance/margin_trading/rest_api/models/margin_account_new_order_response.hpp>
#include <binance/margin_trading/rest_api/models/margin_account_new_oto_response.hpp>
#include <binance/margin_trading/rest_api/models/margin_account_new_otoco_response.hpp>
#include <binance/margin_trading/rest_api/models/margin_manual_liquidation_response.hpp>
#include <binance/margin_trading/rest_api/models/query_current_margin_order_count_usage_response_inner.hpp>
#include <binance/margin_trading/rest_api/models/query_liquidation_loan_repay_history_response.hpp>
#include <binance/margin_trading/rest_api/models/query_liquidation_loan_response.hpp>
#include <binance/margin_trading/rest_api/models/query_margin_accounts_all_oco_response_inner.hpp>
#include <binance/margin_trading/rest_api/models/query_margin_accounts_all_orders_response_inner.hpp>
#include <binance/margin_trading/rest_api/models/query_margin_accounts_oco_response.hpp>
#include <binance/margin_trading/rest_api/models/query_margin_accounts_open_oco_response_inner.hpp>
#include <binance/margin_trading/rest_api/models/query_margin_accounts_open_orders_response_inner.hpp>
#include <binance/margin_trading/rest_api/models/query_margin_accounts_open_otootoco_order_lists_response_inner.hpp>
#include <binance/margin_trading/rest_api/models/query_margin_accounts_order_response.hpp>
#include <binance/margin_trading/rest_api/models/query_margin_accounts_trade_list_response_inner.hpp>
#include <binance/margin_trading/rest_api/models/query_prevented_matches_response_inner.hpp>
#include <binance/margin_trading/rest_api/models/query_special_key_list_response_inner.hpp>
#include <binance/margin_trading/rest_api/models/query_special_key_response.hpp>

namespace binance::margin_trading::rest_api {

enum class CreateSpecialKeyPermissionModeEnum {
    Trade,
    Read,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_MARGIN_TRADING_EXPORT std::string_view
to_string(CreateSpecialKeyPermissionModeEnum value) noexcept;
BINANCE_MARGIN_TRADING_EXPORT CreateSpecialKeyPermissionModeEnum
tag_invoke(boost::json::value_to_tag<CreateSpecialKeyPermissionModeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              CreateSpecialKeyPermissionModeEnum value);

enum class MarginAccountCancelAllOpenOrdersOnASymbolIsIsolatedEnum {
    True_,
    False_,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_MARGIN_TRADING_EXPORT std::string_view
to_string(MarginAccountCancelAllOpenOrdersOnASymbolIsIsolatedEnum value) noexcept;
BINANCE_MARGIN_TRADING_EXPORT MarginAccountCancelAllOpenOrdersOnASymbolIsIsolatedEnum tag_invoke(
    boost::json::value_to_tag<MarginAccountCancelAllOpenOrdersOnASymbolIsIsolatedEnum> /*tag*/,
    const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           MarginAccountCancelAllOpenOrdersOnASymbolIsIsolatedEnum value);

enum class QueryMarginAccountsOpenOrdersIsIsolatedEnum {
    True_,
    False_,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_MARGIN_TRADING_EXPORT std::string_view
to_string(QueryMarginAccountsOpenOrdersIsIsolatedEnum value) noexcept;
BINANCE_MARGIN_TRADING_EXPORT QueryMarginAccountsOpenOrdersIsIsolatedEnum
tag_invoke(boost::json::value_to_tag<QueryMarginAccountsOpenOrdersIsIsolatedEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              QueryMarginAccountsOpenOrdersIsIsolatedEnum value);

enum class MarginAccountCancelOcoIsIsolatedEnum {
    True_,
    False_,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_MARGIN_TRADING_EXPORT std::string_view
to_string(MarginAccountCancelOcoIsIsolatedEnum value) noexcept;
BINANCE_MARGIN_TRADING_EXPORT MarginAccountCancelOcoIsIsolatedEnum
tag_invoke(boost::json::value_to_tag<MarginAccountCancelOcoIsIsolatedEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              MarginAccountCancelOcoIsIsolatedEnum value);

enum class QueryMarginAccountsOcoIsIsolatedEnum {
    True_,
    False_,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_MARGIN_TRADING_EXPORT std::string_view
to_string(QueryMarginAccountsOcoIsIsolatedEnum value) noexcept;
BINANCE_MARGIN_TRADING_EXPORT QueryMarginAccountsOcoIsIsolatedEnum
tag_invoke(boost::json::value_to_tag<QueryMarginAccountsOcoIsIsolatedEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              QueryMarginAccountsOcoIsIsolatedEnum value);

enum class MarginAccountCancelOrderIsIsolatedEnum {
    True_,
    False_,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_MARGIN_TRADING_EXPORT std::string_view
to_string(MarginAccountCancelOrderIsIsolatedEnum value) noexcept;
BINANCE_MARGIN_TRADING_EXPORT MarginAccountCancelOrderIsIsolatedEnum
tag_invoke(boost::json::value_to_tag<MarginAccountCancelOrderIsIsolatedEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              MarginAccountCancelOrderIsIsolatedEnum value);

enum class MarginAccountNewOrderSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_MARGIN_TRADING_EXPORT std::string_view
to_string(MarginAccountNewOrderSideEnum value) noexcept;
BINANCE_MARGIN_TRADING_EXPORT MarginAccountNewOrderSideEnum tag_invoke(
    boost::json::value_to_tag<MarginAccountNewOrderSideEnum> /*tag*/, const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              MarginAccountNewOrderSideEnum value);

enum class MarginAccountNewOrderTypeEnum {
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

[[nodiscard]] BINANCE_MARGIN_TRADING_EXPORT std::string_view
to_string(MarginAccountNewOrderTypeEnum value) noexcept;
BINANCE_MARGIN_TRADING_EXPORT MarginAccountNewOrderTypeEnum tag_invoke(
    boost::json::value_to_tag<MarginAccountNewOrderTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              MarginAccountNewOrderTypeEnum value);

enum class MarginAccountNewOrderIsIsolatedEnum {
    True_,
    False_,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_MARGIN_TRADING_EXPORT std::string_view
to_string(MarginAccountNewOrderIsIsolatedEnum value) noexcept;
BINANCE_MARGIN_TRADING_EXPORT MarginAccountNewOrderIsIsolatedEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOrderIsIsolatedEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              MarginAccountNewOrderIsIsolatedEnum value);

enum class MarginAccountNewOrderNewOrderRespTypeEnum {
    Ack,
    Result,
    Full,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_MARGIN_TRADING_EXPORT std::string_view
to_string(MarginAccountNewOrderNewOrderRespTypeEnum value) noexcept;
BINANCE_MARGIN_TRADING_EXPORT MarginAccountNewOrderNewOrderRespTypeEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOrderNewOrderRespTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              MarginAccountNewOrderNewOrderRespTypeEnum value);

enum class MarginAccountNewOrderSideEffectTypeEnum {
    NoSideEffect,
    MarginBuy,
    AutoRepay,
    AutoBorrowRepay,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_MARGIN_TRADING_EXPORT std::string_view
to_string(MarginAccountNewOrderSideEffectTypeEnum value) noexcept;
BINANCE_MARGIN_TRADING_EXPORT MarginAccountNewOrderSideEffectTypeEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOrderSideEffectTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              MarginAccountNewOrderSideEffectTypeEnum value);

enum class MarginAccountNewOrderTimeInForceEnum {
    Gtc,
    Ioc,
    Fok,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_MARGIN_TRADING_EXPORT std::string_view
to_string(MarginAccountNewOrderTimeInForceEnum value) noexcept;
BINANCE_MARGIN_TRADING_EXPORT MarginAccountNewOrderTimeInForceEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOrderTimeInForceEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              MarginAccountNewOrderTimeInForceEnum value);

enum class MarginAccountNewOrderSelfTradePreventionModeEnum {
    ExpireTaker,
    ExpireMaker,
    ExpireBoth,
    None_,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_MARGIN_TRADING_EXPORT std::string_view
to_string(MarginAccountNewOrderSelfTradePreventionModeEnum value) noexcept;
BINANCE_MARGIN_TRADING_EXPORT MarginAccountNewOrderSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOrderSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           MarginAccountNewOrderSelfTradePreventionModeEnum value);

enum class QueryMarginAccountsOrderIsIsolatedEnum {
    True_,
    False_,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_MARGIN_TRADING_EXPORT std::string_view
to_string(QueryMarginAccountsOrderIsIsolatedEnum value) noexcept;
BINANCE_MARGIN_TRADING_EXPORT QueryMarginAccountsOrderIsIsolatedEnum
tag_invoke(boost::json::value_to_tag<QueryMarginAccountsOrderIsIsolatedEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              QueryMarginAccountsOrderIsIsolatedEnum value);

enum class MarginAccountNewOcoSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_MARGIN_TRADING_EXPORT std::string_view
to_string(MarginAccountNewOcoSideEnum value) noexcept;
BINANCE_MARGIN_TRADING_EXPORT MarginAccountNewOcoSideEnum tag_invoke(
    boost::json::value_to_tag<MarginAccountNewOcoSideEnum> /*tag*/, const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              MarginAccountNewOcoSideEnum value);

enum class MarginAccountNewOcoIsIsolatedEnum {
    True_,
    False_,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_MARGIN_TRADING_EXPORT std::string_view
to_string(MarginAccountNewOcoIsIsolatedEnum value) noexcept;
BINANCE_MARGIN_TRADING_EXPORT MarginAccountNewOcoIsIsolatedEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOcoIsIsolatedEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              MarginAccountNewOcoIsIsolatedEnum value);

enum class MarginAccountNewOcoStopLimitTimeInForceEnum {
    Gtc,
    Fok,
    Ioc,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_MARGIN_TRADING_EXPORT std::string_view
to_string(MarginAccountNewOcoStopLimitTimeInForceEnum value) noexcept;
BINANCE_MARGIN_TRADING_EXPORT MarginAccountNewOcoStopLimitTimeInForceEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOcoStopLimitTimeInForceEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              MarginAccountNewOcoStopLimitTimeInForceEnum value);

enum class MarginAccountNewOcoNewOrderRespTypeEnum {
    Ack,
    Result,
    Full,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_MARGIN_TRADING_EXPORT std::string_view
to_string(MarginAccountNewOcoNewOrderRespTypeEnum value) noexcept;
BINANCE_MARGIN_TRADING_EXPORT MarginAccountNewOcoNewOrderRespTypeEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOcoNewOrderRespTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              MarginAccountNewOcoNewOrderRespTypeEnum value);

enum class MarginAccountNewOcoSideEffectTypeEnum {
    NoSideEffect,
    MarginBuy,
    AutoRepay,
    AutoBorrowRepay,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_MARGIN_TRADING_EXPORT std::string_view
to_string(MarginAccountNewOcoSideEffectTypeEnum value) noexcept;
BINANCE_MARGIN_TRADING_EXPORT MarginAccountNewOcoSideEffectTypeEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOcoSideEffectTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              MarginAccountNewOcoSideEffectTypeEnum value);

enum class MarginAccountNewOcoSelfTradePreventionModeEnum {
    ExpireTaker,
    ExpireMaker,
    ExpireBoth,
    None_,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_MARGIN_TRADING_EXPORT std::string_view
to_string(MarginAccountNewOcoSelfTradePreventionModeEnum value) noexcept;
BINANCE_MARGIN_TRADING_EXPORT MarginAccountNewOcoSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOcoSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              MarginAccountNewOcoSelfTradePreventionModeEnum value);

enum class MarginAccountNewOtoWorkingTypeEnum {
    Limit,
    LimitMaker,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_MARGIN_TRADING_EXPORT std::string_view
to_string(MarginAccountNewOtoWorkingTypeEnum value) noexcept;
BINANCE_MARGIN_TRADING_EXPORT MarginAccountNewOtoWorkingTypeEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOtoWorkingTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              MarginAccountNewOtoWorkingTypeEnum value);

enum class MarginAccountNewOtoWorkingSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_MARGIN_TRADING_EXPORT std::string_view
to_string(MarginAccountNewOtoWorkingSideEnum value) noexcept;
BINANCE_MARGIN_TRADING_EXPORT MarginAccountNewOtoWorkingSideEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOtoWorkingSideEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              MarginAccountNewOtoWorkingSideEnum value);

enum class MarginAccountNewOtoPendingTypeEnum {
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

[[nodiscard]] BINANCE_MARGIN_TRADING_EXPORT std::string_view
to_string(MarginAccountNewOtoPendingTypeEnum value) noexcept;
BINANCE_MARGIN_TRADING_EXPORT MarginAccountNewOtoPendingTypeEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOtoPendingTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              MarginAccountNewOtoPendingTypeEnum value);

enum class MarginAccountNewOtoPendingSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_MARGIN_TRADING_EXPORT std::string_view
to_string(MarginAccountNewOtoPendingSideEnum value) noexcept;
BINANCE_MARGIN_TRADING_EXPORT MarginAccountNewOtoPendingSideEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOtoPendingSideEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              MarginAccountNewOtoPendingSideEnum value);

enum class MarginAccountNewOtoIsIsolatedEnum {
    True_,
    False_,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_MARGIN_TRADING_EXPORT std::string_view
to_string(MarginAccountNewOtoIsIsolatedEnum value) noexcept;
BINANCE_MARGIN_TRADING_EXPORT MarginAccountNewOtoIsIsolatedEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOtoIsIsolatedEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              MarginAccountNewOtoIsIsolatedEnum value);

enum class MarginAccountNewOtoNewOrderRespTypeEnum {
    Ack,
    Result,
    Full,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_MARGIN_TRADING_EXPORT std::string_view
to_string(MarginAccountNewOtoNewOrderRespTypeEnum value) noexcept;
BINANCE_MARGIN_TRADING_EXPORT MarginAccountNewOtoNewOrderRespTypeEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOtoNewOrderRespTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              MarginAccountNewOtoNewOrderRespTypeEnum value);

enum class MarginAccountNewOtoSideEffectTypeEnum {
    NoSideEffect,
    MarginBuy,
    AutoBorrowRepay,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_MARGIN_TRADING_EXPORT std::string_view
to_string(MarginAccountNewOtoSideEffectTypeEnum value) noexcept;
BINANCE_MARGIN_TRADING_EXPORT MarginAccountNewOtoSideEffectTypeEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOtoSideEffectTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              MarginAccountNewOtoSideEffectTypeEnum value);

enum class MarginAccountNewOtoSelfTradePreventionModeEnum {
    ExpireTaker,
    ExpireMaker,
    ExpireBoth,
    None_,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_MARGIN_TRADING_EXPORT std::string_view
to_string(MarginAccountNewOtoSelfTradePreventionModeEnum value) noexcept;
BINANCE_MARGIN_TRADING_EXPORT MarginAccountNewOtoSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOtoSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              MarginAccountNewOtoSelfTradePreventionModeEnum value);

enum class MarginAccountNewOtoWorkingTimeInForceEnum {
    Gtc,
    Ioc,
    Fok,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_MARGIN_TRADING_EXPORT std::string_view
to_string(MarginAccountNewOtoWorkingTimeInForceEnum value) noexcept;
BINANCE_MARGIN_TRADING_EXPORT MarginAccountNewOtoWorkingTimeInForceEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOtoWorkingTimeInForceEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              MarginAccountNewOtoWorkingTimeInForceEnum value);

enum class MarginAccountNewOtoPendingTimeInForceEnum {
    Gtc,
    Ioc,
    Fok,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_MARGIN_TRADING_EXPORT std::string_view
to_string(MarginAccountNewOtoPendingTimeInForceEnum value) noexcept;
BINANCE_MARGIN_TRADING_EXPORT MarginAccountNewOtoPendingTimeInForceEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOtoPendingTimeInForceEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              MarginAccountNewOtoPendingTimeInForceEnum value);

enum class MarginAccountNewOtocoWorkingTypeEnum {
    Limit,
    LimitMaker,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_MARGIN_TRADING_EXPORT std::string_view
to_string(MarginAccountNewOtocoWorkingTypeEnum value) noexcept;
BINANCE_MARGIN_TRADING_EXPORT MarginAccountNewOtocoWorkingTypeEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOtocoWorkingTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              MarginAccountNewOtocoWorkingTypeEnum value);

enum class MarginAccountNewOtocoWorkingSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_MARGIN_TRADING_EXPORT std::string_view
to_string(MarginAccountNewOtocoWorkingSideEnum value) noexcept;
BINANCE_MARGIN_TRADING_EXPORT MarginAccountNewOtocoWorkingSideEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOtocoWorkingSideEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              MarginAccountNewOtocoWorkingSideEnum value);

enum class MarginAccountNewOtocoPendingSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_MARGIN_TRADING_EXPORT std::string_view
to_string(MarginAccountNewOtocoPendingSideEnum value) noexcept;
BINANCE_MARGIN_TRADING_EXPORT MarginAccountNewOtocoPendingSideEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOtocoPendingSideEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              MarginAccountNewOtocoPendingSideEnum value);

enum class MarginAccountNewOtocoPendingAboveTypeEnum {
    LimitMaker,
    StopLoss,
    StopLossLimit,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_MARGIN_TRADING_EXPORT std::string_view
to_string(MarginAccountNewOtocoPendingAboveTypeEnum value) noexcept;
BINANCE_MARGIN_TRADING_EXPORT MarginAccountNewOtocoPendingAboveTypeEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOtocoPendingAboveTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              MarginAccountNewOtocoPendingAboveTypeEnum value);

enum class MarginAccountNewOtocoIsIsolatedEnum {
    True_,
    False_,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_MARGIN_TRADING_EXPORT std::string_view
to_string(MarginAccountNewOtocoIsIsolatedEnum value) noexcept;
BINANCE_MARGIN_TRADING_EXPORT MarginAccountNewOtocoIsIsolatedEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOtocoIsIsolatedEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              MarginAccountNewOtocoIsIsolatedEnum value);

enum class MarginAccountNewOtocoSideEffectTypeEnum {
    NoSideEffect,
    MarginBuy,
    AutoBorrowRepay,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_MARGIN_TRADING_EXPORT std::string_view
to_string(MarginAccountNewOtocoSideEffectTypeEnum value) noexcept;
BINANCE_MARGIN_TRADING_EXPORT MarginAccountNewOtocoSideEffectTypeEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOtocoSideEffectTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              MarginAccountNewOtocoSideEffectTypeEnum value);

enum class MarginAccountNewOtocoNewOrderRespTypeEnum {
    Ack,
    Result,
    Full,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_MARGIN_TRADING_EXPORT std::string_view
to_string(MarginAccountNewOtocoNewOrderRespTypeEnum value) noexcept;
BINANCE_MARGIN_TRADING_EXPORT MarginAccountNewOtocoNewOrderRespTypeEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOtocoNewOrderRespTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              MarginAccountNewOtocoNewOrderRespTypeEnum value);

enum class MarginAccountNewOtocoSelfTradePreventionModeEnum {
    ExpireTaker,
    ExpireMaker,
    ExpireBoth,
    None_,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_MARGIN_TRADING_EXPORT std::string_view
to_string(MarginAccountNewOtocoSelfTradePreventionModeEnum value) noexcept;
BINANCE_MARGIN_TRADING_EXPORT MarginAccountNewOtocoSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOtocoSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           MarginAccountNewOtocoSelfTradePreventionModeEnum value);

enum class MarginAccountNewOtocoWorkingTimeInForceEnum {
    Gtc,
    Ioc,
    Fok,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_MARGIN_TRADING_EXPORT std::string_view
to_string(MarginAccountNewOtocoWorkingTimeInForceEnum value) noexcept;
BINANCE_MARGIN_TRADING_EXPORT MarginAccountNewOtocoWorkingTimeInForceEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOtocoWorkingTimeInForceEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              MarginAccountNewOtocoWorkingTimeInForceEnum value);

enum class MarginAccountNewOtocoPendingAboveTimeInForceEnum {
    Gtc,
    Ioc,
    Fok,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_MARGIN_TRADING_EXPORT std::string_view
to_string(MarginAccountNewOtocoPendingAboveTimeInForceEnum value) noexcept;
BINANCE_MARGIN_TRADING_EXPORT MarginAccountNewOtocoPendingAboveTimeInForceEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOtocoPendingAboveTimeInForceEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           MarginAccountNewOtocoPendingAboveTimeInForceEnum value);

enum class MarginAccountNewOtocoPendingBelowTypeEnum {
    LimitMaker,
    StopLoss,
    StopLossLimit,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_MARGIN_TRADING_EXPORT std::string_view
to_string(MarginAccountNewOtocoPendingBelowTypeEnum value) noexcept;
BINANCE_MARGIN_TRADING_EXPORT MarginAccountNewOtocoPendingBelowTypeEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOtocoPendingBelowTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              MarginAccountNewOtocoPendingBelowTypeEnum value);

enum class MarginAccountNewOtocoPendingBelowTimeInForceEnum {
    Gtc,
    Ioc,
    Fok,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_MARGIN_TRADING_EXPORT std::string_view
to_string(MarginAccountNewOtocoPendingBelowTimeInForceEnum value) noexcept;
BINANCE_MARGIN_TRADING_EXPORT MarginAccountNewOtocoPendingBelowTimeInForceEnum
tag_invoke(boost::json::value_to_tag<MarginAccountNewOtocoPendingBelowTimeInForceEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           MarginAccountNewOtocoPendingBelowTimeInForceEnum value);

enum class MarginManualLiquidationTypeEnum {
    Margin,
    Isolated,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_MARGIN_TRADING_EXPORT std::string_view
to_string(MarginManualLiquidationTypeEnum value) noexcept;
BINANCE_MARGIN_TRADING_EXPORT MarginManualLiquidationTypeEnum
tag_invoke(boost::json::value_to_tag<MarginManualLiquidationTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              MarginManualLiquidationTypeEnum value);

enum class QueryCurrentMarginOrderCountUsageIsIsolatedEnum {
    True_,
    False_,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_MARGIN_TRADING_EXPORT std::string_view
to_string(QueryCurrentMarginOrderCountUsageIsIsolatedEnum value) noexcept;
BINANCE_MARGIN_TRADING_EXPORT QueryCurrentMarginOrderCountUsageIsIsolatedEnum
tag_invoke(boost::json::value_to_tag<QueryCurrentMarginOrderCountUsageIsIsolatedEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           QueryCurrentMarginOrderCountUsageIsIsolatedEnum value);

enum class QueryMarginAccountsAllOcoIsIsolatedEnum {
    True_,
    False_,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_MARGIN_TRADING_EXPORT std::string_view
to_string(QueryMarginAccountsAllOcoIsIsolatedEnum value) noexcept;
BINANCE_MARGIN_TRADING_EXPORT QueryMarginAccountsAllOcoIsIsolatedEnum
tag_invoke(boost::json::value_to_tag<QueryMarginAccountsAllOcoIsIsolatedEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              QueryMarginAccountsAllOcoIsIsolatedEnum value);

enum class QueryMarginAccountsAllOrdersIsIsolatedEnum {
    True_,
    False_,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_MARGIN_TRADING_EXPORT std::string_view
to_string(QueryMarginAccountsAllOrdersIsIsolatedEnum value) noexcept;
BINANCE_MARGIN_TRADING_EXPORT QueryMarginAccountsAllOrdersIsIsolatedEnum
tag_invoke(boost::json::value_to_tag<QueryMarginAccountsAllOrdersIsIsolatedEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              QueryMarginAccountsAllOrdersIsIsolatedEnum value);

enum class QueryMarginAccountsOpenOcoIsIsolatedEnum {
    True_,
    False_,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_MARGIN_TRADING_EXPORT std::string_view
to_string(QueryMarginAccountsOpenOcoIsIsolatedEnum value) noexcept;
BINANCE_MARGIN_TRADING_EXPORT QueryMarginAccountsOpenOcoIsIsolatedEnum
tag_invoke(boost::json::value_to_tag<QueryMarginAccountsOpenOcoIsIsolatedEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              QueryMarginAccountsOpenOcoIsIsolatedEnum value);

enum class QueryMarginAccountsTradeListIsIsolatedEnum {
    True_,
    False_,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_MARGIN_TRADING_EXPORT std::string_view
to_string(QueryMarginAccountsTradeListIsIsolatedEnum value) noexcept;
BINANCE_MARGIN_TRADING_EXPORT QueryMarginAccountsTradeListIsIsolatedEnum
tag_invoke(boost::json::value_to_tag<QueryMarginAccountsTradeListIsIsolatedEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              QueryMarginAccountsTradeListIsIsolatedEnum value);

enum class QueryPreventedMatchesIsIsolatedEnum {
    True_,
    False_,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_MARGIN_TRADING_EXPORT std::string_view
to_string(QueryPreventedMatchesIsIsolatedEnum value) noexcept;
BINANCE_MARGIN_TRADING_EXPORT QueryPreventedMatchesIsIsolatedEnum
tag_invoke(boost::json::value_to_tag<QueryPreventedMatchesIsIsolatedEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              QueryPreventedMatchesIsIsolatedEnum value);

struct CreateSpecialKeyParams {
    common::Required<std::string> api_name;
    std::optional<std::string> symbol = std::nullopt;
    /// Can be added in batches, separated by commas. Max 30 for an API key
    std::optional<std::string> ip = std::nullopt;
    /// 1. If publicKey is inputted it will create an RSA or Ed25519 key.  2. Need to be encoded to
    /// URL-encoded format
    std::optional<std::string> public_key = std::nullopt;
    /// This parameter is only for the Ed25519 API key, and does not effact for other encryption
    /// methods. The value can be TRADE (TRADE for all permissions) or READ (READ for USER_DATA,
    /// FIX_API_READ_ONLY). The default value is TRADE.
    std::optional<CreateSpecialKeyPermissionModeEnum> permission_mode = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct DeleteSpecialKeyParams {
    std::optional<std::string> api_name = std::nullopt;
    std::optional<std::string> symbol = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QuerySpecialKeyParams {
    std::optional<std::string> symbol = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct EditIpForSpecialKeyParams {
    /// Can be added in batches, separated by commas. Max 30 for an API key
    common::Required<std::string> ip;
    /// isolated margin pair
    std::optional<std::string> symbol = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct ExitSpecialKeyModeParams {
    /// The value cannot be greater than `60000`
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetForceLiquidationRecordParams {
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    std::optional<std::string> isolated_symbol = std::nullopt;
    std::optional<std::int64_t> current = std::nullopt;
    std::optional<std::int64_t> size = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetSmallLiabilityExchangeCoinListParams {
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct SmallLiabilityExchangeParams {
    /// The assets list of small liability exchange
    common::Required<std::string> asset_names;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetSmallLiabilityExchangeHistoryParams {
    common::Required<std::int64_t> current;
    common::Required<std::int64_t> size;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct LiquidationLoanRepayParams {
    /// The asset to repay (e.g. USDT, USDC)
    common::Required<std::string> asset;
    /// Repayment amount, must be greater than 0
    common::Required<common::Decimal> amount;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct MarginAccountCancelAllOpenOrdersOnASymbolParams {
    common::Required<std::string> symbol;
    std::optional<MarginAccountCancelAllOpenOrdersOnASymbolIsIsolatedEnum> is_isolated =
        std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryMarginAccountsOpenOrdersParams {
    /// isolated margin pair
    std::optional<std::string> symbol = std::nullopt;
    std::optional<QueryMarginAccountsOpenOrdersIsIsolatedEnum> is_isolated = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct MarginAccountCancelOcoParams {
    common::Required<std::string> symbol;
    std::optional<MarginAccountCancelOcoIsIsolatedEnum> is_isolated = std::nullopt;
    std::optional<std::int64_t> order_list_id = std::nullopt;
    std::optional<std::string> list_client_order_id = std::nullopt;
    std::optional<std::string> new_client_order_id = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryMarginAccountsOcoParams {
    std::optional<QueryMarginAccountsOcoIsIsolatedEnum> is_isolated = std::nullopt;
    std::optional<std::string> symbol = std::nullopt;
    std::optional<std::int64_t> order_list_id = std::nullopt;
    std::optional<std::string> orig_client_order_id = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct MarginAccountCancelOrderParams {
    common::Required<std::string> symbol;
    std::optional<MarginAccountCancelOrderIsIsolatedEnum> is_isolated = std::nullopt;
    std::optional<std::int64_t> order_id = std::nullopt;
    std::optional<std::string> orig_client_order_id = std::nullopt;
    std::optional<std::string> new_client_order_id = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct MarginAccountNewOrderParams {
    common::Required<std::string> symbol;
    common::Required<MarginAccountNewOrderSideEnum> side;
    common::Required<MarginAccountNewOrderTypeEnum> type;
    std::optional<MarginAccountNewOrderIsIsolatedEnum> is_isolated = std::nullopt;
    std::optional<common::Decimal> quantity = std::nullopt;
    std::optional<common::Decimal> quote_order_qty = std::nullopt;
    std::optional<common::Decimal> price = std::nullopt;
    /// Used with `STOP_LOSS`, `STOP_LOSS_LIMIT`, `TAKE_PROFIT`, and `TAKE_PROFIT_LIMIT` orders.
    std::optional<common::Decimal> stop_price = std::nullopt;
    /// A unique id among open orders. Automatically generated if not sent.
    std::optional<std::string> new_client_order_id = std::nullopt;
    /// Used with `LIMIT`, `STOP_LOSS_LIMIT`, and `TAKE_PROFIT_LIMIT` to create an iceberg order.
    std::optional<common::Decimal> iceberg_qty = std::nullopt;
    /// MARKET and LIMIT order types default to FULL, all other orders default to ACK.
    std::optional<MarginAccountNewOrderNewOrderRespTypeEnum> new_order_resp_type = std::nullopt;
    std::optional<MarginAccountNewOrderSideEffectTypeEnum> side_effect_type = std::nullopt;
    std::optional<MarginAccountNewOrderTimeInForceEnum> time_in_force = std::nullopt;
    std::optional<MarginAccountNewOrderSelfTradePreventionModeEnum> self_trade_prevention_mode =
        std::nullopt;
    /// Used with `STOP_LOSS`, `STOP_LOSS_LIMIT`, `TAKE_PROFIT`, and `TAKE_PROFIT_LIMIT` orders.
    std::optional<std::int64_t> trailing_delta = std::nullopt;
    /// Only when MARGIN_BUY or AUTO_BORROW_REPAY order takes effect, true means that the debt
    /// generated by the order needs to be repaid after the order is cancelled.
    std::optional<bool> auto_repay_at_cancel = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryMarginAccountsOrderParams {
    common::Required<std::string> symbol;
    std::optional<QueryMarginAccountsOrderIsIsolatedEnum> is_isolated = std::nullopt;
    std::optional<std::int64_t> order_id = std::nullopt;
    std::optional<std::string> orig_client_order_id = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct MarginAccountNewOcoParams {
    common::Required<std::string> symbol;
    common::Required<MarginAccountNewOcoSideEnum> side;
    common::Required<common::Decimal> quantity;
    common::Required<common::Decimal> price;
    common::Required<common::Decimal> stop_price;
    std::optional<MarginAccountNewOcoIsIsolatedEnum> is_isolated = std::nullopt;
    /// A unique Id for the entire orderList
    std::optional<std::string> list_client_order_id = std::nullopt;
    /// A unique Id for the limit order
    std::optional<std::string> limit_client_order_id = std::nullopt;
    std::optional<common::Decimal> limit_iceberg_qty = std::nullopt;
    /// A unique Id for the stop loss/stop loss limit leg
    std::optional<std::string> stop_client_order_id = std::nullopt;
    /// If provided, `stopLimitTimeInForce` is required.
    std::optional<common::Decimal> stop_limit_price = std::nullopt;
    std::optional<common::Decimal> stop_iceberg_qty = std::nullopt;
    std::optional<MarginAccountNewOcoStopLimitTimeInForceEnum> stop_limit_time_in_force =
        std::nullopt;
    std::optional<MarginAccountNewOcoNewOrderRespTypeEnum> new_order_resp_type = std::nullopt;
    std::optional<MarginAccountNewOcoSideEffectTypeEnum> side_effect_type = std::nullopt;
    std::optional<MarginAccountNewOcoSelfTradePreventionModeEnum> self_trade_prevention_mode =
        std::nullopt;
    /// Only when MARGIN_BUY or AUTO_BORROW_REPAY order takes effect, true means that the debt
    /// generated by the order needs to be repay after the order is cancelled.
    std::optional<bool> auto_repay_at_cancel = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct MarginAccountNewOtoParams {
    common::Required<std::string> symbol;
    common::Required<MarginAccountNewOtoWorkingTypeEnum> working_type;
    common::Required<MarginAccountNewOtoWorkingSideEnum> working_side;
    common::Required<common::Decimal> working_price;
    /// Sets the quantity for the working order.
    common::Required<common::Decimal> working_quantity;
    /// This can only be used if `workingTimeInForce` is `GTC`.
    common::Required<common::Decimal> working_iceberg_qty;
    common::Required<MarginAccountNewOtoPendingTypeEnum> pending_type;
    common::Required<MarginAccountNewOtoPendingSideEnum> pending_side;
    /// Sets the quantity for the pending order.
    common::Required<common::Decimal> pending_quantity;
    std::optional<MarginAccountNewOtoIsIsolatedEnum> is_isolated = std::nullopt;
    /// Arbitrary unique ID among open order lists. Automatically generated if not sent.
    /// A new order list with the same listClientOrderId is accepted only when the previous one is
    /// filled or completely expired. `listClientOrderId` is distinct from the
    /// `workingClientOrderId` and the `pendingClientOrderId`.
    std::optional<std::string> list_client_order_id = std::nullopt;
    /// MARKET and LIMIT order types default to FULL, all other orders default to ACK.
    std::optional<MarginAccountNewOtoNewOrderRespTypeEnum> new_order_resp_type = std::nullopt;
    std::optional<MarginAccountNewOtoSideEffectTypeEnum> side_effect_type = std::nullopt;
    std::optional<MarginAccountNewOtoSelfTradePreventionModeEnum> self_trade_prevention_mode =
        std::nullopt;
    /// Only when MARGIN_BUY order takes effect, true means that the debt generated by the order
    /// needs to be repaid after the order is cancelled.
    std::optional<bool> auto_repay_at_cancel = std::nullopt;
    /// Arbitrary unique ID among open orders for the working order. Automatically generated if not
    /// sent.
    std::optional<std::string> working_client_order_id = std::nullopt;
    std::optional<MarginAccountNewOtoWorkingTimeInForceEnum> working_time_in_force = std::nullopt;
    /// Arbitrary unique ID among open orders for the pending order. Automatically generated if not
    /// sent.
    std::optional<std::string> pending_client_order_id = std::nullopt;
    std::optional<common::Decimal> pending_price = std::nullopt;
    std::optional<common::Decimal> pending_stop_price = std::nullopt;
    std::optional<common::Decimal> pending_trailing_delta = std::nullopt;
    /// This can only be used if `pendingTimeInForce` is `GTC`.
    std::optional<common::Decimal> pending_iceberg_qty = std::nullopt;
    std::optional<MarginAccountNewOtoPendingTimeInForceEnum> pending_time_in_force = std::nullopt;
};

struct MarginAccountNewOtocoParams {
    common::Required<std::string> symbol;
    common::Required<MarginAccountNewOtocoWorkingTypeEnum> working_type;
    common::Required<MarginAccountNewOtocoWorkingSideEnum> working_side;
    common::Required<common::Decimal> working_price;
    common::Required<common::Decimal> working_quantity;
    common::Required<MarginAccountNewOtocoPendingSideEnum> pending_side;
    common::Required<common::Decimal> pending_quantity;
    common::Required<MarginAccountNewOtocoPendingAboveTypeEnum> pending_above_type;
    std::optional<MarginAccountNewOtocoIsIsolatedEnum> is_isolated = std::nullopt;
    std::optional<MarginAccountNewOtocoSideEffectTypeEnum> side_effect_type = std::nullopt;
    /// Only when MARGIN_BUY order takes effect, true means that the debt generated by the order
    /// needs to be repaid after the order is cancelled.
    std::optional<bool> auto_repay_at_cancel = std::nullopt;
    /// Arbitrary unique ID among open order lists. Automatically generated if not sent. A new order
    /// list with the same listClientOrderId is accepted only when the previous one is filled or
    /// completely expired. `listClientOrderId` is distinct from the `workingClientOrderId`,
    /// `pendingAboveClientOrderId`, and the `pendingBelowClientOrderId`.
    std::optional<std::string> list_client_order_id = std::nullopt;
    std::optional<MarginAccountNewOtocoNewOrderRespTypeEnum> new_order_resp_type = std::nullopt;
    std::optional<MarginAccountNewOtocoSelfTradePreventionModeEnum> self_trade_prevention_mode =
        std::nullopt;
    /// Arbitrary unique ID among open orders for the working order. Automatically generated if not
    /// sent.
    std::optional<std::string> working_client_order_id = std::nullopt;
    /// This can only be used if `workingTimeInForce` is `GTC`.
    std::optional<common::Decimal> working_iceberg_qty = std::nullopt;
    std::optional<MarginAccountNewOtocoWorkingTimeInForceEnum> working_time_in_force = std::nullopt;
    /// Arbitrary unique ID among open orders for the pending above order. Automatically generated
    /// if not sent.
    std::optional<std::string> pending_above_client_order_id = std::nullopt;
    std::optional<common::Decimal> pending_above_price = std::nullopt;
    std::optional<common::Decimal> pending_above_stop_price = std::nullopt;
    std::optional<common::Decimal> pending_above_trailing_delta = std::nullopt;
    /// This can only be used if `pendingAboveTimeInForce` is `GTC`.
    std::optional<common::Decimal> pending_above_iceberg_qty = std::nullopt;
    std::optional<MarginAccountNewOtocoPendingAboveTimeInForceEnum> pending_above_time_in_force =
        std::nullopt;
    std::optional<MarginAccountNewOtocoPendingBelowTypeEnum> pending_below_type = std::nullopt;
    /// Arbitrary unique ID among open orders for the pending below order. Automatically generated
    /// if not sent.
    std::optional<std::string> pending_below_client_order_id = std::nullopt;
    std::optional<common::Decimal> pending_below_price = std::nullopt;
    std::optional<common::Decimal> pending_below_stop_price = std::nullopt;
    std::optional<common::Decimal> pending_below_trailing_delta = std::nullopt;
    /// This can only be used if `pendingBelowTimeInForce` is `GTC`.
    std::optional<common::Decimal> pending_below_iceberg_qty = std::nullopt;
    std::optional<MarginAccountNewOtocoPendingBelowTimeInForceEnum> pending_below_time_in_force =
        std::nullopt;
};

struct MarginManualLiquidationParams {
    common::Required<MarginManualLiquidationTypeEnum> type;
    /// When type selects `ISOLATED`, `symbol` must be filled in
    std::optional<std::string> symbol = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryCurrentMarginOrderCountUsageParams {
    std::optional<QueryCurrentMarginOrderCountUsageIsIsolatedEnum> is_isolated = std::nullopt;
    std::optional<std::string> symbol = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryLiquidationLoanParams {
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryLiquidationLoanRepayHistoryParams {
    /// Start time in Unix timestamp (milliseconds). Defaults to 7 days ago if not specified
    std::optional<std::int64_t> start_time = std::nullopt;
    /// End time in Unix timestamp (milliseconds). Defaults to now if not specified
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Current page number, default `1`
    std::optional<std::int64_t> current = std::nullopt;
    /// Page size, default `50`
    std::optional<std::int64_t> size = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryMarginAccountsAllOcoParams {
    std::optional<QueryMarginAccountsAllOcoIsIsolatedEnum> is_isolated = std::nullopt;
    std::optional<std::string> symbol = std::nullopt;
    std::optional<std::int64_t> from_id = std::nullopt;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    std::optional<std::int64_t> limit = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryMarginAccountsAllOrdersParams {
    common::Required<std::string> symbol;
    std::optional<QueryMarginAccountsAllOrdersIsIsolatedEnum> is_isolated = std::nullopt;
    std::optional<std::int64_t> order_id = std::nullopt;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    std::optional<std::int64_t> limit = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryMarginAccountsOpenOcoParams {
    std::optional<QueryMarginAccountsOpenOcoIsIsolatedEnum> is_isolated = std::nullopt;
    std::optional<std::string> symbol = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryMarginAccountsOpenOtootocoOrderListsParams {
    std::optional<std::string> symbol = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryMarginAccountsTradeListParams {
    common::Required<std::string> symbol;
    std::optional<QueryMarginAccountsTradeListIsIsolatedEnum> is_isolated = std::nullopt;
    std::optional<std::int64_t> order_id = std::nullopt;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    std::optional<std::int64_t> from_id = std::nullopt;
    std::optional<std::int64_t> limit = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryPreventedMatchesParams {
    common::Required<std::string> symbol;
    std::optional<std::int64_t> prevented_match_id = std::nullopt;
    std::optional<std::int64_t> order_id = std::nullopt;
    std::optional<std::int64_t> from_prevented_match_id = std::nullopt;
    std::optional<QueryPreventedMatchesIsIsolatedEnum> is_isolated = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QuerySpecialKeyListParams {
    std::optional<std::string> symbol = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_MARGIN_TRADING_EXPORT TradeApi {
public:
    explicit TradeApi(std::shared_ptr<common::RestClient> client);

    /// Create Special Key(Low-Latency Trading) (TRADE)
    ///
    /// POST /sapi/v1/margin/apiKey.
    ///
    /// **Eligibility**
    ///
    /// - Binance Margin offers low-latency trading through a special key, available exclusively to
    /// users with VIP level 7 or higher.
    /// - If you are VIP level 6 or below, please contact your VIP manager for eligibility
    /// criterias.
    /// - All new Margin Special Key users are required to read, understand, and agree to the Margin
    /// Special Key Supplemental Product Terms at the master account level before creating a Margin
    /// Special Key.
    /// - Once signed at the master account level, the agreement applies to all sub-accounts. The
    /// master account and all sub-accounts (Cross Margin Classic and Portfolio Margin Pro) are
    /// authorized to create a Margin Special Key and are subject to the LiquidationLoan policy.
    ///
    /// For more information, please refer to FAQ.
    ///
    /// **Supported Products:**
    ///
    /// - Cross Margin
    /// - Isolated Margin
    /// - Portfolio Margin Pro
    ///
    /// **Unsupported Products:**
    ///
    /// - Portfolio Margin
    ///
    /// We support several types of API keys:
    ///
    /// * Ed25519 (recommended)
    /// * HMAC
    /// * RSA
    ///
    /// We recommend to **use Ed25519 API keys** as it should provide the best performance and
    /// security out of all supported key types. We accept PKCS#8 (BEGIN PUBLIC KEY). For how to
    /// generate an RSA key pair to send API requests on Binance. Please refer to the document below
    /// FAQ .
    ///
    /// **How to use the Margin Special Key**
    /// - Use the below `sapi` endpoint to create your margin special API Key.
    /// - For accessing the Cross Margin account, do not send the `symbol` parameter.
    /// - For accessing the Isolated Margin account(s), pass the relevant `symbol` parameter in the
    /// API Key creation request.
    /// - Use the generated API Key (and Secret key, if applicable) to perform margin trading and
    /// listenKey generation via **Spot** REST API (`https://api.binance.com/api/v3/*`) endpoints.
    ///
    /// Read REST API or WebSocket API documentation to learn how to use different API keys
    ///
    /// You need to enable Permits “Enable Spot & Margin Trading” option for the API Key which
    /// requests this endpoint.
    ///
    /// Weight(UID): 1
    ///
    /// Security Type: TRADE
    ///
    /// Response Notes:
    /// - Error Code Description
    ///
    /// - **UNSUPPORTED_OPERATION** : Portfolio Margin is an unsupported
    /// product, please change the account type to a supported margin product.
    ///
    /// - **Forbidden**:  Cross Margin Pro accounts require additional
    /// agreements, please contact your relationship manager.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#create-special-key
    [[nodiscard]] common::RestApiResponse<CreateSpecialKeyResponse>
    create_special_key(const CreateSpecialKeyParams& params) const;

    /// Asynchronous `create_special_key()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<CreateSpecialKeyResponse>)`.
    template <class CompletionToken>
    auto async_create_special_key(const CreateSpecialKeyParams& params,
                                  CompletionToken&& token) const {
        return common::async_send<CreateSpecialKeyResponse>(
            client_, create_special_key_request(params), std::forward<CompletionToken>(token));
    }

    /// Delete Special Key(Low-Latency Trading) (TRADE)
    ///
    /// DELETE /sapi/v1/margin/apiKey.
    ///
    /// Deleting your Margin Special Key alone does not exit you from the Margin Special Key
    /// framework or discharge your obligations under the Margin Special Key Supplemental Product
    /// Terms. To fully exit, you must:
    ///
    /// 1. Delete your Margin Special Key.
    /// 2. Ensure there are no outstanding liabilities on the account.
    /// 3. Call the Exit Margin Special Key API endpoint.
    /// 4. Confirm the exit status via the API response.
    ///
    /// Only after step 4 is completed and the exit status is confirmed by Binance will your account
    /// revert to standard liquidation logic and no longer be subject to the Margin Special Key
    /// Supplemental Product Terms.
    ///
    /// If apiKey is given, apiName will be ignored. If apiName is given with no
    /// apiKey, all apikeys with given apiName will be deleted.
    ///
    /// You need to enable Permits “Enable Spot & Margin” option for the API Key
    /// which requests this endpoint.
    ///
    /// Weight(UID): 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#delete-special-key
    [[nodiscard]] common::RestApiResponse<boost::json::value>
    delete_special_key(const DeleteSpecialKeyParams& params = {}) const;

    /// Asynchronous `delete_special_key()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<boost::json::value>)`.
    template <class CompletionToken>
    auto async_delete_special_key(const DeleteSpecialKeyParams& params,
                                  CompletionToken&& token) const {
        return common::async_send<boost::json::value>(client_, delete_special_key_request(params),
                                                      std::forward<CompletionToken>(token));
    }

    /// Query Special key(Low Latency Trading) (TRADE)
    ///
    /// GET /sapi/v1/margin/apiKey.
    ///
    /// Query Special Key Information.
    ///
    /// This only applies to Special Key for Low Latency Trading.
    ///
    /// Weight(UID): 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#query-special-key
    [[nodiscard]] common::RestApiResponse<QuerySpecialKeyResponse>
    query_special_key(const QuerySpecialKeyParams& params = {}) const;

    /// Asynchronous `query_special_key()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<QuerySpecialKeyResponse>)`.
    template <class CompletionToken>
    auto async_query_special_key(const QuerySpecialKeyParams& params,
                                 CompletionToken&& token) const {
        return common::async_send<QuerySpecialKeyResponse>(
            client_, query_special_key_request(params), std::forward<CompletionToken>(token));
    }

    /// Edit ip for Special Key(Low-Latency Trading) (TRADE)
    ///
    /// PUT /sapi/v1/margin/apiKey/ip.
    ///
    /// Edit ip restriction. This only applies to Special Key for Low Latency
    /// Trading.
    ///
    /// You need to enable Permits “Enable Spot & Margin” option for the API Key
    /// which requests this endpoint.
    ///
    /// Weight(UID): 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#edit-ip-for-special-key
    [[nodiscard]] common::RestApiResponse<boost::json::value>
    edit_ip_for_special_key(const EditIpForSpecialKeyParams& params) const;

    /// Asynchronous `edit_ip_for_special_key()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<boost::json::value>)`.
    template <class CompletionToken>
    auto async_edit_ip_for_special_key(const EditIpForSpecialKeyParams& params,
                                       CompletionToken&& token) const {
        return common::async_send<boost::json::value>(
            client_, edit_ip_for_special_key_request(params), std::forward<CompletionToken>(token));
    }

    /// Exit Special Key Mode (TRADE)
    ///
    /// POST /sapi/v1/margin/exit-special-key-mode.
    ///
    /// Exit the Margin Special Key mode for Cross Margin Classic accounts.
    ///
    /// **All outstanding liabilities under the Cross Margin Classic account must be fully repaid
    /// before calling this endpoint.** Deleting the Margin Special Key alone does not constitute a
    /// valid exit.
    ///
    /// When a user creates a Margin Special API Key, the account enters "Special Key Mode". Upon a
    /// successful request, the following actions will be performed atomically:
    ///
    /// 1. All existing Margin Special API Keys under the Cross Margin Classic mode account will be
    /// deleted.
    /// 2. All pre-execution margin checks (including Open-order-loss calculation) will revert to
    /// standard mode.
    /// 3. A cooldown period (default: 24 hours) will be enforced, during which the account will not
    /// be permitted to create new Margin Special API Keys.
    ///
    /// For more information, please refer to FAQ.
    ///
    /// **Preconditions:**
    ///
    /// The following conditions must be met; otherwise the request will be rejected:
    ///
    /// - Account type must be **Cross Margin Classic**.
    /// - Account must currently be in **Special Key Mode**. If not, the request silently succeeds.
    /// - Account must **not be in liquidation**.
    /// - Account must **have no liability**.
    ///
    /// You need to enable "Permits Enable Spot & Margin Trading" option for the API Key which
    /// requests this endpoint.
    ///
    /// Weight(UID): 10
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#exit-special-key-mode
    [[nodiscard]] common::RestApiResponse<boost::json::value>
    exit_special_key_mode(const ExitSpecialKeyModeParams& params = {}) const;

    /// Asynchronous `exit_special_key_mode()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<boost::json::value>)`.
    template <class CompletionToken>
    auto async_exit_special_key_mode(const ExitSpecialKeyModeParams& params,
                                     CompletionToken&& token) const {
        return common::async_send<boost::json::value>(
            client_, exit_special_key_mode_request(params), std::forward<CompletionToken>(token));
    }

    /// Get Force Liquidation Record (USER_DATA)
    ///
    /// GET /sapi/v1/margin/forceLiquidationRec.
    ///
    /// Get Force Liquidation Record
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Response in descending order
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#get-force-liquidation-record
    [[nodiscard]] common::RestApiResponse<GetForceLiquidationRecordResponse>
    get_force_liquidation_record(const GetForceLiquidationRecordParams& params = {}) const;

    /// Asynchronous `get_force_liquidation_record()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetForceLiquidationRecordResponse>)`.
    template <class CompletionToken>
    auto async_get_force_liquidation_record(const GetForceLiquidationRecordParams& params,
                                            CompletionToken&& token) const {
        return common::async_send<GetForceLiquidationRecordResponse>(
            client_, get_force_liquidation_record_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Small Liability Exchange Coin List (USER_DATA)
    ///
    /// GET /sapi/v1/margin/exchange-small-liability.
    ///
    /// Query the coins which can be small liability exchange
    ///
    /// Weight(IP): 100
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#get-small-liability-exchange-coin-list
    [[nodiscard]] common::RestApiResponse<
        std::vector<GetSmallLiabilityExchangeCoinListResponseInner>>
    get_small_liability_exchange_coin_list(
        const GetSmallLiabilityExchangeCoinListParams& params = {}) const;

    /// Asynchronous `get_small_liability_exchange_coin_list()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<GetSmallLiabilityExchangeCoinListResponseInner>>)`.
    template <class CompletionToken>
    auto async_get_small_liability_exchange_coin_list(
        const GetSmallLiabilityExchangeCoinListParams& params, CompletionToken&& token) const {
        return common::async_send<std::vector<GetSmallLiabilityExchangeCoinListResponseInner>>(
            client_, get_small_liability_exchange_coin_list_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Small Liability Exchange (MARGIN)
    ///
    /// POST /sapi/v1/margin/exchange-small-liability.
    ///
    /// Small Liability Exchange
    ///
    /// Weight(UID): 3000
    ///
    /// Security Type: MARGIN
    ///
    /// Notes:
    /// - Only convert once within 6 hours
    /// - Only liability valuation less than 10 USDT are supported
    /// - The maximum number of coin is 10
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#small-liability-exchange
    [[nodiscard]] common::RestApiResponse<boost::json::value>
    small_liability_exchange(const SmallLiabilityExchangeParams& params) const;

    /// Asynchronous `small_liability_exchange()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<boost::json::value>)`.
    template <class CompletionToken>
    auto async_small_liability_exchange(const SmallLiabilityExchangeParams& params,
                                        CompletionToken&& token) const {
        return common::async_send<boost::json::value>(client_,
                                                      small_liability_exchange_request(params),
                                                      std::forward<CompletionToken>(token));
    }

    /// Get Small Liability Exchange History (USER_DATA)
    ///
    /// GET /sapi/v1/margin/exchange-small-liability-history.
    ///
    /// Get Small liability Exchange History
    ///
    /// Weight(UID): 100
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#get-small-liability-exchange-history
    [[nodiscard]] common::RestApiResponse<GetSmallLiabilityExchangeHistoryResponse>
    get_small_liability_exchange_history(
        const GetSmallLiabilityExchangeHistoryParams& params) const;

    /// Asynchronous `get_small_liability_exchange_history()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<GetSmallLiabilityExchangeHistoryResponse>)`.
    template <class CompletionToken>
    auto
    async_get_small_liability_exchange_history(const GetSmallLiabilityExchangeHistoryParams& params,
                                               CompletionToken&& token) const {
        return common::async_send<GetSmallLiabilityExchangeHistoryResponse>(
            client_, get_small_liability_exchange_history_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Liquidation Loan Repay (MARGIN)
    ///
    /// POST /sapi/v1/margin/liquidation-loan/repay.
    ///
    /// Repays the outstanding cross-margin liquidation loan from the user's spot wallet. A
    /// liquidation loan represents the account deficit incurred when account equity turns negative
    /// during liquidation (bankruptcy). The repayment amount must be greater than 0 and cannot
    /// exceed the remaining loan balance. If the Spot Account has insufficient USDC balance, the
    /// repayment will fail.
    ///
    /// Weight(UID): 100
    ///
    /// Security Type: MARGIN
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#liquidation-loan-repay
    [[nodiscard]] common::RestApiResponse<LiquidationLoanRepayResponse>
    liquidation_loan_repay(const LiquidationLoanRepayParams& params) const;

    /// Asynchronous `liquidation_loan_repay()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<LiquidationLoanRepayResponse>)`.
    template <class CompletionToken>
    auto async_liquidation_loan_repay(const LiquidationLoanRepayParams& params,
                                      CompletionToken&& token) const {
        return common::async_send<LiquidationLoanRepayResponse>(
            client_, liquidation_loan_repay_request(params), std::forward<CompletionToken>(token));
    }

    /// Margin Account Cancel all Open Orders on a Symbol (TRADE)
    ///
    /// DELETE /sapi/v1/margin/openOrders.
    ///
    /// Cancels all active orders on a symbol for margin account.
    ///
    /// This includes OCO orders.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#margin-account-cancel-all-open-orders-on-asymbol
    [[nodiscard]] common::RestApiResponse<
        std::vector<MarginAccountCancelAllOpenOrdersOnASymbolResponseInner>>
    margin_account_cancel_all_open_orders_on_a_symbol(
        const MarginAccountCancelAllOpenOrdersOnASymbolParams& params) const;

    /// Asynchronous `margin_account_cancel_all_open_orders_on_a_symbol()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<MarginAccountCancelAllOpenOrdersOnASymbolResponseInner>>)`.
    template <class CompletionToken>
    auto async_margin_account_cancel_all_open_orders_on_a_symbol(
        const MarginAccountCancelAllOpenOrdersOnASymbolParams& params,
        CompletionToken&& token) const {
        return common::async_send<
            std::vector<MarginAccountCancelAllOpenOrdersOnASymbolResponseInner>>(
            client_, margin_account_cancel_all_open_orders_on_a_symbol_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Query Margin Account's Open Orders (USER_DATA)
    ///
    /// GET /sapi/v1/margin/openOrders.
    ///
    /// Query Margin Account's Open Orders
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If the symbol is not sent, orders for all symbols will be returned in
    /// an array.
    ///
    /// - When all symbols are returned, the number of requests counted against
    /// the rate limiter is equal to the number of symbols currently trading on
    /// the exchange.
    ///
    /// - If isIsolated ="TRUE", symbol must be sent.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#query-margin-accounts-open-orders
    [[nodiscard]] common::RestApiResponse<std::vector<QueryMarginAccountsOpenOrdersResponseInner>>
    query_margin_accounts_open_orders(const QueryMarginAccountsOpenOrdersParams& params = {}) const;

    /// Asynchronous `query_margin_accounts_open_orders()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<QueryMarginAccountsOpenOrdersResponseInner>>)`.
    template <class CompletionToken>
    auto async_query_margin_accounts_open_orders(const QueryMarginAccountsOpenOrdersParams& params,
                                                 CompletionToken&& token) const {
        return common::async_send<std::vector<QueryMarginAccountsOpenOrdersResponseInner>>(
            client_, query_margin_accounts_open_orders_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Margin Account Cancel OCO (TRADE)
    ///
    /// DELETE /sapi/v1/margin/orderList.
    ///
    /// Cancel an entire Order List for a margin account.
    ///
    /// Weight(UID): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Canceling an individual leg will cancel the entire OCO
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#margin-account-cancel-oco
    [[nodiscard]] common::RestApiResponse<MarginAccountCancelOcoResponse>
    margin_account_cancel_oco(const MarginAccountCancelOcoParams& params) const;

    /// Asynchronous `margin_account_cancel_oco()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<MarginAccountCancelOcoResponse>)`.
    template <class CompletionToken>
    auto async_margin_account_cancel_oco(const MarginAccountCancelOcoParams& params,
                                         CompletionToken&& token) const {
        return common::async_send<MarginAccountCancelOcoResponse>(
            client_, margin_account_cancel_oco_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Query Margin Account's OCO (USER_DATA)
    ///
    /// GET /sapi/v1/margin/orderList.
    ///
    /// Retrieves a specific OCO based on provided optional parameters
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#query-margin-accounts-oco
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

    /// Margin Account Cancel Order (TRADE)
    ///
    /// DELETE /sapi/v1/margin/order.
    ///
    /// Cancel an active order for margin account.
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Either orderId or origClientOrderId must be sent.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#margin-account-cancel-order
    [[nodiscard]] common::RestApiResponse<MarginAccountCancelOrderResponse>
    margin_account_cancel_order(const MarginAccountCancelOrderParams& params) const;

    /// Asynchronous `margin_account_cancel_order()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<MarginAccountCancelOrderResponse>)`.
    template <class CompletionToken>
    auto async_margin_account_cancel_order(const MarginAccountCancelOrderParams& params,
                                           CompletionToken&& token) const {
        return common::async_send<MarginAccountCancelOrderResponse>(
            client_, margin_account_cancel_order_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Margin Account New Order (TRADE)
    ///
    /// POST /sapi/v1/margin/order.
    ///
    /// Post a new order for margin account.
    ///
    /// Weight: 6(UID) or 1500(UID) when sideEffectType is MARGIN_BUY or AUTO_BORROW_REPAY
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - autoRepayAtCancel is suggested to set as “FALSE” to keep liability unrepaid under high
    /// frequent new order/cancel order execution
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#margin-account-new-order
    [[nodiscard]] common::RestApiResponse<MarginAccountNewOrderResponse>
    margin_account_new_order(const MarginAccountNewOrderParams& params) const;

    /// Asynchronous `margin_account_new_order()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<MarginAccountNewOrderResponse>)`.
    template <class CompletionToken>
    auto async_margin_account_new_order(const MarginAccountNewOrderParams& params,
                                        CompletionToken&& token) const {
        return common::async_send<MarginAccountNewOrderResponse>(
            client_, margin_account_new_order_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Query Margin Account's Order (USER_DATA)
    ///
    /// GET /sapi/v1/margin/order.
    ///
    /// Query Margin Account's Order
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Either orderId or origClientOrderId must be sent.
    ///
    /// - For some historical orders cummulativeQuoteQty will be < 0, meaning
    /// the data is not available at this time.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#query-margin-accounts-order
    [[nodiscard]] common::RestApiResponse<QueryMarginAccountsOrderResponse>
    query_margin_accounts_order(const QueryMarginAccountsOrderParams& params) const;

    /// Asynchronous `query_margin_accounts_order()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<QueryMarginAccountsOrderResponse>)`.
    template <class CompletionToken>
    auto async_query_margin_accounts_order(const QueryMarginAccountsOrderParams& params,
                                           CompletionToken&& token) const {
        return common::async_send<QueryMarginAccountsOrderResponse>(
            client_, query_margin_accounts_order_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Margin Account New OCO (TRADE)
    ///
    /// POST /sapi/v1/margin/order/oco.
    ///
    /// Send in a new OCO for a margin account
    ///
    /// Weight: 6(UID) or 1500(UID) when sideEffectType is MARGIN_BUY or AUTO_BORROW_REPAY
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - autoRepayAtCancel is suggested to set as “FALSE” to keep liability unrepaid under high
    /// frequent new order/cancel order execution
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#margin-account-new-oco
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

    /// Margin Account New OTO (TRADE)
    ///
    /// POST /sapi/v1/margin/order/oto.
    ///
    /// Post a new OTO order for margin account:
    ///
    /// - An OTO (One-Triggers-the-Other) is an order list comprised of 2
    /// orders.
    ///
    /// - The first order is called the **working order** and must be `LIMIT` or
    /// `LIMIT_MAKER`. Initially, only the working order goes on the order book.
    ///
    /// - The second order is called the **pending order**. It can be any order
    /// type except for `MARKET` orders using parameter `quoteOrderQty`. The
    /// pending order is only placed on the order book when the working order
    /// gets **fully filled**.
    ///
    /// - If either the working order or the pending order is cancelled
    /// individually, the other order in the order list will also be canceled or
    /// expired.
    ///
    /// - When the order list is placed, if the working order gets **immediately
    /// fully filled**, the placement response will show the working order as
    /// `FILLED` but the pending order will still appear as `PENDING_NEW`. You
    /// need to query the status of the pending order again to see its updated
    /// status.
    ///
    /// - OTOs add **2 orders** to the unfilled order count,
    /// `EXCHANGE_MAX_NUM_ORDERS` filter and `MAX_NUM_ORDERS` filter.
    ///
    /// Weight: 6(UID) or 1500(UID) when sideEffectType is MARGIN_BUY or AUTO_BORROW_REPAY
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - autoRepayAtCancel is suggested to set as “FALSE” to keep liability unrepaid under high
    /// frequent new order/cancel order execution
    /// - Depending on the `pendingType` or `workingType`, some optional parameters will become
    /// mandatory:
    ///
    /// | Type | Additional mandatory parameters | Additional information |
    /// | --- | --- | --- |
    /// | `workingType` = `LIMIT` | `workingTimeInForce` | |
    /// | `pendingType` = `LIMIT` | `pendingPrice`, `pendingTimeInForce` | |
    /// | `pendingType` = `STOP_LOSS` or `TAKE_PROFIT` | `pendingStopPrice` and/or
    /// `pendingTrailingDelta` | | | `pendingType` = `STOP_LOSS_LIMIT` or `TAKE_PROFIT_LIMIT` |
    /// `pendingPrice`, `pendingStopPrice` and/or `pendingTrailingDelta`, `pendingTimeInForce` | |
    /// | `pendingTrailingDelta` is provided | `pendingPrice` | |
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#margin-account-new-oto
    [[nodiscard]] common::RestApiResponse<MarginAccountNewOtoResponse>
    margin_account_new_oto(const MarginAccountNewOtoParams& params) const;

    /// Asynchronous `margin_account_new_oto()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<MarginAccountNewOtoResponse>)`.
    template <class CompletionToken>
    auto async_margin_account_new_oto(const MarginAccountNewOtoParams& params,
                                      CompletionToken&& token) const {
        return common::async_send<MarginAccountNewOtoResponse>(
            client_, margin_account_new_oto_request(params), std::forward<CompletionToken>(token));
    }

    /// Margin Account New OTOCO (TRADE)
    ///
    /// POST /sapi/v1/margin/order/otoco.
    ///
    /// Post a new OTOCO order for margin account：
    ///
    /// - An OTOCO (One-Triggers-One-Cancels-the-Other) is an order list
    /// comprised of 3 orders.
    ///
    /// - The first order is called the **working order** and must be `LIMIT` or
    /// `LIMIT_MAKER`. Initially, only the working order goes on the order book.
    ///   - The behavior of the working order is the same as the OTO.
    /// - OTOCO has 2 pending orders (pending above and pending below), forming
    /// an OCO pair. The pending orders are only placed on the order book when
    /// the working order gets **fully filled**.
    ///   - The rules of the pending above and pending below follow the same rules as the Order List
    ///   OCO.
    /// - OTOCOs add **3 orders** against the unfilled order count,
    /// `EXCHANGE_MAX_NUM_ORDERS` filter, and `MAX_NUM_ORDERS` filter.
    ///
    /// Weight: 6(UID) or 1500(UID) when sideEffectType is MARGIN_BUY or AUTO_BORROW_REPAY
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - autoRepayAtCancel is suggested to set as “FALSE” to keep liability unrepaid under high
    /// frequent new order/cancel order execution
    /// - Depending on the `pendingAboveType`/`pendingBelowType` or `workingType`, some optional
    /// parameters will become mandatory: | Type                                 | Additional
    /// mandatory parameters                              | Additional information | |
    /// ------------------------------------ |
    /// ------------------------------------------------------------ | ---------------------- | |
    /// `workingType` = `LIMIT`              | `workingTimeInForce` |                        | |
    /// `pendingAboveType`= `LIMIT_MAKER`    | `pendingAbovePrice` |                        | |
    /// `pendingAboveType`= `STOP_LOSS`      | `pendingAboveStopPrice` and/or
    /// `pendingAboveTrailingDelta`   |                        | |
    /// `pendingAboveType`=`STOP_LOSS_LIMIT` | `pendingAbovePrice`, `pendingAboveStopPrice` and/or
    /// `pendingAboveTrailingDelta`, `pendingAboveTimeInForce` |                        | |
    /// `pendingBelowType`= `LIMIT_MAKER`    | `pendingBelowPrice` |                        | |
    /// `pendingBelowType`= `STOP_LOSS`      | `pendingBelowStopPrice` and/or
    /// `pendingBelowTrailingDelta`   |                        | |
    /// `pendingBelowType`=`STOP_LOSS_LIMIT` | `pendingBelowPrice`, `pendingBelowStopPrice` and/or
    /// `pendingBelowTrailingDelta`, `pendingBelowTimeInForce` |                        | |
    /// `pendingAboveTrailingDelta` is provided | `pendingAbovePrice` |                        | |
    /// `pendingBelowTrailingDelta` is provided | `pendingBelowPrice` |                        |
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#margin-account-new-otoco
    [[nodiscard]] common::RestApiResponse<MarginAccountNewOtocoResponse>
    margin_account_new_otoco(const MarginAccountNewOtocoParams& params) const;

    /// Asynchronous `margin_account_new_otoco()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<MarginAccountNewOtocoResponse>)`.
    template <class CompletionToken>
    auto async_margin_account_new_otoco(const MarginAccountNewOtocoParams& params,
                                        CompletionToken&& token) const {
        return common::async_send<MarginAccountNewOtocoResponse>(
            client_, margin_account_new_otoco_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Margin Manual Liquidation (TRADE)
    ///
    /// POST /sapi/v1/margin/manual-liquidation.
    ///
    /// Margin Manual Liquidation
    ///
    /// Weight(UID): 3000
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - This endpoint supports Cross Margin Classic Mode and Pro Mode.
    /// - Isolated Margin is only supported in restricted regions.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#margin-manual-liquidation
    [[nodiscard]] common::RestApiResponse<MarginManualLiquidationResponse>
    margin_manual_liquidation(const MarginManualLiquidationParams& params) const;

    /// Asynchronous `margin_manual_liquidation()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<MarginManualLiquidationResponse>)`.
    template <class CompletionToken>
    auto async_margin_manual_liquidation(const MarginManualLiquidationParams& params,
                                         CompletionToken&& token) const {
        return common::async_send<MarginManualLiquidationResponse>(
            client_, margin_manual_liquidation_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Query Current Margin Order Count Usage (TRADE)
    ///
    /// GET /sapi/v1/margin/rateLimit/order.
    ///
    /// Displays the user's current margin order count usage for all intervals.
    ///
    /// Weight(IP): 20
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#query-current-margin-order-count-usage
    [[nodiscard]] common::RestApiResponse<
        std::vector<QueryCurrentMarginOrderCountUsageResponseInner>>
    query_current_margin_order_count_usage(
        const QueryCurrentMarginOrderCountUsageParams& params = {}) const;

    /// Asynchronous `query_current_margin_order_count_usage()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<QueryCurrentMarginOrderCountUsageResponseInner>>)`.
    template <class CompletionToken>
    auto async_query_current_margin_order_count_usage(
        const QueryCurrentMarginOrderCountUsageParams& params, CompletionToken&& token) const {
        return common::async_send<std::vector<QueryCurrentMarginOrderCountUsageResponseInner>>(
            client_, query_current_margin_order_count_usage_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Query Liquidation Loan (USER_DATA)
    ///
    /// GET /sapi/v1/margin/liquidation-loan.
    ///
    /// Query the current user's cross-margin liquidation loan information, including the original
    /// loan amount, repaid amount, and remaining amount. When a cross-margin account is liquidated
    /// and the account equity turns negative (bankruptcy), the system generates a liquidation loan
    /// record representing the deficit. This represents the shortfall amount denominated in USDC.
    ///
    /// Weight(UID): 100
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#query-liquidation-loan
    [[nodiscard]] common::RestApiResponse<QueryLiquidationLoanResponse>
    query_liquidation_loan(const QueryLiquidationLoanParams& params = {}) const;

    /// Asynchronous `query_liquidation_loan()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<QueryLiquidationLoanResponse>)`.
    template <class CompletionToken>
    auto async_query_liquidation_loan(const QueryLiquidationLoanParams& params,
                                      CompletionToken&& token) const {
        return common::async_send<QueryLiquidationLoanResponse>(
            client_, query_liquidation_loan_request(params), std::forward<CompletionToken>(token));
    }

    /// Query Liquidation Loan Repay History (USER_DATA)
    ///
    /// GET /sapi/v1/margin/liquidation-loan/repay-history.
    ///
    /// Query the repayment history of cross-margin liquidation loans (deficit caused by bankruptcy
    /// during liquidation). Supports time-range filtering and pagination.
    ///
    /// Weight(UID): 100
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - The maximum query range is 90 days. If `startTime` is earlier than 90 days ago, it will be
    /// clamped to 90 days ago.
    /// - Only records with status `SUCCESS` or `PENDING` are returned. Failed repayment records are
    /// excluded.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#query-liquidation-loan-repay-history
    [[nodiscard]] common::RestApiResponse<QueryLiquidationLoanRepayHistoryResponse>
    query_liquidation_loan_repay_history(
        const QueryLiquidationLoanRepayHistoryParams& params = {}) const;

    /// Asynchronous `query_liquidation_loan_repay_history()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<QueryLiquidationLoanRepayHistoryResponse>)`.
    template <class CompletionToken>
    auto
    async_query_liquidation_loan_repay_history(const QueryLiquidationLoanRepayHistoryParams& params,
                                               CompletionToken&& token) const {
        return common::async_send<QueryLiquidationLoanRepayHistoryResponse>(
            client_, query_liquidation_loan_repay_history_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Query Margin Account's all OCO (USER_DATA)
    ///
    /// GET /sapi/v1/margin/allOrderList.
    ///
    /// Retrieves all OCO for a specific margin account based on provided optional parameters
    ///
    /// Weight(IP): 200
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#query-margin-accounts-all-oco
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

    /// Query Margin Account's All Orders (USER_DATA)
    ///
    /// GET /sapi/v1/margin/allOrders.
    ///
    /// Query Margin Account's All Orders
    ///
    /// Weight(IP): 200
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If orderId is set, it will get orders >= that orderId. Otherwise the
    /// orders within 24 hours are returned.
    ///
    /// - For some historical orders cummulativeQuoteQty will be < 0, meaning
    /// the data is not available at this time.
    ///
    /// - Less than 24 hours between startTime and endTime.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#query-margin-accounts-all-orders
    [[nodiscard]] common::RestApiResponse<std::vector<QueryMarginAccountsAllOrdersResponseInner>>
    query_margin_accounts_all_orders(const QueryMarginAccountsAllOrdersParams& params) const;

    /// Asynchronous `query_margin_accounts_all_orders()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<QueryMarginAccountsAllOrdersResponseInner>>)`.
    template <class CompletionToken>
    auto async_query_margin_accounts_all_orders(const QueryMarginAccountsAllOrdersParams& params,
                                                CompletionToken&& token) const {
        return common::async_send<std::vector<QueryMarginAccountsAllOrdersResponseInner>>(
            client_, query_margin_accounts_all_orders_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Query Margin Account's Open OCO (USER_DATA)
    ///
    /// GET /sapi/v1/margin/openOrderList.
    ///
    /// Query Margin Account's Open OCO
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#query-margin-accounts-open-oco
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

    /// Query Margin Account's Open OTO/OTOCO Order Lists (USER_DATA)
    ///
    /// GET /sapi/v1/margin/oto/openOrderList.
    ///
    /// Retrieves all open OTO / OTOCO order lists of the margin account.
    ///
    /// Notes:
    /// - The returned list contains order lists whose `listOrderStatus` is `EXECUTING`, i.e. at
    /// least one order of the list is still open (`NEW` / `PARTIALLY_FILLED`).
    /// - For OTO, the `orders` array contains 2 orders: the working order and the pending order.
    /// - For OTOCO, the `orders` array contains 3 orders: the working order and the two pending
    /// orders (pending above / pending below).
    ///
    /// Weight(UID): 10
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#query-margin-accounts-open-otootoco-order-lists
    [[nodiscard]] common::RestApiResponse<
        std::vector<QueryMarginAccountsOpenOtootocoOrderListsResponseInner>>
    query_margin_accounts_open_otootoco_order_lists(
        const QueryMarginAccountsOpenOtootocoOrderListsParams& params = {}) const;

    /// Asynchronous `query_margin_accounts_open_otootoco_order_lists()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<QueryMarginAccountsOpenOtootocoOrderListsResponseInner>>)`.
    template <class CompletionToken>
    auto async_query_margin_accounts_open_otootoco_order_lists(
        const QueryMarginAccountsOpenOtootocoOrderListsParams& params,
        CompletionToken&& token) const {
        return common::async_send<
            std::vector<QueryMarginAccountsOpenOtootocoOrderListsResponseInner>>(
            client_, query_margin_accounts_open_otootoco_order_lists_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Query Margin Account's Trade List (USER_DATA)
    ///
    /// GET /sapi/v1/margin/myTrades.
    ///
    /// Query Margin Account's Trade List
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If fromId is set, it will get trades >= that fromId. Otherwise the
    /// trades within 24 hours are returned.
    ///
    /// - Less than 24 hours between startTime and endTime.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#query-margin-accounts-trade-list
    [[nodiscard]] common::RestApiResponse<std::vector<QueryMarginAccountsTradeListResponseInner>>
    query_margin_accounts_trade_list(const QueryMarginAccountsTradeListParams& params) const;

    /// Asynchronous `query_margin_accounts_trade_list()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<QueryMarginAccountsTradeListResponseInner>>)`.
    template <class CompletionToken>
    auto async_query_margin_accounts_trade_list(const QueryMarginAccountsTradeListParams& params,
                                                CompletionToken&& token) const {
        return common::async_send<std::vector<QueryMarginAccountsTradeListResponseInner>>(
            client_, query_margin_accounts_trade_list_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Query Prevented Matches (USER_DATA)
    ///
    /// GET /sapi/v1/margin/myPreventedMatches.
    ///
    /// Displays the list of orders that were expired due to STP. (Self-Trade Prevention).
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Supported parameter combinations:
    ///
    /// - `symbol` + `preventedMatchId`
    ///
    /// - `symbol` + `orderId`
    ///
    /// - `symbol` + `orderId` + `fromPreventedMatchId`
    ///
    /// - If `orderId` is provided, all prevented matches for that order will be
    /// returned.
    ///
    /// - If `preventedMatchId` is provided, the specific prevented match will
    /// be returned.
    ///
    /// - A single request returns a maximum of 500 records. If there are more
    /// than 500 records, use `symbol` + `orderId` + `fromPreventedMatchId`
    /// combination for pagination.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#query-prevented-matches
    [[nodiscard]] common::RestApiResponse<std::vector<QueryPreventedMatchesResponseInner>>
    query_prevented_matches(const QueryPreventedMatchesParams& params) const;

    /// Asynchronous `query_prevented_matches()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<QueryPreventedMatchesResponseInner>>)`.
    template <class CompletionToken>
    auto async_query_prevented_matches(const QueryPreventedMatchesParams& params,
                                       CompletionToken&& token) const {
        return common::async_send<std::vector<QueryPreventedMatchesResponseInner>>(
            client_, query_prevented_matches_request(params), std::forward<CompletionToken>(token));
    }

    /// Query Special key List(Low Latency Trading) (TRADE)
    ///
    /// GET /sapi/v1/margin/api-key-list.
    ///
    /// This only applies to Special Key for Low Latency Trading.
    ///
    /// Weight(UID): 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/trade#query-special-key-list
    [[nodiscard]] common::RestApiResponse<std::vector<QuerySpecialKeyListResponseInner>>
    query_special_key_list(const QuerySpecialKeyListParams& params = {}) const;

    /// Asynchronous `query_special_key_list()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<QuerySpecialKeyListResponseInner>>)`.
    template <class CompletionToken>
    auto async_query_special_key_list(const QuerySpecialKeyListParams& params,
                                      CompletionToken&& token) const {
        return common::async_send<std::vector<QuerySpecialKeyListResponseInner>>(
            client_, query_special_key_list_request(params), std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest
    create_special_key_request(const CreateSpecialKeyParams& params) const;
    [[nodiscard]] common::RestRequest
    delete_special_key_request(const DeleteSpecialKeyParams& params) const;
    [[nodiscard]] common::RestRequest
    query_special_key_request(const QuerySpecialKeyParams& params) const;
    [[nodiscard]] common::RestRequest
    edit_ip_for_special_key_request(const EditIpForSpecialKeyParams& params) const;
    [[nodiscard]] common::RestRequest
    exit_special_key_mode_request(const ExitSpecialKeyModeParams& params) const;
    [[nodiscard]] common::RestRequest
    get_force_liquidation_record_request(const GetForceLiquidationRecordParams& params) const;
    [[nodiscard]] common::RestRequest get_small_liability_exchange_coin_list_request(
        const GetSmallLiabilityExchangeCoinListParams& params) const;
    [[nodiscard]] common::RestRequest
    small_liability_exchange_request(const SmallLiabilityExchangeParams& params) const;
    [[nodiscard]] common::RestRequest get_small_liability_exchange_history_request(
        const GetSmallLiabilityExchangeHistoryParams& params) const;
    [[nodiscard]] common::RestRequest
    liquidation_loan_repay_request(const LiquidationLoanRepayParams& params) const;
    [[nodiscard]] common::RestRequest margin_account_cancel_all_open_orders_on_a_symbol_request(
        const MarginAccountCancelAllOpenOrdersOnASymbolParams& params) const;
    [[nodiscard]] common::RestRequest query_margin_accounts_open_orders_request(
        const QueryMarginAccountsOpenOrdersParams& params) const;
    [[nodiscard]] common::RestRequest
    margin_account_cancel_oco_request(const MarginAccountCancelOcoParams& params) const;
    [[nodiscard]] common::RestRequest
    query_margin_accounts_oco_request(const QueryMarginAccountsOcoParams& params) const;
    [[nodiscard]] common::RestRequest
    margin_account_cancel_order_request(const MarginAccountCancelOrderParams& params) const;
    [[nodiscard]] common::RestRequest
    margin_account_new_order_request(const MarginAccountNewOrderParams& params) const;
    [[nodiscard]] common::RestRequest
    query_margin_accounts_order_request(const QueryMarginAccountsOrderParams& params) const;
    [[nodiscard]] common::RestRequest
    margin_account_new_oco_request(const MarginAccountNewOcoParams& params) const;
    [[nodiscard]] common::RestRequest
    margin_account_new_oto_request(const MarginAccountNewOtoParams& params) const;
    [[nodiscard]] common::RestRequest
    margin_account_new_otoco_request(const MarginAccountNewOtocoParams& params) const;
    [[nodiscard]] common::RestRequest
    margin_manual_liquidation_request(const MarginManualLiquidationParams& params) const;
    [[nodiscard]] common::RestRequest query_current_margin_order_count_usage_request(
        const QueryCurrentMarginOrderCountUsageParams& params) const;
    [[nodiscard]] common::RestRequest
    query_liquidation_loan_request(const QueryLiquidationLoanParams& params) const;
    [[nodiscard]] common::RestRequest query_liquidation_loan_repay_history_request(
        const QueryLiquidationLoanRepayHistoryParams& params) const;
    [[nodiscard]] common::RestRequest
    query_margin_accounts_all_oco_request(const QueryMarginAccountsAllOcoParams& params) const;
    [[nodiscard]] common::RestRequest query_margin_accounts_all_orders_request(
        const QueryMarginAccountsAllOrdersParams& params) const;
    [[nodiscard]] common::RestRequest
    query_margin_accounts_open_oco_request(const QueryMarginAccountsOpenOcoParams& params) const;
    [[nodiscard]] common::RestRequest query_margin_accounts_open_otootoco_order_lists_request(
        const QueryMarginAccountsOpenOtootocoOrderListsParams& params) const;
    [[nodiscard]] common::RestRequest query_margin_accounts_trade_list_request(
        const QueryMarginAccountsTradeListParams& params) const;
    [[nodiscard]] common::RestRequest
    query_prevented_matches_request(const QueryPreventedMatchesParams& params) const;
    [[nodiscard]] common::RestRequest
    query_special_key_list_request(const QuerySpecialKeyListParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::margin_trading::rest_api
