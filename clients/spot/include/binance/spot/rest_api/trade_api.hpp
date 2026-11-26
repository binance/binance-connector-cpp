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
#include <binance/spot/export.hpp>
#include <binance/spot/rest_api/models/delete_open_orders_response_inner.hpp>
#include <binance/spot/rest_api/models/delete_order_list_response.hpp>
#include <binance/spot/rest_api/models/delete_order_response.hpp>
#include <binance/spot/rest_api/models/new_order_response.hpp>
#include <binance/spot/rest_api/models/order_amend_keep_priority_response.hpp>
#include <binance/spot/rest_api/models/order_cancel_replace_response.hpp>
#include <binance/spot/rest_api/models/order_list_oco_response.hpp>
#include <binance/spot/rest_api/models/order_list_opo_response.hpp>
#include <binance/spot/rest_api/models/order_list_opoco_response.hpp>
#include <binance/spot/rest_api/models/order_list_oto_response.hpp>
#include <binance/spot/rest_api/models/order_list_otoco_response.hpp>
#include <binance/spot/rest_api/models/order_oco_response.hpp>
#include <binance/spot/rest_api/models/order_test_response.hpp>
#include <binance/spot/rest_api/models/sor_order_response.hpp>
#include <binance/spot/rest_api/models/sor_order_test_response.hpp>

namespace binance::spot::rest_api {

enum class DeleteOrderCancelRestrictionsEnum {
    OnlyNew,
    OnlyPartiallyFilled,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(DeleteOrderCancelRestrictionsEnum value) noexcept;
BINANCE_SPOT_EXPORT DeleteOrderCancelRestrictionsEnum
tag_invoke(boost::json::value_to_tag<DeleteOrderCancelRestrictionsEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    DeleteOrderCancelRestrictionsEnum value);

enum class NewOrderSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view to_string(NewOrderSideEnum value) noexcept;
BINANCE_SPOT_EXPORT NewOrderSideEnum tag_invoke(boost::json::value_to_tag<NewOrderSideEnum> /*tag*/,
                                                const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    NewOrderSideEnum value);

enum class NewOrderTypeEnum {
    Market,
    Limit,
    StopLoss,
    StopLossLimit,
    TakeProfit,
    TakeProfitLimit,
    LimitMaker,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view to_string(NewOrderTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT NewOrderTypeEnum tag_invoke(boost::json::value_to_tag<NewOrderTypeEnum> /*tag*/,
                                                const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    NewOrderTypeEnum value);

enum class NewOrderTimeInForceEnum {
    Gtc,
    Ioc,
    Fok,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(NewOrderTimeInForceEnum value) noexcept;
BINANCE_SPOT_EXPORT NewOrderTimeInForceEnum tag_invoke(
    boost::json::value_to_tag<NewOrderTimeInForceEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    NewOrderTimeInForceEnum value);

enum class NewOrderNewOrderRespTypeEnum {
    Ack,
    Result,
    Full,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(NewOrderNewOrderRespTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT NewOrderNewOrderRespTypeEnum tag_invoke(
    boost::json::value_to_tag<NewOrderNewOrderRespTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    NewOrderNewOrderRespTypeEnum value);

enum class NewOrderSelfTradePreventionModeEnum {
    None_,
    ExpireTaker,
    ExpireMaker,
    ExpireBoth,
    Decrement,
    Transfer,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(NewOrderSelfTradePreventionModeEnum value) noexcept;
BINANCE_SPOT_EXPORT NewOrderSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<NewOrderSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    NewOrderSelfTradePreventionModeEnum value);

enum class NewOrderPegPriceTypeEnum {
    PrimaryPeg,
    MarketPeg,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(NewOrderPegPriceTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT NewOrderPegPriceTypeEnum tag_invoke(
    boost::json::value_to_tag<NewOrderPegPriceTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    NewOrderPegPriceTypeEnum value);

enum class NewOrderPegOffsetTypeEnum {
    PriceLevel,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(NewOrderPegOffsetTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT NewOrderPegOffsetTypeEnum tag_invoke(
    boost::json::value_to_tag<NewOrderPegOffsetTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    NewOrderPegOffsetTypeEnum value);

enum class OrderCancelReplaceSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderCancelReplaceSideEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderCancelReplaceSideEnum tag_invoke(
    boost::json::value_to_tag<OrderCancelReplaceSideEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderCancelReplaceSideEnum value);

enum class OrderCancelReplaceTypeEnum {
    Market,
    Limit,
    StopLoss,
    StopLossLimit,
    TakeProfit,
    TakeProfitLimit,
    LimitMaker,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderCancelReplaceTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderCancelReplaceTypeEnum tag_invoke(
    boost::json::value_to_tag<OrderCancelReplaceTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderCancelReplaceTypeEnum value);

enum class OrderCancelReplaceCancelReplaceModeEnum {
    StopOnFailure,
    AllowFailure,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderCancelReplaceCancelReplaceModeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderCancelReplaceCancelReplaceModeEnum
tag_invoke(boost::json::value_to_tag<OrderCancelReplaceCancelReplaceModeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderCancelReplaceCancelReplaceModeEnum value);

enum class OrderCancelReplaceTimeInForceEnum {
    Gtc,
    Ioc,
    Fok,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderCancelReplaceTimeInForceEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderCancelReplaceTimeInForceEnum
tag_invoke(boost::json::value_to_tag<OrderCancelReplaceTimeInForceEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderCancelReplaceTimeInForceEnum value);

enum class OrderCancelReplaceNewOrderRespTypeEnum {
    Ack,
    Result,
    Full,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderCancelReplaceNewOrderRespTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderCancelReplaceNewOrderRespTypeEnum
tag_invoke(boost::json::value_to_tag<OrderCancelReplaceNewOrderRespTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderCancelReplaceNewOrderRespTypeEnum value);

enum class OrderCancelReplaceSelfTradePreventionModeEnum {
    None_,
    ExpireTaker,
    ExpireMaker,
    ExpireBoth,
    Decrement,
    Transfer,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderCancelReplaceSelfTradePreventionModeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderCancelReplaceSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<OrderCancelReplaceSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderCancelReplaceSelfTradePreventionModeEnum value);

enum class OrderCancelReplaceCancelRestrictionsEnum {
    OnlyNew,
    OnlyPartiallyFilled,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderCancelReplaceCancelRestrictionsEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderCancelReplaceCancelRestrictionsEnum
tag_invoke(boost::json::value_to_tag<OrderCancelReplaceCancelRestrictionsEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderCancelReplaceCancelRestrictionsEnum value);

enum class OrderCancelReplaceOrderRateLimitExceededModeEnum {
    DoNothing,
    CancelOnly,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderCancelReplaceOrderRateLimitExceededModeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderCancelReplaceOrderRateLimitExceededModeEnum
tag_invoke(boost::json::value_to_tag<OrderCancelReplaceOrderRateLimitExceededModeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderCancelReplaceOrderRateLimitExceededModeEnum value);

enum class OrderCancelReplacePegPriceTypeEnum {
    PrimaryPeg,
    MarketPeg,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderCancelReplacePegPriceTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderCancelReplacePegPriceTypeEnum
tag_invoke(boost::json::value_to_tag<OrderCancelReplacePegPriceTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderCancelReplacePegPriceTypeEnum value);

enum class OrderCancelReplacePegOffsetTypeEnum {
    PriceLevel,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderCancelReplacePegOffsetTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderCancelReplacePegOffsetTypeEnum
tag_invoke(boost::json::value_to_tag<OrderCancelReplacePegOffsetTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderCancelReplacePegOffsetTypeEnum value);

enum class OrderListOcoSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view to_string(OrderListOcoSideEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOcoSideEnum
tag_invoke(boost::json::value_to_tag<OrderListOcoSideEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOcoSideEnum value);

enum class OrderListOcoAboveTypeEnum {
    StopLossLimit,
    StopLoss,
    LimitMaker,
    TakeProfit,
    TakeProfitLimit,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOcoAboveTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOcoAboveTypeEnum tag_invoke(
    boost::json::value_to_tag<OrderListOcoAboveTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOcoAboveTypeEnum value);

enum class OrderListOcoBelowTypeEnum {
    StopLoss,
    StopLossLimit,
    TakeProfit,
    TakeProfitLimit,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOcoBelowTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOcoBelowTypeEnum tag_invoke(
    boost::json::value_to_tag<OrderListOcoBelowTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOcoBelowTypeEnum value);

enum class OrderListOcoAboveTimeInForceEnum {
    Gtc,
    Ioc,
    Fok,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOcoAboveTimeInForceEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOcoAboveTimeInForceEnum
tag_invoke(boost::json::value_to_tag<OrderListOcoAboveTimeInForceEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOcoAboveTimeInForceEnum value);

enum class OrderListOcoAbovePegPriceTypeEnum {
    PrimaryPeg,
    MarketPeg,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOcoAbovePegPriceTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOcoAbovePegPriceTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOcoAbovePegPriceTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOcoAbovePegPriceTypeEnum value);

enum class OrderListOcoAbovePegOffsetTypeEnum {
    PriceLevel,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOcoAbovePegOffsetTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOcoAbovePegOffsetTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOcoAbovePegOffsetTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOcoAbovePegOffsetTypeEnum value);

enum class OrderListOcoBelowTimeInForceEnum {
    Gtc,
    Ioc,
    Fok,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOcoBelowTimeInForceEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOcoBelowTimeInForceEnum
tag_invoke(boost::json::value_to_tag<OrderListOcoBelowTimeInForceEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOcoBelowTimeInForceEnum value);

enum class OrderListOcoBelowPegPriceTypeEnum {
    PrimaryPeg,
    MarketPeg,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOcoBelowPegPriceTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOcoBelowPegPriceTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOcoBelowPegPriceTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOcoBelowPegPriceTypeEnum value);

enum class OrderListOcoBelowPegOffsetTypeEnum {
    PriceLevel,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOcoBelowPegOffsetTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOcoBelowPegOffsetTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOcoBelowPegOffsetTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOcoBelowPegOffsetTypeEnum value);

enum class OrderListOcoNewOrderRespTypeEnum {
    Ack,
    Result,
    Full,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOcoNewOrderRespTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOcoNewOrderRespTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOcoNewOrderRespTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOcoNewOrderRespTypeEnum value);

enum class OrderListOcoSelfTradePreventionModeEnum {
    None_,
    ExpireTaker,
    ExpireMaker,
    ExpireBoth,
    Decrement,
    Transfer,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOcoSelfTradePreventionModeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOcoSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<OrderListOcoSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOcoSelfTradePreventionModeEnum value);

enum class OrderListOpoWorkingTypeEnum {
    Limit,
    LimitMaker,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOpoWorkingTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOpoWorkingTypeEnum tag_invoke(
    boost::json::value_to_tag<OrderListOpoWorkingTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOpoWorkingTypeEnum value);

enum class OrderListOpoWorkingSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOpoWorkingSideEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOpoWorkingSideEnum tag_invoke(
    boost::json::value_to_tag<OrderListOpoWorkingSideEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOpoWorkingSideEnum value);

enum class OrderListOpoPendingTypeEnum {
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

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOpoPendingTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOpoPendingTypeEnum tag_invoke(
    boost::json::value_to_tag<OrderListOpoPendingTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOpoPendingTypeEnum value);

enum class OrderListOpoPendingSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOpoPendingSideEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOpoPendingSideEnum tag_invoke(
    boost::json::value_to_tag<OrderListOpoPendingSideEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOpoPendingSideEnum value);

enum class OrderListOpoNewOrderRespTypeEnum {
    Ack,
    Result,
    Full,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOpoNewOrderRespTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOpoNewOrderRespTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOpoNewOrderRespTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOpoNewOrderRespTypeEnum value);

enum class OrderListOpoSelfTradePreventionModeEnum {
    None_,
    ExpireTaker,
    ExpireMaker,
    ExpireBoth,
    Decrement,
    Transfer,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOpoSelfTradePreventionModeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOpoSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<OrderListOpoSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOpoSelfTradePreventionModeEnum value);

enum class OrderListOpoWorkingTimeInForceEnum {
    Gtc,
    Ioc,
    Fok,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOpoWorkingTimeInForceEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOpoWorkingTimeInForceEnum
tag_invoke(boost::json::value_to_tag<OrderListOpoWorkingTimeInForceEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOpoWorkingTimeInForceEnum value);

enum class OrderListOpoWorkingPegPriceTypeEnum {
    PrimaryPeg,
    MarketPeg,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOpoWorkingPegPriceTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOpoWorkingPegPriceTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOpoWorkingPegPriceTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOpoWorkingPegPriceTypeEnum value);

enum class OrderListOpoWorkingPegOffsetTypeEnum {
    PriceLevel,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOpoWorkingPegOffsetTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOpoWorkingPegOffsetTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOpoWorkingPegOffsetTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOpoWorkingPegOffsetTypeEnum value);

enum class OrderListOpoPendingTimeInForceEnum {
    Gtc,
    Ioc,
    Fok,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOpoPendingTimeInForceEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOpoPendingTimeInForceEnum
tag_invoke(boost::json::value_to_tag<OrderListOpoPendingTimeInForceEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOpoPendingTimeInForceEnum value);

enum class OrderListOpoPendingPegPriceTypeEnum {
    PrimaryPeg,
    MarketPeg,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOpoPendingPegPriceTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOpoPendingPegPriceTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOpoPendingPegPriceTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOpoPendingPegPriceTypeEnum value);

enum class OrderListOpoPendingPegOffsetTypeEnum {
    PriceLevel,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOpoPendingPegOffsetTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOpoPendingPegOffsetTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOpoPendingPegOffsetTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOpoPendingPegOffsetTypeEnum value);

enum class OrderListOpocoWorkingTypeEnum {
    Limit,
    LimitMaker,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOpocoWorkingTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOpocoWorkingTypeEnum tag_invoke(
    boost::json::value_to_tag<OrderListOpocoWorkingTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOpocoWorkingTypeEnum value);

enum class OrderListOpocoWorkingSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOpocoWorkingSideEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOpocoWorkingSideEnum tag_invoke(
    boost::json::value_to_tag<OrderListOpocoWorkingSideEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOpocoWorkingSideEnum value);

enum class OrderListOpocoPendingSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOpocoPendingSideEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOpocoPendingSideEnum tag_invoke(
    boost::json::value_to_tag<OrderListOpocoPendingSideEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOpocoPendingSideEnum value);

enum class OrderListOpocoPendingAboveTypeEnum {
    StopLossLimit,
    StopLoss,
    LimitMaker,
    TakeProfit,
    TakeProfitLimit,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOpocoPendingAboveTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOpocoPendingAboveTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOpocoPendingAboveTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOpocoPendingAboveTypeEnum value);

enum class OrderListOpocoNewOrderRespTypeEnum {
    Ack,
    Result,
    Full,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOpocoNewOrderRespTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOpocoNewOrderRespTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOpocoNewOrderRespTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOpocoNewOrderRespTypeEnum value);

enum class OrderListOpocoSelfTradePreventionModeEnum {
    None_,
    ExpireTaker,
    ExpireMaker,
    ExpireBoth,
    Decrement,
    Transfer,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOpocoSelfTradePreventionModeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOpocoSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<OrderListOpocoSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOpocoSelfTradePreventionModeEnum value);

enum class OrderListOpocoWorkingTimeInForceEnum {
    Gtc,
    Ioc,
    Fok,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOpocoWorkingTimeInForceEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOpocoWorkingTimeInForceEnum
tag_invoke(boost::json::value_to_tag<OrderListOpocoWorkingTimeInForceEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOpocoWorkingTimeInForceEnum value);

enum class OrderListOpocoWorkingPegPriceTypeEnum {
    PrimaryPeg,
    MarketPeg,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOpocoWorkingPegPriceTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOpocoWorkingPegPriceTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOpocoWorkingPegPriceTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOpocoWorkingPegPriceTypeEnum value);

enum class OrderListOpocoWorkingPegOffsetTypeEnum {
    PriceLevel,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOpocoWorkingPegOffsetTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOpocoWorkingPegOffsetTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOpocoWorkingPegOffsetTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOpocoWorkingPegOffsetTypeEnum value);

enum class OrderListOpocoPendingAboveTimeInForceEnum {
    Gtc,
    Ioc,
    Fok,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOpocoPendingAboveTimeInForceEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOpocoPendingAboveTimeInForceEnum
tag_invoke(boost::json::value_to_tag<OrderListOpocoPendingAboveTimeInForceEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOpocoPendingAboveTimeInForceEnum value);

enum class OrderListOpocoPendingAbovePegPriceTypeEnum {
    PrimaryPeg,
    MarketPeg,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOpocoPendingAbovePegPriceTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOpocoPendingAbovePegPriceTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOpocoPendingAbovePegPriceTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOpocoPendingAbovePegPriceTypeEnum value);

enum class OrderListOpocoPendingAbovePegOffsetTypeEnum {
    PriceLevel,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOpocoPendingAbovePegOffsetTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOpocoPendingAbovePegOffsetTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOpocoPendingAbovePegOffsetTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOpocoPendingAbovePegOffsetTypeEnum value);

enum class OrderListOpocoPendingBelowTypeEnum {
    StopLoss,
    StopLossLimit,
    TakeProfit,
    TakeProfitLimit,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOpocoPendingBelowTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOpocoPendingBelowTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOpocoPendingBelowTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOpocoPendingBelowTypeEnum value);

enum class OrderListOpocoPendingBelowTimeInForceEnum {
    Gtc,
    Ioc,
    Fok,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOpocoPendingBelowTimeInForceEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOpocoPendingBelowTimeInForceEnum
tag_invoke(boost::json::value_to_tag<OrderListOpocoPendingBelowTimeInForceEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOpocoPendingBelowTimeInForceEnum value);

enum class OrderListOpocoPendingBelowPegPriceTypeEnum {
    PrimaryPeg,
    MarketPeg,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOpocoPendingBelowPegPriceTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOpocoPendingBelowPegPriceTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOpocoPendingBelowPegPriceTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOpocoPendingBelowPegPriceTypeEnum value);

enum class OrderListOpocoPendingBelowPegOffsetTypeEnum {
    PriceLevel,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOpocoPendingBelowPegOffsetTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOpocoPendingBelowPegOffsetTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOpocoPendingBelowPegOffsetTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOpocoPendingBelowPegOffsetTypeEnum value);

enum class OrderListOtoWorkingTypeEnum {
    Limit,
    LimitMaker,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOtoWorkingTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOtoWorkingTypeEnum tag_invoke(
    boost::json::value_to_tag<OrderListOtoWorkingTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOtoWorkingTypeEnum value);

enum class OrderListOtoWorkingSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOtoWorkingSideEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOtoWorkingSideEnum tag_invoke(
    boost::json::value_to_tag<OrderListOtoWorkingSideEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOtoWorkingSideEnum value);

enum class OrderListOtoPendingTypeEnum {
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

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOtoPendingTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOtoPendingTypeEnum tag_invoke(
    boost::json::value_to_tag<OrderListOtoPendingTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOtoPendingTypeEnum value);

enum class OrderListOtoPendingSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOtoPendingSideEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOtoPendingSideEnum tag_invoke(
    boost::json::value_to_tag<OrderListOtoPendingSideEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOtoPendingSideEnum value);

enum class OrderListOtoNewOrderRespTypeEnum {
    Ack,
    Result,
    Full,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOtoNewOrderRespTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOtoNewOrderRespTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOtoNewOrderRespTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOtoNewOrderRespTypeEnum value);

enum class OrderListOtoSelfTradePreventionModeEnum {
    None_,
    ExpireTaker,
    ExpireMaker,
    ExpireBoth,
    Decrement,
    Transfer,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOtoSelfTradePreventionModeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOtoSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<OrderListOtoSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOtoSelfTradePreventionModeEnum value);

enum class OrderListOtoWorkingTimeInForceEnum {
    Gtc,
    Ioc,
    Fok,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOtoWorkingTimeInForceEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOtoWorkingTimeInForceEnum
tag_invoke(boost::json::value_to_tag<OrderListOtoWorkingTimeInForceEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOtoWorkingTimeInForceEnum value);

enum class OrderListOtoWorkingPegPriceTypeEnum {
    PrimaryPeg,
    MarketPeg,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOtoWorkingPegPriceTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOtoWorkingPegPriceTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOtoWorkingPegPriceTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOtoWorkingPegPriceTypeEnum value);

enum class OrderListOtoWorkingPegOffsetTypeEnum {
    PriceLevel,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOtoWorkingPegOffsetTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOtoWorkingPegOffsetTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOtoWorkingPegOffsetTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOtoWorkingPegOffsetTypeEnum value);

enum class OrderListOtoPendingTimeInForceEnum {
    Gtc,
    Ioc,
    Fok,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOtoPendingTimeInForceEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOtoPendingTimeInForceEnum
tag_invoke(boost::json::value_to_tag<OrderListOtoPendingTimeInForceEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOtoPendingTimeInForceEnum value);

enum class OrderListOtoPendingPegPriceTypeEnum {
    PrimaryPeg,
    MarketPeg,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOtoPendingPegPriceTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOtoPendingPegPriceTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOtoPendingPegPriceTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOtoPendingPegPriceTypeEnum value);

enum class OrderListOtoPendingPegOffsetTypeEnum {
    PriceLevel,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOtoPendingPegOffsetTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOtoPendingPegOffsetTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOtoPendingPegOffsetTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOtoPendingPegOffsetTypeEnum value);

enum class OrderListOtocoWorkingTypeEnum {
    Limit,
    LimitMaker,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOtocoWorkingTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOtocoWorkingTypeEnum tag_invoke(
    boost::json::value_to_tag<OrderListOtocoWorkingTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOtocoWorkingTypeEnum value);

enum class OrderListOtocoWorkingSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOtocoWorkingSideEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOtocoWorkingSideEnum tag_invoke(
    boost::json::value_to_tag<OrderListOtocoWorkingSideEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOtocoWorkingSideEnum value);

enum class OrderListOtocoPendingSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOtocoPendingSideEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOtocoPendingSideEnum tag_invoke(
    boost::json::value_to_tag<OrderListOtocoPendingSideEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOtocoPendingSideEnum value);

enum class OrderListOtocoPendingAboveTypeEnum {
    StopLossLimit,
    StopLoss,
    LimitMaker,
    TakeProfit,
    TakeProfitLimit,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOtocoPendingAboveTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOtocoPendingAboveTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOtocoPendingAboveTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOtocoPendingAboveTypeEnum value);

enum class OrderListOtocoNewOrderRespTypeEnum {
    Ack,
    Result,
    Full,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOtocoNewOrderRespTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOtocoNewOrderRespTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOtocoNewOrderRespTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOtocoNewOrderRespTypeEnum value);

enum class OrderListOtocoSelfTradePreventionModeEnum {
    None_,
    ExpireTaker,
    ExpireMaker,
    ExpireBoth,
    Decrement,
    Transfer,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOtocoSelfTradePreventionModeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOtocoSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<OrderListOtocoSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOtocoSelfTradePreventionModeEnum value);

enum class OrderListOtocoWorkingTimeInForceEnum {
    Gtc,
    Ioc,
    Fok,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOtocoWorkingTimeInForceEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOtocoWorkingTimeInForceEnum
tag_invoke(boost::json::value_to_tag<OrderListOtocoWorkingTimeInForceEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOtocoWorkingTimeInForceEnum value);

enum class OrderListOtocoWorkingPegPriceTypeEnum {
    PrimaryPeg,
    MarketPeg,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOtocoWorkingPegPriceTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOtocoWorkingPegPriceTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOtocoWorkingPegPriceTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOtocoWorkingPegPriceTypeEnum value);

enum class OrderListOtocoWorkingPegOffsetTypeEnum {
    PriceLevel,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOtocoWorkingPegOffsetTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOtocoWorkingPegOffsetTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOtocoWorkingPegOffsetTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOtocoWorkingPegOffsetTypeEnum value);

enum class OrderListOtocoPendingAboveTimeInForceEnum {
    Gtc,
    Ioc,
    Fok,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOtocoPendingAboveTimeInForceEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOtocoPendingAboveTimeInForceEnum
tag_invoke(boost::json::value_to_tag<OrderListOtocoPendingAboveTimeInForceEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOtocoPendingAboveTimeInForceEnum value);

enum class OrderListOtocoPendingAbovePegPriceTypeEnum {
    PrimaryPeg,
    MarketPeg,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOtocoPendingAbovePegPriceTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOtocoPendingAbovePegPriceTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOtocoPendingAbovePegPriceTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOtocoPendingAbovePegPriceTypeEnum value);

enum class OrderListOtocoPendingAbovePegOffsetTypeEnum {
    PriceLevel,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOtocoPendingAbovePegOffsetTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOtocoPendingAbovePegOffsetTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOtocoPendingAbovePegOffsetTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOtocoPendingAbovePegOffsetTypeEnum value);

enum class OrderListOtocoPendingBelowTypeEnum {
    StopLoss,
    StopLossLimit,
    TakeProfit,
    TakeProfitLimit,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOtocoPendingBelowTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOtocoPendingBelowTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOtocoPendingBelowTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOtocoPendingBelowTypeEnum value);

enum class OrderListOtocoPendingBelowTimeInForceEnum {
    Gtc,
    Ioc,
    Fok,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOtocoPendingBelowTimeInForceEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOtocoPendingBelowTimeInForceEnum
tag_invoke(boost::json::value_to_tag<OrderListOtocoPendingBelowTimeInForceEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOtocoPendingBelowTimeInForceEnum value);

enum class OrderListOtocoPendingBelowPegPriceTypeEnum {
    PrimaryPeg,
    MarketPeg,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOtocoPendingBelowPegPriceTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOtocoPendingBelowPegPriceTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOtocoPendingBelowPegPriceTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOtocoPendingBelowPegPriceTypeEnum value);

enum class OrderListOtocoPendingBelowPegOffsetTypeEnum {
    PriceLevel,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListOtocoPendingBelowPegOffsetTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListOtocoPendingBelowPegOffsetTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListOtocoPendingBelowPegOffsetTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListOtocoPendingBelowPegOffsetTypeEnum value);

enum class OrderOcoSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view to_string(OrderOcoSideEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderOcoSideEnum tag_invoke(boost::json::value_to_tag<OrderOcoSideEnum> /*tag*/,
                                                const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderOcoSideEnum value);

enum class OrderOcoStopLimitTimeInForceEnum {
    Gtc,
    Ioc,
    Fok,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderOcoStopLimitTimeInForceEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderOcoStopLimitTimeInForceEnum
tag_invoke(boost::json::value_to_tag<OrderOcoStopLimitTimeInForceEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderOcoStopLimitTimeInForceEnum value);

enum class OrderOcoNewOrderRespTypeEnum {
    Ack,
    Result,
    Full,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderOcoNewOrderRespTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderOcoNewOrderRespTypeEnum tag_invoke(
    boost::json::value_to_tag<OrderOcoNewOrderRespTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderOcoNewOrderRespTypeEnum value);

enum class OrderOcoSelfTradePreventionModeEnum {
    None_,
    ExpireTaker,
    ExpireMaker,
    ExpireBoth,
    Decrement,
    Transfer,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderOcoSelfTradePreventionModeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderOcoSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<OrderOcoSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderOcoSelfTradePreventionModeEnum value);

enum class OrderTestSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view to_string(OrderTestSideEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderTestSideEnum
tag_invoke(boost::json::value_to_tag<OrderTestSideEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderTestSideEnum value);

enum class OrderTestTypeEnum {
    Market,
    Limit,
    StopLoss,
    StopLossLimit,
    TakeProfit,
    TakeProfitLimit,
    LimitMaker,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view to_string(OrderTestTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderTestTypeEnum
tag_invoke(boost::json::value_to_tag<OrderTestTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderTestTypeEnum value);

enum class OrderTestTimeInForceEnum {
    Gtc,
    Ioc,
    Fok,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderTestTimeInForceEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderTestTimeInForceEnum tag_invoke(
    boost::json::value_to_tag<OrderTestTimeInForceEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderTestTimeInForceEnum value);

enum class OrderTestNewOrderRespTypeEnum {
    Ack,
    Result,
    Full,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderTestNewOrderRespTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderTestNewOrderRespTypeEnum tag_invoke(
    boost::json::value_to_tag<OrderTestNewOrderRespTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderTestNewOrderRespTypeEnum value);

enum class OrderTestSelfTradePreventionModeEnum {
    None_,
    ExpireTaker,
    ExpireMaker,
    ExpireBoth,
    Decrement,
    Transfer,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderTestSelfTradePreventionModeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderTestSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<OrderTestSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderTestSelfTradePreventionModeEnum value);

enum class OrderTestPegPriceTypeEnum {
    PrimaryPeg,
    MarketPeg,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderTestPegPriceTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderTestPegPriceTypeEnum tag_invoke(
    boost::json::value_to_tag<OrderTestPegPriceTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderTestPegPriceTypeEnum value);

enum class OrderTestPegOffsetTypeEnum {
    PriceLevel,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderTestPegOffsetTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderTestPegOffsetTypeEnum tag_invoke(
    boost::json::value_to_tag<OrderTestPegOffsetTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderTestPegOffsetTypeEnum value);

enum class SorOrderSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view to_string(SorOrderSideEnum value) noexcept;
BINANCE_SPOT_EXPORT SorOrderSideEnum tag_invoke(boost::json::value_to_tag<SorOrderSideEnum> /*tag*/,
                                                const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    SorOrderSideEnum value);

enum class SorOrderTypeEnum {
    Market,
    Limit,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view to_string(SorOrderTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT SorOrderTypeEnum tag_invoke(boost::json::value_to_tag<SorOrderTypeEnum> /*tag*/,
                                                const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    SorOrderTypeEnum value);

enum class SorOrderTimeInForceEnum {
    Gtc,
    Ioc,
    Fok,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(SorOrderTimeInForceEnum value) noexcept;
BINANCE_SPOT_EXPORT SorOrderTimeInForceEnum tag_invoke(
    boost::json::value_to_tag<SorOrderTimeInForceEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    SorOrderTimeInForceEnum value);

enum class SorOrderNewOrderRespTypeEnum {
    Ack,
    Result,
    Full,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(SorOrderNewOrderRespTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT SorOrderNewOrderRespTypeEnum tag_invoke(
    boost::json::value_to_tag<SorOrderNewOrderRespTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    SorOrderNewOrderRespTypeEnum value);

enum class SorOrderSelfTradePreventionModeEnum {
    None_,
    ExpireTaker,
    ExpireMaker,
    ExpireBoth,
    Decrement,
    Transfer,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(SorOrderSelfTradePreventionModeEnum value) noexcept;
BINANCE_SPOT_EXPORT SorOrderSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<SorOrderSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    SorOrderSelfTradePreventionModeEnum value);

enum class SorOrderTestSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view to_string(SorOrderTestSideEnum value) noexcept;
BINANCE_SPOT_EXPORT SorOrderTestSideEnum
tag_invoke(boost::json::value_to_tag<SorOrderTestSideEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    SorOrderTestSideEnum value);

enum class SorOrderTestTypeEnum {
    Market,
    Limit,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view to_string(SorOrderTestTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT SorOrderTestTypeEnum
tag_invoke(boost::json::value_to_tag<SorOrderTestTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    SorOrderTestTypeEnum value);

enum class SorOrderTestTimeInForceEnum {
    Gtc,
    Ioc,
    Fok,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(SorOrderTestTimeInForceEnum value) noexcept;
BINANCE_SPOT_EXPORT SorOrderTestTimeInForceEnum tag_invoke(
    boost::json::value_to_tag<SorOrderTestTimeInForceEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    SorOrderTestTimeInForceEnum value);

enum class SorOrderTestNewOrderRespTypeEnum {
    Ack,
    Result,
    Full,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(SorOrderTestNewOrderRespTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT SorOrderTestNewOrderRespTypeEnum
tag_invoke(boost::json::value_to_tag<SorOrderTestNewOrderRespTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    SorOrderTestNewOrderRespTypeEnum value);

enum class SorOrderTestSelfTradePreventionModeEnum {
    None_,
    ExpireTaker,
    ExpireMaker,
    ExpireBoth,
    Decrement,
    Transfer,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(SorOrderTestSelfTradePreventionModeEnum value) noexcept;
BINANCE_SPOT_EXPORT SorOrderTestSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<SorOrderTestSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    SorOrderTestSelfTradePreventionModeEnum value);

struct DeleteOpenOrdersParams {
    common::Required<std::string> symbol;
    /// Supports up to three decimal places of precision (e.g., 6000.346) so that microseconds may
    /// be specified.
    std::optional<common::Decimal> recv_window = std::nullopt;
};

struct DeleteOrderParams {
    common::Required<std::string> symbol;
    std::optional<std::int64_t> order_id = std::nullopt;
    std::optional<std::string> orig_client_order_id = std::nullopt;
    /// Used to uniquely identify this cancel. Automatically generated by default.
    std::optional<std::string> new_client_order_id = std::nullopt;
    /// Supported values:
    /// `ONLY_NEW` - Cancel will succeed if the order status is `NEW`.
    /// `ONLY_PARTIALLY_FILLED` - Cancel will succeed if order status is `PARTIALLY_FILLED`. For
    /// more information please refer to Regarding `cancelRestrictions`.
    std::optional<DeleteOrderCancelRestrictionsEnum> cancel_restrictions = std::nullopt;
    /// Supports up to three decimal places of precision (e.g., 6000.346) so that microseconds may
    /// be specified.
    std::optional<common::Decimal> recv_window = std::nullopt;
};

struct NewOrderParams {
    common::Required<std::string> symbol;
    common::Required<NewOrderSideEnum> side;
    common::Required<NewOrderTypeEnum> type;
    std::optional<NewOrderTimeInForceEnum> time_in_force = std::nullopt;
    std::optional<common::Decimal> quantity = std::nullopt;
    std::optional<common::Decimal> quote_order_qty = std::nullopt;
    std::optional<common::Decimal> price = std::nullopt;
    /// A unique id among open orders. Automatically generated if not sent.
    /// Orders with the same `newClientOrderID` can be accepted only when the previous one is
    /// filled, otherwise the order will be rejected.
    std::optional<std::string> new_client_order_id = std::nullopt;
    std::optional<std::int64_t> strategy_id = std::nullopt;
    /// The value cannot be less than `1000000`.
    std::optional<std::int64_t> strategy_type = std::nullopt;
    /// Used with `STOP_LOSS`, `STOP_LOSS_LIMIT`, `TAKE_PROFIT`, and `TAKE_PROFIT_LIMIT` orders.
    std::optional<common::Decimal> stop_price = std::nullopt;
    /// See Trailing Stop order FAQ
    std::optional<std::int64_t> trailing_delta = std::nullopt;
    /// Used with `LIMIT`, `STOP_LOSS_LIMIT`, and `TAKE_PROFIT_LIMIT` to create an iceberg order.
    std::optional<common::Decimal> iceberg_qty = std::nullopt;
    /// `MARKET` and `LIMIT` order types default to `FULL`, all other orders default to `ACK`.
    std::optional<NewOrderNewOrderRespTypeEnum> new_order_resp_type = std::nullopt;
    /// The allowed enums is dependent on what is configured on the symbol.
    std::optional<NewOrderSelfTradePreventionModeEnum> self_trade_prevention_mode = std::nullopt;
    /// See Pegged Orders Info
    std::optional<NewOrderPegPriceTypeEnum> peg_price_type = std::nullopt;
    /// Price level to peg the price to (max: 100). See Pegged Orders Info
    std::optional<std::int64_t> peg_offset_value = std::nullopt;
    /// Only `PRICE_LEVEL` is supported. See Pegged Orders Info
    std::optional<NewOrderPegOffsetTypeEnum> peg_offset_type = std::nullopt;
    /// For orders on the BUY side only. Maximum quote-asset notional the order may consume. See
    /// Quote Notional Limit.
    std::optional<common::Decimal> quote_notional_limit = std::nullopt;
    /// Supports up to three decimal places of precision (e.g., 6000.346) so that microseconds may
    /// be specified.
    std::optional<common::Decimal> recv_window = std::nullopt;
};

struct DeleteOrderListParams {
    common::Required<std::string> symbol;
    /// Either `orderListId` or `listClientOrderId` must be provided
    std::optional<std::int64_t> order_list_id = std::nullopt;
    /// Either `orderListId` or `listClientOrderId` must be provided
    std::optional<std::string> list_client_order_id = std::nullopt;
    /// Used to uniquely identify this cancel. Automatically generated by default.
    std::optional<std::string> new_client_order_id = std::nullopt;
    /// Supports up to three decimal places of precision (e.g., 6000.346) so that microseconds may
    /// be specified.
    std::optional<common::Decimal> recv_window = std::nullopt;
};

struct OrderAmendKeepPriorityParams {
    common::Required<std::string> symbol;
    /// `newQty` must be greater than 0 and less than the order's quantity.
    common::Required<common::Decimal> new_qty;
    /// `orderId` or `origClientOrderId` must be sent
    std::optional<std::int64_t> order_id = std::nullopt;
    /// `orderId` or `origClientOrderId` must be sent
    std::optional<std::string> orig_client_order_id = std::nullopt;
    /// The new client order ID for the order after being amended.
    /// If not sent, one will be randomly generated.
    /// It is possible to reuse the current clientOrderId by sending it as the `newClientOrderId`.
    std::optional<std::string> new_client_order_id = std::nullopt;
    /// The value cannot be greater than `60000`.
    /// Supports up to three decimal places of precision (e.g., 6000.346) so that microseconds may
    /// be specified.
    std::optional<common::Decimal> recv_window = std::nullopt;
};

struct OrderCancelReplaceParams {
    common::Required<std::string> symbol;
    common::Required<OrderCancelReplaceSideEnum> side;
    common::Required<OrderCancelReplaceTypeEnum> type;
    /// The allowed values are:
    /// `STOP_ON_FAILURE` - If the cancel request fails, the new order placement will not be
    /// attempted. `ALLOW_FAILURE` - new order placement will be attempted even if cancel request
    /// fails.
    common::Required<OrderCancelReplaceCancelReplaceModeEnum> cancel_replace_mode;
    std::optional<OrderCancelReplaceTimeInForceEnum> time_in_force = std::nullopt;
    std::optional<common::Decimal> quantity = std::nullopt;
    std::optional<common::Decimal> quote_order_qty = std::nullopt;
    std::optional<common::Decimal> price = std::nullopt;
    /// Used to uniquely identify this cancel. Automatically generated by default.
    std::optional<std::string> cancel_new_client_order_id = std::nullopt;
    /// Either `cancelOrderId` or `cancelOrigClientOrderId` must be sent.
    ///
    /// If both `cancelOrderId` and `cancelOrigClientOrderId` parameters are provided, the
    /// `cancelOrderId` is searched first, then the `cancelOrigClientOrderId` from that result is
    /// checked against that order.
    ///
    /// If both conditions are not met the request will be rejected.
    std::optional<std::string> cancel_orig_client_order_id = std::nullopt;
    /// Either `cancelOrderId` or `cancelOrigClientOrderId` must be sent.
    ///
    /// If both `cancelOrderId` and `cancelOrigClientOrderId` parameters are provided, the
    /// `cancelOrderId` is searched first, then the `cancelOrigClientOrderId` from that result is
    /// checked against that order.
    ///
    /// If both conditions are not met the request will be rejected.
    std::optional<std::int64_t> cancel_order_id = std::nullopt;
    /// Used to identify the new order.
    std::optional<std::string> new_client_order_id = std::nullopt;
    std::optional<std::int64_t> strategy_id = std::nullopt;
    /// The value cannot be less than `1000000`.
    std::optional<std::int64_t> strategy_type = std::nullopt;
    std::optional<common::Decimal> stop_price = std::nullopt;
    /// See Trailing Stop order FAQ
    std::optional<std::int64_t> trailing_delta = std::nullopt;
    std::optional<common::Decimal> iceberg_qty = std::nullopt;
    /// Allowed values:
    /// `ACK`, `RESULT`, `FULL`
    /// `MARKET` and `LIMIT` orders types default to `FULL`; all other orders default to `ACK`
    std::optional<OrderCancelReplaceNewOrderRespTypeEnum> new_order_resp_type = std::nullopt;
    /// The allowed enums is dependent on what is configured on the symbol. The possible supported
    /// values are: STP Modes.
    std::optional<OrderCancelReplaceSelfTradePreventionModeEnum> self_trade_prevention_mode =
        std::nullopt;
    /// Supported values:
    /// `ONLY_NEW` - Cancel will succeed if the order status is `NEW`.
    /// `ONLY_PARTIALLY_FILLED ` - Cancel will succeed if order status is `PARTIALLY_FILLED`. For
    /// more information please refer to Regarding `cancelRestrictions`.
    std::optional<OrderCancelReplaceCancelRestrictionsEnum> cancel_restrictions = std::nullopt;
    /// Supported values:
    /// `DO_NOTHING` (default)- will only attempt to cancel the order if account has not exceeded
    /// the unfilled order rate limit `CANCEL_ONLY` - will always cancel the order
    std::optional<OrderCancelReplaceOrderRateLimitExceededModeEnum> order_rate_limit_exceeded_mode =
        std::nullopt;
    /// `PRIMARY_PEG` or `MARKET_PEG`
    /// See Pegged Orders
    std::optional<OrderCancelReplacePegPriceTypeEnum> peg_price_type = std::nullopt;
    /// Price level to peg the price to (max: 100)
    /// See Pegged Orders
    std::optional<std::int64_t> peg_offset_value = std::nullopt;
    /// Only `PRICE_LEVEL` is supported
    /// See Pegged Orders.
    std::optional<OrderCancelReplacePegOffsetTypeEnum> peg_offset_type = std::nullopt;
    /// For replacement orders on the BUY side only. Maximum quote-asset notional the replacement
    /// order may consume. See Quote Notional Limit.
    std::optional<common::Decimal> quote_notional_limit = std::nullopt;
    /// Supports up to three decimal places of precision (e.g., 6000.346) so that microseconds may
    /// be specified.
    std::optional<common::Decimal> recv_window = std::nullopt;
};

struct OrderListOcoParams {
    common::Required<std::string> symbol;
    common::Required<OrderListOcoSideEnum> side;
    /// Quantity for both orders of the order list.
    common::Required<common::Decimal> quantity;
    common::Required<OrderListOcoAboveTypeEnum> above_type;
    /// Supported values: `STOP_LOSS`, `STOP_LOSS_LIMIT`, `TAKE_PROFIT`, `TAKE_PROFIT_LIMIT`
    common::Required<OrderListOcoBelowTypeEnum> below_type;
    /// Arbitrary unique ID among open order lists. Automatically generated if not sent. A new order
    /// list with the same `listClientOrderId` is accepted only when the previous one is filled or
    /// completely expired. `listClientOrderId` is distinct from the `aboveClientOrderId` and the
    /// `belowClientOrderId`.
    std::optional<std::string> list_client_order_id = std::nullopt;
    /// Arbitrary unique ID among open orders for the above order. Automatically generated if not
    /// sent.
    std::optional<std::string> above_client_order_id = std::nullopt;
    /// Note that this can only be used if `aboveTimeInForce` is `GTC`.
    std::optional<common::Decimal> above_iceberg_qty = std::nullopt;
    /// Can be used if `aboveType` is `STOP_LOSS_LIMIT`, `LIMIT_MAKER`, or `TAKE_PROFIT_LIMIT` to
    /// specify the limit price.
    std::optional<common::Decimal> above_price = std::nullopt;
    /// Can be used if `aboveType` is `STOP_LOSS`, `STOP_LOSS_LIMIT`, `TAKE_PROFIT`,
    /// `TAKE_PROFIT_LIMIT`. Either `aboveStopPrice` or `aboveTrailingDelta` or both, must be
    /// specified.
    std::optional<common::Decimal> above_stop_price = std::nullopt;
    /// See Trailing Stop order FAQ
    std::optional<std::int64_t> above_trailing_delta = std::nullopt;
    /// Required if `aboveType` is `STOP_LOSS_LIMIT` or `TAKE_PROFIT_LIMIT`.
    std::optional<OrderListOcoAboveTimeInForceEnum> above_time_in_force = std::nullopt;
    /// Arbitrary numeric value identifying the above order within an order strategy.
    std::optional<std::int64_t> above_strategy_id = std::nullopt;
    /// Arbitrary numeric value identifying the above order strategy. Values smaller than `1000000`
    /// are reserved and cannot be used.
    std::optional<std::int64_t> above_strategy_type = std::nullopt;
    /// `PRIMARY_PEG` or `MARKET_PEG`. See Pegged Orders
    std::optional<OrderListOcoAbovePegPriceTypeEnum> above_peg_price_type = std::nullopt;
    std::optional<OrderListOcoAbovePegOffsetTypeEnum> above_peg_offset_type = std::nullopt;
    std::optional<std::int64_t> above_peg_offset_value = std::nullopt;
    /// Arbitrary unique ID among open orders for the below order. Automatically generated if not
    /// sent.
    std::optional<std::string> below_client_order_id = std::nullopt;
    /// Note that this can only be used if `belowTimeInForce` is `GTC`.
    std::optional<common::Decimal> below_iceberg_qty = std::nullopt;
    /// Can be used if `belowType` is `STOP_LOSS_LIMIT`, `LIMIT_MAKER`, or `TAKE_PROFIT_LIMIT` to
    /// specify the limit price.
    std::optional<common::Decimal> below_price = std::nullopt;
    /// Can be used if `belowType` is `STOP_LOSS`, `STOP_LOSS_LIMIT`, `TAKE_PROFIT`,
    /// `TAKE_PROFIT_LIMIT`. Either `belowStopPrice` or `belowTrailingDelta` or both, must be
    /// specified.
    std::optional<common::Decimal> below_stop_price = std::nullopt;
    /// See Trailing Stop order FAQ
    std::optional<std::int64_t> below_trailing_delta = std::nullopt;
    /// Required if `belowType` is `STOP_LOSS_LIMIT` or `TAKE_PROFIT_LIMIT`.
    std::optional<OrderListOcoBelowTimeInForceEnum> below_time_in_force = std::nullopt;
    /// Arbitrary numeric value identifying the below order within an order strategy.
    std::optional<std::int64_t> below_strategy_id = std::nullopt;
    /// Arbitrary numeric value identifying the below order strategy. Values smaller than `1000000`
    /// are reserved and cannot be used.
    std::optional<std::int64_t> below_strategy_type = std::nullopt;
    /// See Pegged Orders
    std::optional<OrderListOcoBelowPegPriceTypeEnum> below_peg_price_type = std::nullopt;
    std::optional<OrderListOcoBelowPegOffsetTypeEnum> below_peg_offset_type = std::nullopt;
    std::optional<std::int64_t> below_peg_offset_value = std::nullopt;
    /// Select response format: `ACK`, `RESULT`, `FULL`.
    std::optional<OrderListOcoNewOrderRespTypeEnum> new_order_resp_type = std::nullopt;
    /// The allowed enums is dependent on what is configured on the symbol. Supported values: STP
    /// Modes
    std::optional<OrderListOcoSelfTradePreventionModeEnum> self_trade_prevention_mode =
        std::nullopt;
    /// Quote notional limit for the above order (only for orders on the BUY side). See Quote
    /// Notional Limit.
    std::optional<common::Decimal> above_quote_notional_limit = std::nullopt;
    /// Quote notional limit for the below order (only for orders on the BUY side). See Quote
    /// Notional Limit.
    std::optional<common::Decimal> below_quote_notional_limit = std::nullopt;
    /// The value cannot be greater than `60000`. Supports up to three decimal places of precision
    /// (e.g., 6000.346) so that microseconds may be specified.
    std::optional<common::Decimal> recv_window = std::nullopt;
};

struct OrderListOpoParams {
    common::Required<std::string> symbol;
    /// Supported values: `LIMIT`, `LIMIT_MAKER`
    common::Required<OrderListOpoWorkingTypeEnum> working_type;
    /// Supported values: Order Side
    common::Required<OrderListOpoWorkingSideEnum> working_side;
    /// Price for the working order.
    common::Required<common::Decimal> working_price;
    /// Sets the quantity for the working order.
    common::Required<common::Decimal> working_quantity;
    /// Supported values: Order Types. Note that `MARKET` orders using `quoteOrderQty` are not
    /// supported.
    common::Required<OrderListOpoPendingTypeEnum> pending_type;
    /// Supported values: Order Side
    common::Required<OrderListOpoPendingSideEnum> pending_side;
    /// Arbitrary unique ID among open order lists. Automatically generated if not sent. A new order
    /// list with the same `listClientOrderId` is accepted only when the previous one is filled or
    /// completely expired. `listClientOrderId` is distinct from the `workingClientOrderId` and the
    /// `pendingClientOrderId`.
    std::optional<std::string> list_client_order_id = std::nullopt;
    /// Format of the JSON response. Supported values: Order Response Type
    std::optional<OrderListOpoNewOrderRespTypeEnum> new_order_resp_type = std::nullopt;
    /// The allowed enums is dependent on what is configured on the symbol. Supported values: STP
    /// Modes
    std::optional<OrderListOpoSelfTradePreventionModeEnum> self_trade_prevention_mode =
        std::nullopt;
    /// Arbitrary unique ID among open orders for the working order. Automatically generated if not
    /// sent.
    std::optional<std::string> working_client_order_id = std::nullopt;
    /// This can only be used if `workingTimeInForce` is `GTC`, or if `workingType` is
    /// `LIMIT_MAKER`.
    std::optional<common::Decimal> working_iceberg_qty = std::nullopt;
    /// Supported values: Time In Force
    std::optional<OrderListOpoWorkingTimeInForceEnum> working_time_in_force = std::nullopt;
    /// Arbitrary numeric value identifying the working order within an order strategy.
    std::optional<std::int64_t> working_strategy_id = std::nullopt;
    /// Arbitrary numeric value identifying the working order strategy. Values smaller than
    /// `1000000` are reserved and cannot be used.
    std::optional<std::int64_t> working_strategy_type = std::nullopt;
    /// See Pegged Orders
    std::optional<OrderListOpoWorkingPegPriceTypeEnum> working_peg_price_type = std::nullopt;
    std::optional<OrderListOpoWorkingPegOffsetTypeEnum> working_peg_offset_type = std::nullopt;
    std::optional<std::int64_t> working_peg_offset_value = std::nullopt;
    /// Arbitrary unique ID among open orders for the pending order. Automatically generated if not
    /// sent.
    std::optional<std::string> pending_client_order_id = std::nullopt;
    /// Price for the pending order.
    std::optional<common::Decimal> pending_price = std::nullopt;
    /// Stop price for the pending order.
    std::optional<common::Decimal> pending_stop_price = std::nullopt;
    /// Trailing delta for the pending order.
    std::optional<common::Decimal> pending_trailing_delta = std::nullopt;
    /// This can only be used if `pendingTimeInForce` is `GTC` or if `pendingType` is `LIMIT_MAKER`.
    std::optional<common::Decimal> pending_iceberg_qty = std::nullopt;
    /// Supported values: Time In Force
    std::optional<OrderListOpoPendingTimeInForceEnum> pending_time_in_force = std::nullopt;
    /// Arbitrary numeric value identifying the pending order within an order strategy.
    std::optional<std::int64_t> pending_strategy_id = std::nullopt;
    /// Arbitrary numeric value identifying the pending order strategy. Values smaller than
    /// `1000000` are reserved and cannot be used.
    std::optional<std::int64_t> pending_strategy_type = std::nullopt;
    /// See Pegged Orders
    std::optional<OrderListOpoPendingPegPriceTypeEnum> pending_peg_price_type = std::nullopt;
    std::optional<OrderListOpoPendingPegOffsetTypeEnum> pending_peg_offset_type = std::nullopt;
    std::optional<std::int64_t> pending_peg_offset_value = std::nullopt;
    /// Quote notional limit for the working LIMIT order on the BUY side. See Quote Notional Limit.
    std::optional<common::Decimal> working_quote_notional_limit = std::nullopt;
    /// Supports up to three decimal places of precision (e.g., 6000.346) so that microseconds may
    /// be specified.
    std::optional<common::Decimal> recv_window = std::nullopt;
};

struct OrderListOpocoParams {
    common::Required<std::string> symbol;
    /// Supported values: `LIMIT`, `LIMIT_MAKER`
    common::Required<OrderListOpocoWorkingTypeEnum> working_type;
    /// Supported values: Order Side
    common::Required<OrderListOpocoWorkingSideEnum> working_side;
    /// Price for the working order.
    common::Required<common::Decimal> working_price;
    /// Sets the quantity for the working order.
    common::Required<common::Decimal> working_quantity;
    /// Supported values: Order Side
    common::Required<OrderListOpocoPendingSideEnum> pending_side;
    /// Supported values: `STOP_LOSS_LIMIT`, `STOP_LOSS`, `LIMIT_MAKER`, `TAKE_PROFIT`,
    /// `TAKE_PROFIT_LIMIT`
    common::Required<OrderListOpocoPendingAboveTypeEnum> pending_above_type;
    /// Arbitrary unique ID among open order lists. Automatically generated if not sent. A new order
    /// list with the same `listClientOrderId` is accepted only when the previous one is filled or
    /// completely expired. `listClientOrderId` is distinct from the `workingClientOrderId`,
    /// `pendingAboveClientOrderId`, and the `pendingBelowClientOrderId`.
    std::optional<std::string> list_client_order_id = std::nullopt;
    /// Format of the JSON response. Supported values: Order Response Type
    std::optional<OrderListOpocoNewOrderRespTypeEnum> new_order_resp_type = std::nullopt;
    /// The allowed enums is dependent on what is configured on the symbol. Supported values: STP
    /// Modes
    std::optional<OrderListOpocoSelfTradePreventionModeEnum> self_trade_prevention_mode =
        std::nullopt;
    /// Arbitrary unique ID among open orders for the working order. Automatically generated if not
    /// sent.
    std::optional<std::string> working_client_order_id = std::nullopt;
    /// This can only be used if `workingTimeInForce` is `GTC`, or if `workingType` is
    /// `LIMIT_MAKER`.
    std::optional<common::Decimal> working_iceberg_qty = std::nullopt;
    /// Supported values: Time In Force
    std::optional<OrderListOpocoWorkingTimeInForceEnum> working_time_in_force = std::nullopt;
    /// Arbitrary numeric value identifying the working order within an order strategy.
    std::optional<std::int64_t> working_strategy_id = std::nullopt;
    /// Arbitrary numeric value identifying the working order strategy. Values smaller than
    /// `1000000` are reserved and cannot be used.
    std::optional<std::int64_t> working_strategy_type = std::nullopt;
    /// See Pegged Orders
    std::optional<OrderListOpocoWorkingPegPriceTypeEnum> working_peg_price_type = std::nullopt;
    /// See Pegged Orders
    std::optional<OrderListOpocoWorkingPegOffsetTypeEnum> working_peg_offset_type = std::nullopt;
    /// Price level for pegging (max: 100). See Pegged Orders
    std::optional<std::int64_t> working_peg_offset_value = std::nullopt;
    /// Arbitrary unique ID among open orders for the pending above order. Automatically generated
    /// if not sent.
    std::optional<std::string> pending_above_client_order_id = std::nullopt;
    /// Can be used if `pendingAboveType` is `STOP_LOSS_LIMIT`, `LIMIT_MAKER`, or
    /// `TAKE_PROFIT_LIMIT` to specify the limit price.
    std::optional<common::Decimal> pending_above_price = std::nullopt;
    /// Can be used if `pendingAboveType` is `STOP_LOSS`, `STOP_LOSS_LIMIT`, `TAKE_PROFIT`,
    /// `TAKE_PROFIT_LIMIT`.
    std::optional<common::Decimal> pending_above_stop_price = std::nullopt;
    /// See Trailing Stop order FAQ
    std::optional<common::Decimal> pending_above_trailing_delta = std::nullopt;
    /// This can only be used if `pendingAboveTimeInForce` is `GTC` or `pendingAboveType` is
    /// `LIMIT_MAKER`.
    std::optional<common::Decimal> pending_above_iceberg_qty = std::nullopt;
    /// Required if `pendingAboveType` is `STOP_LOSS_LIMIT` or `TAKE_PROFIT_LIMIT`.
    std::optional<OrderListOpocoPendingAboveTimeInForceEnum> pending_above_time_in_force =
        std::nullopt;
    /// Arbitrary numeric value identifying the pending above order within an order strategy.
    std::optional<std::int64_t> pending_above_strategy_id = std::nullopt;
    /// Arbitrary numeric value identifying the pending above order strategy. Values smaller than
    /// `1000000` are reserved and cannot be used.
    std::optional<std::int64_t> pending_above_strategy_type = std::nullopt;
    /// See Pegged Orders
    std::optional<OrderListOpocoPendingAbovePegPriceTypeEnum> pending_above_peg_price_type =
        std::nullopt;
    /// See Pegged Orders
    std::optional<OrderListOpocoPendingAbovePegOffsetTypeEnum> pending_above_peg_offset_type =
        std::nullopt;
    /// Price level for pegging (max: 100). See Pegged Orders
    std::optional<std::int64_t> pending_above_peg_offset_value = std::nullopt;
    /// Supported values: `STOP_LOSS`, `STOP_LOSS_LIMIT`, `TAKE_PROFIT`, `TAKE_PROFIT_LIMIT`
    std::optional<OrderListOpocoPendingBelowTypeEnum> pending_below_type = std::nullopt;
    /// Arbitrary unique ID among open orders for the pending below order. Automatically generated
    /// if not sent.
    std::optional<std::string> pending_below_client_order_id = std::nullopt;
    /// Can be used if `pendingBelowType` is `STOP_LOSS_LIMIT` or `TAKE_PROFIT_LIMIT` to specify the
    /// limit price.
    std::optional<common::Decimal> pending_below_price = std::nullopt;
    /// Can be used if `pendingBelowType` is `STOP_LOSS`, `STOP_LOSS_LIMIT`, `TAKE_PROFIT`,
    /// `TAKE_PROFIT_LIMIT`. Either `pendingBelowStopPrice` or `pendingBelowTrailingDelta` or both,
    /// must be specified.
    std::optional<common::Decimal> pending_below_stop_price = std::nullopt;
    /// See Trailing Stop order FAQ
    std::optional<common::Decimal> pending_below_trailing_delta = std::nullopt;
    /// This can only be used if `pendingBelowTimeInForce` is `GTC` or `pendingBelowType` is
    /// `LIMIT_MAKER`.
    std::optional<common::Decimal> pending_below_iceberg_qty = std::nullopt;
    /// Supported values: Time In Force
    std::optional<OrderListOpocoPendingBelowTimeInForceEnum> pending_below_time_in_force =
        std::nullopt;
    /// Arbitrary numeric value identifying the pending below order within an order strategy.
    std::optional<std::int64_t> pending_below_strategy_id = std::nullopt;
    /// Arbitrary numeric value identifying the pending below order strategy. Values smaller than
    /// `1000000` are reserved and cannot be used.
    std::optional<std::int64_t> pending_below_strategy_type = std::nullopt;
    /// See Pegged Orders
    std::optional<OrderListOpocoPendingBelowPegPriceTypeEnum> pending_below_peg_price_type =
        std::nullopt;
    std::optional<OrderListOpocoPendingBelowPegOffsetTypeEnum> pending_below_peg_offset_type =
        std::nullopt;
    std::optional<std::int64_t> pending_below_peg_offset_value = std::nullopt;
    /// Quote notional limit for the working LIMIT order on the BUY side. See Quote Notional Limit.
    std::optional<common::Decimal> working_quote_notional_limit = std::nullopt;
    /// The value cannot be greater than `60000`. Supports up to three decimal places of precision
    /// (e.g., 6000.346) so that microseconds may be specified.
    std::optional<common::Decimal> recv_window = std::nullopt;
};

struct OrderListOtoParams {
    common::Required<std::string> symbol;
    /// Supported values: `LIMIT`, `LIMIT_MAKER`
    common::Required<OrderListOtoWorkingTypeEnum> working_type;
    /// Supported values: Order Side
    common::Required<OrderListOtoWorkingSideEnum> working_side;
    common::Required<common::Decimal> working_price;
    /// Sets the quantity for the working order.
    common::Required<common::Decimal> working_quantity;
    /// Supported values: Order Types. Note that `MARKET` orders using `quoteOrderQty` are not
    /// supported.
    common::Required<OrderListOtoPendingTypeEnum> pending_type;
    /// Supported values: Order Side
    common::Required<OrderListOtoPendingSideEnum> pending_side;
    /// Sets the quantity for the pending order.
    common::Required<common::Decimal> pending_quantity;
    /// Arbitrary unique ID among open order lists. Automatically generated if not sent. A new order
    /// list with the same `listClientOrderId` is accepted only when the previous one is filled or
    /// completely expired. `listClientOrderId` is distinct from the `workingClientOrderId` and the
    /// `pendingClientOrderId`.
    std::optional<std::string> list_client_order_id = std::nullopt;
    /// Format of the JSON response. Supported values: Order Response Type
    std::optional<OrderListOtoNewOrderRespTypeEnum> new_order_resp_type = std::nullopt;
    /// The allowed enums is dependent on what is configured on the symbol. Supported values: STP
    /// Modes
    std::optional<OrderListOtoSelfTradePreventionModeEnum> self_trade_prevention_mode =
        std::nullopt;
    /// Arbitrary unique ID among open orders for the working order. Automatically generated if not
    /// sent.
    std::optional<std::string> working_client_order_id = std::nullopt;
    /// This can only be used if `workingTimeInForce` is `GTC`, or if `workingType` is
    /// `LIMIT_MAKER`.
    std::optional<common::Decimal> working_iceberg_qty = std::nullopt;
    /// Supported values: Time In Force
    std::optional<OrderListOtoWorkingTimeInForceEnum> working_time_in_force = std::nullopt;
    /// Arbitrary numeric value identifying the working order within an order strategy.
    std::optional<std::int64_t> working_strategy_id = std::nullopt;
    /// Arbitrary numeric value identifying the working order strategy. Values smaller than
    /// `1000000` are reserved and cannot be used.
    std::optional<std::int64_t> working_strategy_type = std::nullopt;
    /// See Pegged Orders
    std::optional<OrderListOtoWorkingPegPriceTypeEnum> working_peg_price_type = std::nullopt;
    std::optional<OrderListOtoWorkingPegOffsetTypeEnum> working_peg_offset_type = std::nullopt;
    std::optional<std::int64_t> working_peg_offset_value = std::nullopt;
    /// Arbitrary unique ID among open orders for the pending order. Automatically generated if not
    /// sent.
    std::optional<std::string> pending_client_order_id = std::nullopt;
    std::optional<common::Decimal> pending_price = std::nullopt;
    std::optional<common::Decimal> pending_stop_price = std::nullopt;
    std::optional<common::Decimal> pending_trailing_delta = std::nullopt;
    /// This can only be used if `pendingTimeInForce` is `GTC` or if `pendingType` is `LIMIT_MAKER`.
    std::optional<common::Decimal> pending_iceberg_qty = std::nullopt;
    /// Supported values: Time In Force
    std::optional<OrderListOtoPendingTimeInForceEnum> pending_time_in_force = std::nullopt;
    /// Arbitrary numeric value identifying the pending order within an order strategy.
    std::optional<std::int64_t> pending_strategy_id = std::nullopt;
    /// Arbitrary numeric value identifying the pending order strategy. Values smaller than
    /// `1000000` are reserved and cannot be used.
    std::optional<std::int64_t> pending_strategy_type = std::nullopt;
    /// See Pegged Orders
    std::optional<OrderListOtoPendingPegPriceTypeEnum> pending_peg_price_type = std::nullopt;
    std::optional<OrderListOtoPendingPegOffsetTypeEnum> pending_peg_offset_type = std::nullopt;
    std::optional<std::int64_t> pending_peg_offset_value = std::nullopt;
    /// Quote notional limit for the working order (only for orders on the BUY side). See Quote
    /// Notional Limit.
    std::optional<common::Decimal> working_quote_notional_limit = std::nullopt;
    /// Quote notional limit for the pending order (only for orders on the BUY side). See Quote
    /// Notional Limit.
    std::optional<common::Decimal> pending_quote_notional_limit = std::nullopt;
    /// The value cannot be greater than `60000`. Supports up to three decimal places of precision
    /// (e.g., 6000.346) so that microseconds may be specified.
    std::optional<common::Decimal> recv_window = std::nullopt;
};

struct OrderListOtocoParams {
    common::Required<std::string> symbol;
    /// Supported values: `LIMIT`, `LIMIT_MAKER`
    common::Required<OrderListOtocoWorkingTypeEnum> working_type;
    /// Supported values: Order Side
    common::Required<OrderListOtocoWorkingSideEnum> working_side;
    common::Required<common::Decimal> working_price;
    /// Sets the quantity for the working order.
    common::Required<common::Decimal> working_quantity;
    /// Supported values: Order Side
    common::Required<OrderListOtocoPendingSideEnum> pending_side;
    /// Sets the quantity for the pending orders.
    common::Required<common::Decimal> pending_quantity;
    /// Supported values: `STOP_LOSS_LIMIT`, `STOP_LOSS`, `LIMIT_MAKER`, `TAKE_PROFIT`,
    /// `TAKE_PROFIT_LIMIT`
    common::Required<OrderListOtocoPendingAboveTypeEnum> pending_above_type;
    /// Arbitrary unique ID among open order lists. Automatically generated if not sent. A new order
    /// list with the same `listClientOrderId` is accepted only when the previous one is filled or
    /// completely expired. `listClientOrderId` is distinct from the `workingClientOrderId`,
    /// `pendingAboveClientOrderId`, and the `pendingBelowClientOrderId`.
    std::optional<std::string> list_client_order_id = std::nullopt;
    /// Format of the JSON response. Supported values: Order Response Type
    std::optional<OrderListOtocoNewOrderRespTypeEnum> new_order_resp_type = std::nullopt;
    /// The allowed enums is dependent on what is configured on the symbol. Supported values: STP
    /// Modes
    std::optional<OrderListOtocoSelfTradePreventionModeEnum> self_trade_prevention_mode =
        std::nullopt;
    /// Arbitrary unique ID among open orders for the working order. Automatically generated if not
    /// sent.
    std::optional<std::string> working_client_order_id = std::nullopt;
    /// This can only be used if `workingTimeInForce` is `GTC`, or if `workingType` is
    /// `LIMIT_MAKER`.
    std::optional<common::Decimal> working_iceberg_qty = std::nullopt;
    /// Supported values: Time In Force
    std::optional<OrderListOtocoWorkingTimeInForceEnum> working_time_in_force = std::nullopt;
    /// Arbitrary numeric value identifying the working order within an order strategy.
    std::optional<std::int64_t> working_strategy_id = std::nullopt;
    /// Arbitrary numeric value identifying the working order strategy. Values smaller than
    /// `1000000` are reserved and cannot be used.
    std::optional<std::int64_t> working_strategy_type = std::nullopt;
    /// See Pegged Orders
    std::optional<OrderListOtocoWorkingPegPriceTypeEnum> working_peg_price_type = std::nullopt;
    std::optional<OrderListOtocoWorkingPegOffsetTypeEnum> working_peg_offset_type = std::nullopt;
    std::optional<std::int64_t> working_peg_offset_value = std::nullopt;
    /// Arbitrary unique ID among open orders for the pending above order. Automatically generated
    /// if not sent.
    std::optional<std::string> pending_above_client_order_id = std::nullopt;
    /// Can be used if `pendingAboveType` is `STOP_LOSS_LIMIT`, `LIMIT_MAKER`, or
    /// `TAKE_PROFIT_LIMIT` to specify the limit price.
    std::optional<common::Decimal> pending_above_price = std::nullopt;
    /// Can be used if `pendingAboveType` is `STOP_LOSS`, `STOP_LOSS_LIMIT`, `TAKE_PROFIT`,
    /// `TAKE_PROFIT_LIMIT`.
    std::optional<common::Decimal> pending_above_stop_price = std::nullopt;
    /// See Trailing Stop order FAQ
    std::optional<common::Decimal> pending_above_trailing_delta = std::nullopt;
    /// This can only be used if `pendingAboveTimeInForce` is `GTC` or if `pendingAboveType` is
    /// `LIMIT_MAKER`.
    std::optional<common::Decimal> pending_above_iceberg_qty = std::nullopt;
    /// Required if `pendingAboveType` is `STOP_LOSS_LIMIT` or `TAKE_PROFIT_LIMIT`.
    std::optional<OrderListOtocoPendingAboveTimeInForceEnum> pending_above_time_in_force =
        std::nullopt;
    /// Arbitrary numeric value identifying the pending above order within an order strategy.
    std::optional<std::int64_t> pending_above_strategy_id = std::nullopt;
    /// Arbitrary numeric value identifying the pending above order strategy. Values smaller than
    /// `1000000` are reserved and cannot be used.
    std::optional<std::int64_t> pending_above_strategy_type = std::nullopt;
    /// See Pegged Orders
    std::optional<OrderListOtocoPendingAbovePegPriceTypeEnum> pending_above_peg_price_type =
        std::nullopt;
    std::optional<OrderListOtocoPendingAbovePegOffsetTypeEnum> pending_above_peg_offset_type =
        std::nullopt;
    std::optional<std::int64_t> pending_above_peg_offset_value = std::nullopt;
    /// Supported values: `STOP_LOSS`, `STOP_LOSS_LIMIT`, `TAKE_PROFIT`, `TAKE_PROFIT_LIMIT`
    std::optional<OrderListOtocoPendingBelowTypeEnum> pending_below_type = std::nullopt;
    /// Arbitrary unique ID among open orders for the pending below order. Automatically generated
    /// if not sent.
    std::optional<std::string> pending_below_client_order_id = std::nullopt;
    /// Can be used if `pendingBelowType` is `STOP_LOSS_LIMIT` or `TAKE_PROFIT_LIMIT` to specify the
    /// limit price.
    std::optional<common::Decimal> pending_below_price = std::nullopt;
    /// Can be used if `pendingBelowType` is `STOP_LOSS`, `STOP_LOSS_LIMIT`, `TAKE_PROFIT`,
    /// `TAKE_PROFIT_LIMIT`. Either `pendingBelowStopPrice` or `pendingBelowTrailingDelta` or both,
    /// must be specified.
    std::optional<common::Decimal> pending_below_stop_price = std::nullopt;
    /// See Trailing Stop order FAQ
    std::optional<common::Decimal> pending_below_trailing_delta = std::nullopt;
    /// This can only be used if `pendingBelowTimeInForce` is `GTC`, or if `pendingBelowType` is
    /// `LIMIT_MAKER`.
    std::optional<common::Decimal> pending_below_iceberg_qty = std::nullopt;
    /// Required if `pendingBelowType` is `STOP_LOSS_LIMIT` or `TAKE_PROFIT_LIMIT`.
    std::optional<OrderListOtocoPendingBelowTimeInForceEnum> pending_below_time_in_force =
        std::nullopt;
    /// Arbitrary numeric value identifying the pending below order within an order strategy.
    std::optional<std::int64_t> pending_below_strategy_id = std::nullopt;
    /// Arbitrary numeric value identifying the pending below order strategy. Values smaller than
    /// `1000000` are reserved and cannot be used.
    std::optional<std::int64_t> pending_below_strategy_type = std::nullopt;
    /// See Pegged Orders
    std::optional<OrderListOtocoPendingBelowPegPriceTypeEnum> pending_below_peg_price_type =
        std::nullopt;
    std::optional<OrderListOtocoPendingBelowPegOffsetTypeEnum> pending_below_peg_offset_type =
        std::nullopt;
    std::optional<std::int64_t> pending_below_peg_offset_value = std::nullopt;
    /// Quote notional limit for the working order (only for orders on the BUY side). See Quote
    /// Notional Limit.
    std::optional<common::Decimal> working_quote_notional_limit = std::nullopt;
    /// Quote notional limit for the pending above order (only for orders on the BUY side). See
    /// Quote Notional Limit.
    std::optional<common::Decimal> pending_above_quote_notional_limit = std::nullopt;
    /// Quote notional limit for the pending below order (only for orders on the BUY side). See
    /// Quote Notional Limit.
    std::optional<common::Decimal> pending_below_quote_notional_limit = std::nullopt;
    /// The value cannot be greater than `60000`. Supports up to three decimal places of precision
    /// (e.g., 6000.346) so that microseconds may be specified.
    std::optional<common::Decimal> recv_window = std::nullopt;
};

struct OrderOcoParams {
    common::Required<std::string> symbol;
    common::Required<OrderOcoSideEnum> side;
    common::Required<common::Decimal> quantity;
    common::Required<common::Decimal> price;
    common::Required<common::Decimal> stop_price;
    /// A unique Id for the entire orderList
    std::optional<std::string> list_client_order_id = std::nullopt;
    /// A unique Id for the limit order
    std::optional<std::string> limit_client_order_id = std::nullopt;
    std::optional<std::int64_t> limit_strategy_id = std::nullopt;
    /// The value cannot be less than `1000000`.
    std::optional<std::int64_t> limit_strategy_type = std::nullopt;
    /// Used to make the `LIMIT_MAKER` leg an iceberg order.
    std::optional<common::Decimal> limit_iceberg_qty = std::nullopt;
    std::optional<std::int64_t> trailing_delta = std::nullopt;
    /// A unique Id for the stop loss/stop loss limit leg
    std::optional<std::string> stop_client_order_id = std::nullopt;
    std::optional<std::int64_t> stop_strategy_id = std::nullopt;
    /// The value cannot be less than `1000000`.
    std::optional<std::int64_t> stop_strategy_type = std::nullopt;
    /// If provided, `stopLimitTimeInForce` is required.
    std::optional<common::Decimal> stop_limit_price = std::nullopt;
    /// Used with `STOP_LOSS_LIMIT` leg to make an iceberg order.
    std::optional<common::Decimal> stop_iceberg_qty = std::nullopt;
    /// Valid values are `GTC`/`FOK`/`IOC`
    std::optional<OrderOcoStopLimitTimeInForceEnum> stop_limit_time_in_force = std::nullopt;
    /// Format of the JSON response. Supported values: Order Response Type
    std::optional<OrderOcoNewOrderRespTypeEnum> new_order_resp_type = std::nullopt;
    /// The allowed values are dependent on what is configured on the symbol. Supported values: STP
    /// Modes
    std::optional<OrderOcoSelfTradePreventionModeEnum> self_trade_prevention_mode = std::nullopt;
    /// The value cannot be greater than `60000`.
    /// Supports up to three decimal places of precision (e.g., 6000.346) so that microseconds may
    /// be specified.
    std::optional<common::Decimal> recv_window = std::nullopt;
};

struct OrderTestParams {
    common::Required<std::string> symbol;
    common::Required<OrderTestSideEnum> side;
    common::Required<OrderTestTypeEnum> type;
    /// Default: `false`
    /// See Commissions FAQ to learn more.
    std::optional<bool> compute_commission_rates = std::nullopt;
    std::optional<OrderTestTimeInForceEnum> time_in_force = std::nullopt;
    std::optional<common::Decimal> quantity = std::nullopt;
    std::optional<common::Decimal> quote_order_qty = std::nullopt;
    std::optional<common::Decimal> price = std::nullopt;
    /// A unique id among open orders. Automatically generated if not sent. Orders with the same
    /// `newClientOrderID` can be accepted only when the previous one is filled, otherwise the order
    /// will be rejected.
    std::optional<std::string> new_client_order_id = std::nullopt;
    std::optional<std::int64_t> strategy_id = std::nullopt;
    /// The value cannot be less than `1000000`.
    std::optional<std::int64_t> strategy_type = std::nullopt;
    /// Used with `STOP_LOSS`, `STOP_LOSS_LIMIT`, `TAKE_PROFIT`, and `TAKE_PROFIT_LIMIT` orders.
    std::optional<common::Decimal> stop_price = std::nullopt;
    /// See Trailing Stop order FAQ
    std::optional<std::int64_t> trailing_delta = std::nullopt;
    /// Used with `LIMIT`, `STOP_LOSS_LIMIT`, and `TAKE_PROFIT_LIMIT` to create an iceberg order.
    std::optional<common::Decimal> iceberg_qty = std::nullopt;
    /// Set the response JSON. `ACK`, `RESULT`, or `FULL`; `MARKET` and `LIMIT` order types default
    /// to `FULL`, all other orders default to `ACK`.
    std::optional<OrderTestNewOrderRespTypeEnum> new_order_resp_type = std::nullopt;
    /// The allowed enums is dependent on what is configured on the symbol. Supported values: STP
    /// Modes
    std::optional<OrderTestSelfTradePreventionModeEnum> self_trade_prevention_mode = std::nullopt;
    /// `PRIMARY_PEG` or `MARKET_PEG`. See Pegged Orders
    std::optional<OrderTestPegPriceTypeEnum> peg_price_type = std::nullopt;
    /// Price level for pegging (max: 100). See Pegged Orders
    std::optional<std::int64_t> peg_offset_value = std::nullopt;
    /// Only `PRICE_LEVEL` is supported. See Pegged Orders
    std::optional<OrderTestPegOffsetTypeEnum> peg_offset_type = std::nullopt;
    /// For orders on the BUY side only. Maximum quote-asset notional the order may consume. See
    /// Quote Notional Limit.
    std::optional<common::Decimal> quote_notional_limit = std::nullopt;
    /// The value cannot be greater than `60000`. Supports up to three decimal places of precision
    /// (e.g., 6000.346) so that microseconds may be specified.
    std::optional<common::Decimal> recv_window = std::nullopt;
};

struct SorOrderParams {
    common::Required<std::string> symbol;
    common::Required<SorOrderSideEnum> side;
    common::Required<SorOrderTypeEnum> type;
    common::Required<common::Decimal> quantity;
    std::optional<SorOrderTimeInForceEnum> time_in_force = std::nullopt;
    std::optional<common::Decimal> price = std::nullopt;
    /// A unique id among open orders. Automatically generated if not sent.
    /// Orders with the same `newClientOrderID` can be accepted only when the previous one is
    /// filled, otherwise the order will be rejected.
    std::optional<std::string> new_client_order_id = std::nullopt;
    std::optional<std::int64_t> strategy_id = std::nullopt;
    /// The value cannot be less than `1000000`.
    std::optional<std::int64_t> strategy_type = std::nullopt;
    /// Used with `LIMIT` to create an iceberg order.
    std::optional<common::Decimal> iceberg_qty = std::nullopt;
    /// Set the response JSON. `ACK`, `RESULT`, or `FULL`. Default to `FULL`
    std::optional<SorOrderNewOrderRespTypeEnum> new_order_resp_type = std::nullopt;
    /// The allowed enums is dependent on what is configured on the symbol. The possible supported
    /// values are: STP Modes.
    std::optional<SorOrderSelfTradePreventionModeEnum> self_trade_prevention_mode = std::nullopt;
    /// The value cannot be greater than `60000`.
    /// Supports up to three decimal places of precision (e.g., 6000.346) so that microseconds may
    /// be specified.
    std::optional<common::Decimal> recv_window = std::nullopt;
};

struct SorOrderTestParams {
    common::Required<std::string> symbol;
    common::Required<SorOrderTestSideEnum> side;
    common::Required<SorOrderTestTypeEnum> type;
    common::Required<common::Decimal> quantity;
    std::optional<bool> compute_commission_rates = std::nullopt;
    std::optional<SorOrderTestTimeInForceEnum> time_in_force = std::nullopt;
    std::optional<common::Decimal> price = std::nullopt;
    /// A unique id among open orders. Automatically generated if not sent. Orders with the same
    /// `newClientOrderID` can be accepted only when the previous one is filled, otherwise the order
    /// will be rejected.
    std::optional<std::string> new_client_order_id = std::nullopt;
    std::optional<std::int64_t> strategy_id = std::nullopt;
    /// The value cannot be less than `1000000`.
    std::optional<std::int64_t> strategy_type = std::nullopt;
    /// Used with `LIMIT` to create an iceberg order.
    std::optional<common::Decimal> iceberg_qty = std::nullopt;
    /// Set the response JSON. `ACK`, `RESULT`, or `FULL`. Default to `FULL`.
    std::optional<SorOrderTestNewOrderRespTypeEnum> new_order_resp_type = std::nullopt;
    /// The allowed enums is dependent on what is configured on the symbol. Supported values: STP
    /// Modes
    std::optional<SorOrderTestSelfTradePreventionModeEnum> self_trade_prevention_mode =
        std::nullopt;
    /// The value cannot be greater than `60000`. Supports up to three decimal places of precision
    /// (e.g., 6000.346) so that microseconds may be specified.
    std::optional<common::Decimal> recv_window = std::nullopt;
};

class BINANCE_SPOT_EXPORT TradeApi {
public:
    explicit TradeApi(std::shared_ptr<common::RestClient> client);

    /// Cancel All Open Orders on a Symbol (TRADE)
    ///
    /// DELETE /api/v3/openOrders.
    ///
    /// Cancels all active orders on a symbol.
    /// This includes orders that are part of an order list.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// **Data Source:** Matching Engine
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/trade#delete-open-orders
    [[nodiscard]] common::RestApiResponse<std::vector<DeleteOpenOrdersResponseInner>>
    delete_open_orders(const DeleteOpenOrdersParams& params) const;

    /// Asynchronous `delete_open_orders()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<DeleteOpenOrdersResponseInner>>)`.
    template <class CompletionToken>
    auto async_delete_open_orders(const DeleteOpenOrdersParams& params,
                                  CompletionToken&& token) const {
        return common::async_send<std::vector<DeleteOpenOrdersResponseInner>>(
            client_, delete_open_orders_request(params), std::forward<CompletionToken>(token));
    }

    /// Cancel order (TRADE)
    ///
    /// DELETE /api/v3/order.
    ///
    /// Cancel an active order.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// **Data Source:** Matching Engine
    ///
    /// - Either `orderId` or `origClientOrderId` must be sent.
    /// - If both `orderId` and `origClientOrderId` are provided, the `orderId` is searched first,
    /// then the `origClientOrderId` from that result is checked against that order. If both
    /// conditions are not met the request will be rejected.
    ///
    /// Response Notes:
    /// **Notes:**
    /// - The payload above does not show all fields that can appear in the order response. Please
    /// refer to Conditional fields in Order Responses.
    /// - The performance for canceling an order (single cancel or as part of a cancel-replace) is
    /// always better when only `orderId` is sent. Sending `origClientOrderId` or both `orderId` +
    /// `origClientOrderId` will be slower.
    ///
    /// **Regarding `cancelRestrictions`**
    ///
    /// * If the `cancelRestrictions` value is not any of the supported values, the error will be:
    /// ```json
    /// {
    ///     "code": -1145,
    ///     "msg": "Invalid cancelRestrictions"
    /// }
    /// ```
    /// * If the order did not pass the conditions for `cancelRestrictions`, the error will be:
    /// ```json
    /// {
    ///     "code": -2011,
    ///     "msg": "Order was not canceled due to cancel restrictions."
    /// }
    /// ```
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/trade#delete-order
    [[nodiscard]] common::RestApiResponse<DeleteOrderResponse>
    delete_order(const DeleteOrderParams& params) const;

    /// Asynchronous `delete_order()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<DeleteOrderResponse>)`.
    template <class CompletionToken>
    auto async_delete_order(const DeleteOrderParams& params, CompletionToken&& token) const {
        return common::async_send<DeleteOrderResponse>(client_, delete_order_request(params),
                                                       std::forward<CompletionToken>(token));
    }

    /// New order (TRADE)
    ///
    /// POST /api/v3/order.
    ///
    /// Send in a new order.
    ///
    /// This adds 1 order to the `EXCHANGE_MAX_ORDERS` filter and the `MAX_NUM_ORDERS` filter.
    ///
    /// Weight(IP): 1
    ///
    /// Unfilled Order Count: 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// **Data Source:** Matching Engine
    ///
    /// Some additional mandatory parameters based on order `type`:
    ///
    /// Type | Additional mandatory parameters | Additional Information
    /// ------------ | ------------| ------
    /// `LIMIT` | `timeInForce`, `quantity`, `price`|
    /// `MARKET` | `quantity` or `quoteOrderQty`| `MARKET` orders using the `quantity` field
    /// specifies the amount of the `base asset` the user wants to buy or sell at the market price.
    /// E.g. MARKET order on BTCUSDT will specify how much BTC the user is buying or selling.
    ///
    /// `MARKET` orders using `quoteOrderQty` specifies the amount the user wants to spend (when
    /// buying) or receive (when selling) the `quote` asset; the correct `quantity` will be
    /// determined based on the market liquidity and `quoteOrderQty`. E.g. Using the symbol BTCUSDT:
    /// `BUY` side, the order will buy as many BTC as `quoteOrderQty` USDT can.
    /// `SELL` side, the order will sell as much BTC needed to receive `quoteOrderQty` USDT.
    /// `STOP_LOSS` | `quantity`, `stopPrice` or `trailingDelta`| This will execute a `MARKET` order
    /// when the conditions are met. (e.g. `stopPrice` is met or `trailingDelta` is activated)
    /// `STOP_LOSS_LIMIT` | `timeInForce`, `quantity`,  `price`, `stopPrice` or `trailingDelta`
    /// `TAKE_PROFIT` | `quantity`, `stopPrice` or `trailingDelta` | This will execute a `MARKET`
    /// order when the conditions are met. (e.g. `stopPrice` is met or `trailingDelta` is activated)
    /// `TAKE_PROFIT_LIMIT` | `timeInForce`, `quantity`, `price`, `stopPrice` or `trailingDelta` |
    /// `LIMIT_MAKER` | `quantity`, `price`| This is a `LIMIT` order that will be rejected if the
    /// order immediately matches and trades as a taker. This is also known as a POST-ONLY order.
    ///
    /// Notes on using parameters for Pegged Orders:
    ///
    /// * These parameters are allowed for `LIMIT`, `LIMIT_MAKER`, `STOP_LOSS_LIMIT`,
    /// `TAKE_PROFIT_LIMIT` orders.
    /// * If `pegPriceType` is specified, `price` becomes optional. Otherwise, it is still
    /// mandatory.
    /// * `pegPriceType=PRIMARY_PEG` means the primary peg, that is the best price on the same side
    /// of the order book as your order.
    /// * `pegPriceType=MARKET_PEG` means the market peg, that is the best price on the opposite
    /// side of the order book from your order.
    /// * Use `pegOffsetType` and `pegOffsetValue` to request a price level other than the best one.
    /// These parameters must be specified together.
    ///
    /// Other info:
    /// * Any `LIMIT` or `LIMIT_MAKER` type order can be made an iceberg order by sending an
    /// `icebergQty`.
    /// * Any order with an `icebergQty` MUST have `timeInForce` set to `GTC`.
    /// * For `STOP_LOSS`, `STOP_LOSS_LIMIT`, `TAKE_PROFIT_LIMIT` and `TAKE_PROFIT` orders,
    /// `trailingDelta` can be combined with `stopPrice`.
    /// * `MARKET` orders using `quoteOrderQty` will not break `LOT_SIZE` filter rules; the order
    /// will execute a `quantity` that will have the notional value as close as possible to
    /// `quoteOrderQty`. Trigger order price rules against market price for both MARKET and LIMIT
    /// versions:
    ///   * Price above market price: `STOP_LOSS` `BUY`, `TAKE_PROFIT` `SELL`
    ///   * Price below market price: `STOP_LOSS` `SELL`, `TAKE_PROFIT` `BUY`
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/trade#new-order
    [[nodiscard]] common::RestApiResponse<NewOrderResponse>
    new_order(const NewOrderParams& params) const;

    /// Asynchronous `new_order()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<NewOrderResponse>)`.
    template <class CompletionToken>
    auto async_new_order(const NewOrderParams& params, CompletionToken&& token) const {
        return common::async_send<NewOrderResponse>(client_, new_order_request(params),
                                                    std::forward<CompletionToken>(token));
    }

    /// Cancel Order list (TRADE)
    ///
    /// DELETE /api/v3/orderList.
    ///
    /// Cancel an entire Order list
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// **Data Source:** Matching Engine
    ///
    /// **Notes:**
    ///   - Canceling an individual order from an order list will cancel the entire order list.
    ///   - If both orderListId and listClientOrderId parameters are provided, the orderListId is
    ///   searched first, then the listClientOrderId from that result is checked against that order.
    ///   If both conditions are not met the request will be rejected.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/trade#delete-order-list
    [[nodiscard]] common::RestApiResponse<DeleteOrderListResponse>
    delete_order_list(const DeleteOrderListParams& params) const;

    /// Asynchronous `delete_order_list()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<DeleteOrderListResponse>)`.
    template <class CompletionToken>
    auto async_delete_order_list(const DeleteOrderListParams& params,
                                 CompletionToken&& token) const {
        return common::async_send<DeleteOrderListResponse>(
            client_, delete_order_list_request(params), std::forward<CompletionToken>(token));
    }

    /// Order Amend Keep Priority (TRADE)
    ///
    /// PUT /api/v3/order/amend/keepPriority.
    ///
    /// Reduce the quantity of an existing open order.
    ///
    /// This adds 0 orders to the `EXCHANGE_MAX_ORDERS` filter and the `MAX_NUM_ORDERS` filter.
    ///
    /// Read Order Amend Keep Priority FAQ to learn more.
    ///
    /// Weight(IP): 4
    ///
    /// Unfilled Order Count: 0
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// **Data Source:** Matching Engine
    ///
    /// Response Notes:
    /// **Note:** The payload above does not show all fields that can appear. Please refer to
    /// Conditional fields in Order Responses.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/trade#order-amend-keep-priority
    [[nodiscard]] common::RestApiResponse<OrderAmendKeepPriorityResponse>
    order_amend_keep_priority(const OrderAmendKeepPriorityParams& params) const;

    /// Asynchronous `order_amend_keep_priority()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<OrderAmendKeepPriorityResponse>)`.
    template <class CompletionToken>
    auto async_order_amend_keep_priority(const OrderAmendKeepPriorityParams& params,
                                         CompletionToken&& token) const {
        return common::async_send<OrderAmendKeepPriorityResponse>(
            client_, order_amend_keep_priority_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Cancel an Existing Order and Send a New Order (TRADE)
    ///
    /// POST /api/v3/order/cancelReplace.
    ///
    /// - Cancels an existing order and places a new order on the same symbol.
    /// - Filters and Order Count are evaluated before the processing of the cancellation and order
    /// placement occurs.
    /// - A new order that was not attempted (i.e. when `newOrderResult: NOT_ATTEMPTED`), will still
    /// increase the unfilled order count by 1.
    /// - You can only cancel an individual order from an orderList using this endpoint, but the
    /// result is the same as canceling the entire orderList.
    ///
    /// Weight(IP): 1
    ///
    /// Unfilled Order Count: 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// **Data Source:** Matching Engine
    ///
    /// Similar to `POST /api/v3/order`, additional mandatory parameters are determined by `type`.
    /// Response format varies depending on whether the processing of the message succeeded,
    /// partially succeeded, or failed.
    ///
    /// - Request | Response
    /// - `cancelReplaceMode` | `orderRateLimitExceededMode` | Unfilled Order Count | `cancelResult`
    /// | `newOrderResult` | `status`
    /// - `STOP_ON_FAILURE` | `DO_NOTHING` | Within Limits | ✅ `SUCCESS` | ✅ `SUCCESS` | `200`
    /// - `STOP_ON_FAILURE` | `DO_NOTHING` | Within Limits | ❌ `FAILURE` | ➖ `NOT_ATTEMPTED` |
    /// `400`
    /// - `STOP_ON_FAILURE` | `DO_NOTHING` | Within Limits | ✅ `SUCCESS` | ❌ `FAILURE` | `409`
    /// - `STOP_ON_FAILURE` | `DO_NOTHING` | Exceeds Limits | ✅ `SUCCESS` | ✅ `SUCCESS` | N/A
    /// - `STOP_ON_FAILURE` | `DO_NOTHING` | Exceeds Limits | ❌ `FAILURE` | ➖ `NOT_ATTEMPTED` |
    /// N/A
    /// - `STOP_ON_FAILURE` | `DO_NOTHING` | Exceeds Limits | ✅ `SUCCESS` | ❌ `FAILURE` | N/A
    /// - `STOP_ON_FAILURE` | `CANCEL_ONLY` | Within Limits | ✅ `SUCCESS` | ✅ `SUCCESS` | `200`
    /// - `STOP_ON_FAILURE` | `CANCEL_ONLY` | Within Limits | ❌ `FAILURE` | ➖ `NOT_ATTEMPTED` |
    /// `400`
    /// - `STOP_ON_FAILURE` | `CANCEL_ONLY` | Within Limits | ✅ `SUCCESS` | ❌ `FAILURE` | `409`
    /// - `STOP_ON_FAILURE` | `CANCEL_ONLY` | Exceeds Limits | ❌ `FAILURE` | ➖ `NOT_ATTEMPTED` |
    /// `429`
    /// - `STOP_ON_FAILURE` | `CANCEL_ONLY` | Exceeds Limits | ✅ `SUCCESS` | ❌ `FAILURE` | `429`
    /// - `ALLOW_FAILURE` | `DO_NOTHING` | Within Limits | ✅ `SUCCESS` | ✅ `SUCCESS` | `200`
    /// - `ALLOW_FAILURE` | `DO_NOTHING` | Within Limits | ❌ `FAILURE` | ❌ `FAILURE` | `400`
    /// - `ALLOW_FAILURE` | `DO_NOTHING` | Within Limits | ❌ `FAILURE` | ✅ `SUCCESS` | `409`
    /// - `ALLOW_FAILURE` | `DO_NOTHING` | Within Limits | ✅ `SUCCESS` | ❌ `FAILURE` | `409`
    /// - `ALLOW_FAILURE` | `DO_NOTHING` | Exceeds Limits | ✅ `SUCCESS` | ✅ `SUCCESS` | N/A
    /// - `ALLOW_FAILURE` | `DO_NOTHING` | Exceeds Limits | ❌ `FAILURE` | ❌ `FAILURE` | N/A
    /// - `ALLOW_FAILURE` | `DO_NOTHING` | Exceeds Limits | ❌ `FAILURE` | ✅ `SUCCESS` | N/A
    /// - `ALLOW_FAILURE` | `DO_NOTHING` | Exceeds Limits | ✅ `SUCCESS` | ❌ `FAILURE` | N/A
    /// - `ALLOW_FAILURE` | `CANCEL_ONLY` | Within Limits | ✅ `SUCCESS` | ✅ `SUCCESS` | `200`
    /// - `ALLOW_FAILURE` | `CANCEL_ONLY` | Within Limits | ❌ `FAILURE` | ❌ `FAILURE` | `400`
    /// - `ALLOW_FAILURE` | `CANCEL_ONLY` | Within Limits | ❌ `FAILURE` | ✅ `SUCCESS` | `409`
    /// - `ALLOW_FAILURE` | `CANCEL_ONLY` | Within Limits | ✅ `SUCCESS` | ❌ `FAILURE` | `409`
    /// - `ALLOW_FAILURE` | `CANCEL_ONLY` | Exceeds Limits | ✅ `SUCCESS` | ✅ `SUCCESS` | `N/A`
    /// - `ALLOW_FAILURE` | `CANCEL_ONLY` | Exceeds Limits | ❌ `FAILURE` | ❌ `FAILURE` | `400`
    /// - `ALLOW_FAILURE` | `CANCEL_ONLY` | Exceeds Limits | ❌ `FAILURE` | ✅ `SUCCESS` | N/A
    /// - `ALLOW_FAILURE` | `CANCEL_ONLY` | Exceeds Limits | ✅ `SUCCESS` | ❌ `FAILURE` | `409`
    ///
    /// Response Notes:
    /// **Notes:**
    /// - The payload above does not show all fields that can appear. Please refer to Conditional
    /// fields in Order Responses.
    /// - The performance for canceling an order (single cancel or as part of a cancel-replace) is
    /// always better when only `orderId` is sent. Sending `origClientOrderId` or both `orderId` +
    /// `origClientOrderId` will be slower.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/trade#order-cancel-replace
    [[nodiscard]] common::RestApiResponse<OrderCancelReplaceResponse>
    order_cancel_replace(const OrderCancelReplaceParams& params) const;

    /// Asynchronous `order_cancel_replace()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<OrderCancelReplaceResponse>)`.
    template <class CompletionToken>
    auto async_order_cancel_replace(const OrderCancelReplaceParams& params,
                                    CompletionToken&& token) const {
        return common::async_send<OrderCancelReplaceResponse>(
            client_, order_cancel_replace_request(params), std::forward<CompletionToken>(token));
    }

    /// New Order list - OCO (TRADE)
    ///
    /// POST /api/v3/orderList/oco.
    ///
    /// Send in an one-cancels-the-other (OCO) pair, where activation of one
    /// order immediately cancels the other.
    ///
    /// - An OCO has 2 orders called the **above order** and **below order**.
    /// - One of the orders must be a `LIMIT_MAKER/TAKE_PROFIT/TAKE_PROFIT_LIMIT` order and the
    /// other must be `STOP_LOSS` or `STOP_LOSS_LIMIT` order.
    /// - Price restrictions
    ///   - If the OCO is on the `SELL` side:
    ///     - `LIMIT_MAKER/TAKE_PROFIT_LIMIT` `price` > Last Traded Price >
    ///     `STOP_LOSS/STOP_LOSS_LIMIT` `stopPrice`
    ///     - `TAKE_PROFIT stopPrice` > Last Traded Price > `STOP_LOSS/STOP_LOSS_LIMIT stopPrice`
    ///   - If the OCO is on the `BUY` side:
    ///     - `LIMIT_MAKER/TAKE_PROFIT_LIMIT price` < Last Traded Price < `stopPrice`
    ///     - `TAKE_PROFIT stopPrice` < Last Traded Price < `STOP_LOSS/STOP_LOSS_LIMIT stopPrice` *
    ///     OCOs add **2 orders** to the `EXCHANGE_MAX_ORDERS` filter and the `MAX_NUM_ORDERS`
    ///     filter.
    /// - OCOs add 2 orders to the `EXCHANGE_MAX_ORDERS` filter and the `MAX_NUM_ORDERS` filter.
    ///
    /// Weight(IP): 1
    ///
    /// Unfilled Order Count: 2
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// **Data Source:** Matching Engine
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/trade#order-list-oco
    [[nodiscard]] common::RestApiResponse<OrderListOcoResponse>
    order_list_oco(const OrderListOcoParams& params) const;

    /// Asynchronous `order_list_oco()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<OrderListOcoResponse>)`.
    template <class CompletionToken>
    auto async_order_list_oco(const OrderListOcoParams& params, CompletionToken&& token) const {
        return common::async_send<OrderListOcoResponse>(client_, order_list_oco_request(params),
                                                        std::forward<CompletionToken>(token));
    }

    /// New Order List - OPO (TRADE)
    ///
    /// POST /api/v3/orderList/opo.
    ///
    /// Place an OPO.
    ///
    /// - The working order must be `LIMIT` or `LIMIT_MAKER`.
    /// - OPOs add 2 orders to the `EXCHANGE_MAX_NUM_ORDERS` filter and `MAX_NUM_ORDERS` filter.
    ///
    /// Weight(IP): 1
    ///
    /// Unfilled Order Count: 2
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// **Data Source:** Matching Engine
    ///
    /// Response Notes:
    /// **Note:** The payload above does not show all fields that can appear. Please refer to
    /// Conditional fields in Order Responses.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/trade#order-list-opo
    [[nodiscard]] common::RestApiResponse<OrderListOpoResponse>
    order_list_opo(const OrderListOpoParams& params) const;

    /// Asynchronous `order_list_opo()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<OrderListOpoResponse>)`.
    template <class CompletionToken>
    auto async_order_list_opo(const OrderListOpoParams& params, CompletionToken&& token) const {
        return common::async_send<OrderListOpoResponse>(client_, order_list_opo_request(params),
                                                        std::forward<CompletionToken>(token));
    }

    /// New Order List - OPOCO (TRADE)
    ///
    /// POST /api/v3/orderList/opoco.
    ///
    /// Place an OPOCO.
    ///
    /// - The working order must be `LIMIT` or `LIMIT_MAKER`.
    ///
    /// Weight(IP): 1
    ///
    /// Unfilled Order Count: 3
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// **Data Source:** Matching Engine
    ///
    /// Response Notes:
    /// **Note:** The payload above does not show all fields that can appear. Please refer to
    /// Conditional fields in Order Responses.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/trade#order-list-opoco
    [[nodiscard]] common::RestApiResponse<OrderListOpocoResponse>
    order_list_opoco(const OrderListOpocoParams& params) const;

    /// Asynchronous `order_list_opoco()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<OrderListOpocoResponse>)`.
    template <class CompletionToken>
    auto async_order_list_opoco(const OrderListOpocoParams& params, CompletionToken&& token) const {
        return common::async_send<OrderListOpocoResponse>(client_, order_list_opoco_request(params),
                                                          std::forward<CompletionToken>(token));
    }

    /// New Order list - OTO (TRADE)
    ///
    /// POST /api/v3/orderList/oto.
    ///
    /// Place an OTO.
    ///
    /// - An OTO (One-Triggers-the-Other) is an order list comprised of 2 orders.
    /// - The first order is called the **working order** and must be `LIMIT` or `LIMIT_MAKER`.
    /// Initially, only the working order goes on the order book.
    /// - The second order is called the **pending order**. It can be any order type except for
    /// `MARKET` orders using parameter `quoteOrderQty`. The pending order is only placed on the
    /// order book when the working order gets **fully filled**.
    /// - If either the working order or the pending order is cancelled individually, the other
    /// order in the order list will also be canceled or expired.
    /// - When the order list is placed, if the working order gets **immediately fully filled**, the
    /// placement response will show the working order as `FILLED` but the pending order will still
    /// appear as `PENDING_NEW`. You need to query the status of the pending order again to see its
    /// updated status.
    /// - OTOs add **2 orders** to the `EXCHANGE_MAX_NUM_ORDERS` filter and `MAX_NUM_ORDERS` filter.
    ///
    /// Weight(IP): 1
    ///
    /// Unfilled Order Count: 2
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// **Data Source:** Matching Engine
    ///
    /// **Mandatory parameters based on `pendingType` or `workingType`**
    ///
    /// Depending on the `pendingType` or `workingType`, some optional parameters will become
    /// mandatory.
    ///
    /// |Type                                                  |Additional mandatory
    /// parameters|Additional information|
    /// |----                                                  |---- |------
    /// |`workingType` = `LIMIT`                               |`workingTimeInForce`           |
    /// |`pendingType` = `LIMIT`                                |`pendingPrice`,
    /// `pendingTimeInForce`          |
    /// |`pendingType` = `STOP_LOSS` or `TAKE_PROFIT`           |`pendingStopPrice` and/or
    /// `pendingTrailingDelta`|
    /// |`pendingType` = `STOP_LOSS_LIMIT` or `TAKE_PROFIT_LIMIT`|`pendingPrice`, `pendingStopPrice`
    /// and/or `pendingTrailingDelta`, `pendingTimeInForce`|
    ///
    /// Response Notes:
    /// **Note:** The payload above does not show all fields that can appear. Please refer to
    /// Conditional fields in Order Responses.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/trade#order-list-oto
    [[nodiscard]] common::RestApiResponse<OrderListOtoResponse>
    order_list_oto(const OrderListOtoParams& params) const;

    /// Asynchronous `order_list_oto()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<OrderListOtoResponse>)`.
    template <class CompletionToken>
    auto async_order_list_oto(const OrderListOtoParams& params, CompletionToken&& token) const {
        return common::async_send<OrderListOtoResponse>(client_, order_list_oto_request(params),
                                                        std::forward<CompletionToken>(token));
    }

    /// New Order list - OTOCO (TRADE)
    ///
    /// POST /api/v3/orderList/otoco.
    ///
    /// Place an OTOCO.
    ///
    /// - An OTOCO (One-Triggers-One-Cancels-the-Other) is an order list comprised of 3 orders.
    /// - The first order is called the **working order** and must be `LIMIT` or `LIMIT_MAKER`.
    /// Initially, only the working order goes on the order book.
    ///   - The behavior of the working order is the same as the OTO.
    /// - OTOCO has 2 pending orders (pending above and pending below), forming an OCO pair. The
    /// pending orders are only placed on the order book when the working order gets **fully
    /// filled**.
    ///   - The rules of the pending above and pending below follow the same rules as the Order list
    ///   OCO.
    /// - OTOCOs add **3 orders** to the `EXCHANGE_MAX_NUM_ORDERS` filter and `MAX_NUM_ORDERS`
    /// filter.
    ///
    /// Weight(IP): 1
    ///
    /// Unfilled Order Count: 3
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// **Data Source:** Matching Engine
    ///
    /// **Mandatory parameters based on `pendingAboveType`, `pendingBelowType` or `workingType`**
    ///
    /// Depending on the `pendingAboveType`/`pendingBelowType` or `workingType`, some optional
    /// parameters will become mandatory.
    ///
    /// |Type                                                       |Additional mandatory
    /// parameters|Additional information|
    /// |----                                                       |---- |------
    /// |`workingType` = `LIMIT`                                    |`workingTimeInForce` |
    /// |`pendingAboveType`= `LIMIT_MAKER`                                |`pendingAbovePrice`     |
    /// |`pendingAboveType` = `STOP_LOSS/TAKE_PROFIT`        |`pendingAboveStopPrice` and/or
    /// `pendingAboveTrailingDelta`|
    /// |`pendingAboveType=STOP_LOSS_LIMIT/TAKE_PROFIT_LIMIT` |`pendingAbovePrice`,
    /// `pendingAboveStopPrice` and/or `pendingAboveTrailingDelta`, `pendingAboveTimeInForce`|
    /// |`pendingBelowType`= `LIMIT_MAKER`                                |`pendingBelowPrice` |
    /// |`pendingBelowType= STOP_LOSS/TAKE_PROFIT`         |`pendingBelowStopPrice` and/or
    /// `pendingBelowTrailingDelta`|
    /// |`pendingBelowType=STOP_LOSS_LIMIT/TAKE_PROFIT_LIMIT` |`pendingBelowPrice`,
    /// `pendingBelowStopPrice` and/or `pendingBelowTrailingDelta`, `pendingBelowTimeInForce`|
    ///
    /// Response Notes:
    /// **Note:** The payload above does not show all fields that can appear. Please refer to
    /// Conditional fields in Order Responses.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/trade#order-list-otoco
    [[nodiscard]] common::RestApiResponse<OrderListOtocoResponse>
    order_list_otoco(const OrderListOtocoParams& params) const;

    /// Asynchronous `order_list_otoco()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<OrderListOtocoResponse>)`.
    template <class CompletionToken>
    auto async_order_list_otoco(const OrderListOtocoParams& params, CompletionToken&& token) const {
        return common::async_send<OrderListOtocoResponse>(client_, order_list_otoco_request(params),
                                                          std::forward<CompletionToken>(token));
    }

    /// New OCO - Deprecated (TRADE)
    ///
    /// POST /api/v3/order/oco.
    ///
    /// Send in a new OCO.
    ///
    /// - Price Restrictions:
    ///   - `SELL`: Limit Price > Last Price > Stop Price
    ///   - `BUY`: Limit Price < Last Price < Stop Price
    /// - Quantity Restrictions:
    ///   - Both legs must have the same quantity.
    ///   - `ICEBERG` quantities however do not have to be the same
    /// - `OCO` adds **2 orders** to the `EXCHANGE_MAX_ORDERS` filter and the `MAX_NUM_ORDERS`
    /// filter.
    ///
    /// Weight(IP): 1
    ///
    /// Unfilled Order Count: 2
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// **Data Source:** Matching Engine
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/trade#order-oco
    ///
    /// Deprecated: this endpoint may be removed in a future version.
    [[nodiscard]] common::RestApiResponse<OrderOcoResponse>
    order_oco(const OrderOcoParams& params) const;

    /// Asynchronous `order_oco()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<OrderOcoResponse>)`.
    template <class CompletionToken>
    auto async_order_oco(const OrderOcoParams& params, CompletionToken&& token) const {
        return common::async_send<OrderOcoResponse>(client_, order_oco_request(params),
                                                    std::forward<CompletionToken>(token));
    }

    /// Test new order (TRADE)
    ///
    /// POST /api/v3/order/test.
    ///
    /// Test new order creation and signature/recvWindow long.
    ///
    /// Creates and validates a new order but does not send it into the matching
    /// engine.
    ///
    /// Weight: |Condition|Weight|
    /// |---|---|
    /// |Without `computeCommissionRates`|1|
    /// |With `computeCommissionRates`|20|
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// **Data Source:** Memory
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/trade#order-test
    [[nodiscard]] common::RestApiResponse<OrderTestResponse>
    order_test(const OrderTestParams& params) const;

    /// Asynchronous `order_test()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<OrderTestResponse>)`.
    template <class CompletionToken>
    auto async_order_test(const OrderTestParams& params, CompletionToken&& token) const {
        return common::async_send<OrderTestResponse>(client_, order_test_request(params),
                                                     std::forward<CompletionToken>(token));
    }

    /// New order using SOR (TRADE)
    ///
    /// POST /api/v3/sor/order.
    ///
    /// Places an order using smart order routing (SOR).
    ///
    /// This adds 1 order to the `EXCHANGE_MAX_ORDERS` filter and the `MAX_NUM_ORDERS` filter.
    ///
    /// Read SOR FAQ to learn more.
    ///
    /// Weight(IP): 1
    ///
    /// Unfilled Order Count: 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// **Data Source:** Matching Engine
    ///
    /// **Note:** `POST /api/v3/sor/order` only supports `LIMIT` and `MARKET` orders.
    /// `quoteOrderQty` is not supported.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/trade#sor-order
    [[nodiscard]] common::RestApiResponse<SorOrderResponse>
    sor_order(const SorOrderParams& params) const;

    /// Asynchronous `sor_order()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<SorOrderResponse>)`.
    template <class CompletionToken>
    auto async_sor_order(const SorOrderParams& params, CompletionToken&& token) const {
        return common::async_send<SorOrderResponse>(client_, sor_order_request(params),
                                                    std::forward<CompletionToken>(token));
    }

    /// Test new order using SOR (TRADE)
    ///
    /// POST /api/v3/sor/order/test.
    ///
    /// Test new order creation and signature/recvWindow using smart order routing (SOR).
    /// Creates and validates a new order but does not send it into the matching engine.
    ///
    /// Weight: |Condition|Weight|
    /// |---|---|
    /// |Without `computeCommissionRates`|1|
    /// |With `computeCommissionRates`|20|
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// **Data Source:** Memory
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/trade#sor-order-test
    [[nodiscard]] common::RestApiResponse<SorOrderTestResponse>
    sor_order_test(const SorOrderTestParams& params) const;

    /// Asynchronous `sor_order_test()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<SorOrderTestResponse>)`.
    template <class CompletionToken>
    auto async_sor_order_test(const SorOrderTestParams& params, CompletionToken&& token) const {
        return common::async_send<SorOrderTestResponse>(client_, sor_order_test_request(params),
                                                        std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest
    delete_open_orders_request(const DeleteOpenOrdersParams& params) const;
    [[nodiscard]] common::RestRequest delete_order_request(const DeleteOrderParams& params) const;
    [[nodiscard]] common::RestRequest new_order_request(const NewOrderParams& params) const;
    [[nodiscard]] common::RestRequest
    delete_order_list_request(const DeleteOrderListParams& params) const;
    [[nodiscard]] common::RestRequest
    order_amend_keep_priority_request(const OrderAmendKeepPriorityParams& params) const;
    [[nodiscard]] common::RestRequest
    order_cancel_replace_request(const OrderCancelReplaceParams& params) const;
    [[nodiscard]] common::RestRequest
    order_list_oco_request(const OrderListOcoParams& params) const;
    [[nodiscard]] common::RestRequest
    order_list_opo_request(const OrderListOpoParams& params) const;
    [[nodiscard]] common::RestRequest
    order_list_opoco_request(const OrderListOpocoParams& params) const;
    [[nodiscard]] common::RestRequest
    order_list_oto_request(const OrderListOtoParams& params) const;
    [[nodiscard]] common::RestRequest
    order_list_otoco_request(const OrderListOtocoParams& params) const;
    [[nodiscard]] common::RestRequest order_oco_request(const OrderOcoParams& params) const;
    [[nodiscard]] common::RestRequest order_test_request(const OrderTestParams& params) const;
    [[nodiscard]] common::RestRequest sor_order_request(const SorOrderParams& params) const;
    [[nodiscard]] common::RestRequest
    sor_order_test_request(const SorOrderTestParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::spot::rest_api
