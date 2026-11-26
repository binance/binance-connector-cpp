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
#include <binance/spot/export.hpp>
#include <binance/spot/websocket_api/models/open_orders_cancel_all_response_result_inner.hpp>
#include <binance/spot/websocket_api/models/order_amend_keep_priority_response_result.hpp>
#include <binance/spot/websocket_api/models/order_cancel_replace_response_result.hpp>
#include <binance/spot/websocket_api/models/order_cancel_response_result.hpp>
#include <binance/spot/websocket_api/models/order_list_cancel_response_result.hpp>
#include <binance/spot/websocket_api/models/order_list_place_oco_response_result.hpp>
#include <binance/spot/websocket_api/models/order_list_place_opo_response_result.hpp>
#include <binance/spot/websocket_api/models/order_list_place_opoco_response_result.hpp>
#include <binance/spot/websocket_api/models/order_list_place_oto_response_result.hpp>
#include <binance/spot/websocket_api/models/order_list_place_otoco_response_result.hpp>
#include <binance/spot/websocket_api/models/order_list_place_response_result.hpp>
#include <binance/spot/websocket_api/models/order_place_response_result.hpp>
#include <binance/spot/websocket_api/models/order_test_response_result.hpp>
#include <binance/spot/websocket_api/models/sor_order_place_response_result_inner.hpp>
#include <binance/spot/websocket_api/models/sor_order_test_response_result.hpp>

namespace binance::spot::websocket_api {

enum class OrderCancelCancelRestrictionsEnum {
    OnlyNew,
    OnlyPartiallyFilled,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderCancelCancelRestrictionsEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderCancelCancelRestrictionsEnum
tag_invoke(boost::json::value_to_tag<OrderCancelCancelRestrictionsEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderCancelCancelRestrictionsEnum value);

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

enum class OrderListPlaceSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view to_string(OrderListPlaceSideEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceSideEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceSideEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceSideEnum value);

enum class OrderListPlaceStopLimitTimeInForceEnum {
    Gtc,
    Ioc,
    Fok,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceStopLimitTimeInForceEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceStopLimitTimeInForceEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceStopLimitTimeInForceEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceStopLimitTimeInForceEnum value);

enum class OrderListPlaceNewOrderRespTypeEnum {
    Ack,
    Result,
    Full,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceNewOrderRespTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceNewOrderRespTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceNewOrderRespTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceNewOrderRespTypeEnum value);

enum class OrderListPlaceSelfTradePreventionModeEnum {
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
to_string(OrderListPlaceSelfTradePreventionModeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceSelfTradePreventionModeEnum value);

enum class OrderListPlaceOcoSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOcoSideEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOcoSideEnum tag_invoke(
    boost::json::value_to_tag<OrderListPlaceOcoSideEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOcoSideEnum value);

enum class OrderListPlaceOcoAboveTypeEnum {
    StopLossLimit,
    StopLoss,
    LimitMaker,
    TakeProfit,
    TakeProfitLimit,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOcoAboveTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOcoAboveTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOcoAboveTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOcoAboveTypeEnum value);

enum class OrderListPlaceOcoBelowTypeEnum {
    StopLoss,
    StopLossLimit,
    TakeProfit,
    TakeProfitLimit,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOcoBelowTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOcoBelowTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOcoBelowTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOcoBelowTypeEnum value);

enum class OrderListPlaceOcoAboveTimeInForceEnum {
    Gtc,
    Ioc,
    Fok,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOcoAboveTimeInForceEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOcoAboveTimeInForceEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOcoAboveTimeInForceEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOcoAboveTimeInForceEnum value);

enum class OrderListPlaceOcoAbovePegPriceTypeEnum {
    PrimaryPeg,
    MarketPeg,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOcoAbovePegPriceTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOcoAbovePegPriceTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOcoAbovePegPriceTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOcoAbovePegPriceTypeEnum value);

enum class OrderListPlaceOcoAbovePegOffsetTypeEnum {
    PriceLevel,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOcoAbovePegOffsetTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOcoAbovePegOffsetTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOcoAbovePegOffsetTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOcoAbovePegOffsetTypeEnum value);

enum class OrderListPlaceOcoBelowTimeInForceEnum {
    Gtc,
    Ioc,
    Fok,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOcoBelowTimeInForceEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOcoBelowTimeInForceEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOcoBelowTimeInForceEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOcoBelowTimeInForceEnum value);

enum class OrderListPlaceOcoBelowPegPriceTypeEnum {
    PrimaryPeg,
    MarketPeg,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOcoBelowPegPriceTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOcoBelowPegPriceTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOcoBelowPegPriceTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOcoBelowPegPriceTypeEnum value);

enum class OrderListPlaceOcoBelowPegOffsetTypeEnum {
    PriceLevel,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOcoBelowPegOffsetTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOcoBelowPegOffsetTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOcoBelowPegOffsetTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOcoBelowPegOffsetTypeEnum value);

enum class OrderListPlaceOcoNewOrderRespTypeEnum {
    Ack,
    Result,
    Full,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOcoNewOrderRespTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOcoNewOrderRespTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOcoNewOrderRespTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOcoNewOrderRespTypeEnum value);

enum class OrderListPlaceOcoSelfTradePreventionModeEnum {
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
to_string(OrderListPlaceOcoSelfTradePreventionModeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOcoSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOcoSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOcoSelfTradePreventionModeEnum value);

enum class OrderListPlaceOpoWorkingTypeEnum {
    Limit,
    LimitMaker,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOpoWorkingTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOpoWorkingTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOpoWorkingTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOpoWorkingTypeEnum value);

enum class OrderListPlaceOpoWorkingSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOpoWorkingSideEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOpoWorkingSideEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOpoWorkingSideEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOpoWorkingSideEnum value);

enum class OrderListPlaceOpoPendingTypeEnum {
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
to_string(OrderListPlaceOpoPendingTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOpoPendingTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOpoPendingTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOpoPendingTypeEnum value);

enum class OrderListPlaceOpoPendingSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOpoPendingSideEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOpoPendingSideEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOpoPendingSideEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOpoPendingSideEnum value);

enum class OrderListPlaceOpoNewOrderRespTypeEnum {
    Ack,
    Result,
    Full,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOpoNewOrderRespTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOpoNewOrderRespTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOpoNewOrderRespTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOpoNewOrderRespTypeEnum value);

enum class OrderListPlaceOpoSelfTradePreventionModeEnum {
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
to_string(OrderListPlaceOpoSelfTradePreventionModeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOpoSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOpoSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOpoSelfTradePreventionModeEnum value);

enum class OrderListPlaceOpoWorkingTimeInForceEnum {
    Gtc,
    Ioc,
    Fok,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOpoWorkingTimeInForceEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOpoWorkingTimeInForceEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOpoWorkingTimeInForceEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOpoWorkingTimeInForceEnum value);

enum class OrderListPlaceOpoWorkingPegPriceTypeEnum {
    PrimaryPeg,
    MarketPeg,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOpoWorkingPegPriceTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOpoWorkingPegPriceTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOpoWorkingPegPriceTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOpoWorkingPegPriceTypeEnum value);

enum class OrderListPlaceOpoWorkingPegOffsetTypeEnum {
    PriceLevel,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOpoWorkingPegOffsetTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOpoWorkingPegOffsetTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOpoWorkingPegOffsetTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOpoWorkingPegOffsetTypeEnum value);

enum class OrderListPlaceOpoPendingTimeInForceEnum {
    Gtc,
    Ioc,
    Fok,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOpoPendingTimeInForceEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOpoPendingTimeInForceEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOpoPendingTimeInForceEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOpoPendingTimeInForceEnum value);

enum class OrderListPlaceOpoPendingPegPriceTypeEnum {
    PrimaryPeg,
    MarketPeg,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOpoPendingPegPriceTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOpoPendingPegPriceTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOpoPendingPegPriceTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOpoPendingPegPriceTypeEnum value);

enum class OrderListPlaceOpoPendingPegOffsetTypeEnum {
    PriceLevel,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOpoPendingPegOffsetTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOpoPendingPegOffsetTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOpoPendingPegOffsetTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOpoPendingPegOffsetTypeEnum value);

enum class OrderListPlaceOpocoWorkingTypeEnum {
    Limit,
    LimitMaker,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOpocoWorkingTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOpocoWorkingTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOpocoWorkingTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOpocoWorkingTypeEnum value);

enum class OrderListPlaceOpocoWorkingSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOpocoWorkingSideEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOpocoWorkingSideEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOpocoWorkingSideEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOpocoWorkingSideEnum value);

enum class OrderListPlaceOpocoPendingSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOpocoPendingSideEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOpocoPendingSideEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOpocoPendingSideEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOpocoPendingSideEnum value);

enum class OrderListPlaceOpocoPendingAboveTypeEnum {
    StopLossLimit,
    StopLoss,
    LimitMaker,
    TakeProfit,
    TakeProfitLimit,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOpocoPendingAboveTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOpocoPendingAboveTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOpocoPendingAboveTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOpocoPendingAboveTypeEnum value);

enum class OrderListPlaceOpocoNewOrderRespTypeEnum {
    Ack,
    Result,
    Full,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOpocoNewOrderRespTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOpocoNewOrderRespTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOpocoNewOrderRespTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOpocoNewOrderRespTypeEnum value);

enum class OrderListPlaceOpocoSelfTradePreventionModeEnum {
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
to_string(OrderListPlaceOpocoSelfTradePreventionModeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOpocoSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOpocoSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOpocoSelfTradePreventionModeEnum value);

enum class OrderListPlaceOpocoWorkingTimeInForceEnum {
    Gtc,
    Ioc,
    Fok,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOpocoWorkingTimeInForceEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOpocoWorkingTimeInForceEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOpocoWorkingTimeInForceEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOpocoWorkingTimeInForceEnum value);

enum class OrderListPlaceOpocoWorkingPegPriceTypeEnum {
    PrimaryPeg,
    MarketPeg,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOpocoWorkingPegPriceTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOpocoWorkingPegPriceTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOpocoWorkingPegPriceTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOpocoWorkingPegPriceTypeEnum value);

enum class OrderListPlaceOpocoWorkingPegOffsetTypeEnum {
    PriceLevel,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOpocoWorkingPegOffsetTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOpocoWorkingPegOffsetTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOpocoWorkingPegOffsetTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOpocoWorkingPegOffsetTypeEnum value);

enum class OrderListPlaceOpocoPendingAboveTimeInForceEnum {
    Gtc,
    Ioc,
    Fok,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOpocoPendingAboveTimeInForceEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOpocoPendingAboveTimeInForceEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOpocoPendingAboveTimeInForceEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOpocoPendingAboveTimeInForceEnum value);

enum class OrderListPlaceOpocoPendingAbovePegPriceTypeEnum {
    PrimaryPeg,
    MarketPeg,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOpocoPendingAbovePegPriceTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOpocoPendingAbovePegPriceTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOpocoPendingAbovePegPriceTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOpocoPendingAbovePegPriceTypeEnum value);

enum class OrderListPlaceOpocoPendingAbovePegOffsetTypeEnum {
    PriceLevel,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOpocoPendingAbovePegOffsetTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOpocoPendingAbovePegOffsetTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOpocoPendingAbovePegOffsetTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOpocoPendingAbovePegOffsetTypeEnum value);

enum class OrderListPlaceOpocoPendingBelowTypeEnum {
    StopLoss,
    StopLossLimit,
    TakeProfit,
    TakeProfitLimit,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOpocoPendingBelowTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOpocoPendingBelowTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOpocoPendingBelowTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOpocoPendingBelowTypeEnum value);

enum class OrderListPlaceOpocoPendingBelowTimeInForceEnum {
    Gtc,
    Ioc,
    Fok,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOpocoPendingBelowTimeInForceEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOpocoPendingBelowTimeInForceEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOpocoPendingBelowTimeInForceEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOpocoPendingBelowTimeInForceEnum value);

enum class OrderListPlaceOpocoPendingBelowPegPriceTypeEnum {
    PrimaryPeg,
    MarketPeg,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOpocoPendingBelowPegPriceTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOpocoPendingBelowPegPriceTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOpocoPendingBelowPegPriceTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOpocoPendingBelowPegPriceTypeEnum value);

enum class OrderListPlaceOpocoPendingBelowPegOffsetTypeEnum {
    PriceLevel,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOpocoPendingBelowPegOffsetTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOpocoPendingBelowPegOffsetTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOpocoPendingBelowPegOffsetTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOpocoPendingBelowPegOffsetTypeEnum value);

enum class OrderListPlaceOtoWorkingTypeEnum {
    Limit,
    LimitMaker,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOtoWorkingTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOtoWorkingTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOtoWorkingTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOtoWorkingTypeEnum value);

enum class OrderListPlaceOtoWorkingSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOtoWorkingSideEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOtoWorkingSideEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOtoWorkingSideEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOtoWorkingSideEnum value);

enum class OrderListPlaceOtoPendingTypeEnum {
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
to_string(OrderListPlaceOtoPendingTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOtoPendingTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOtoPendingTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOtoPendingTypeEnum value);

enum class OrderListPlaceOtoPendingSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOtoPendingSideEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOtoPendingSideEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOtoPendingSideEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOtoPendingSideEnum value);

enum class OrderListPlaceOtoNewOrderRespTypeEnum {
    Ack,
    Result,
    Full,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOtoNewOrderRespTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOtoNewOrderRespTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOtoNewOrderRespTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOtoNewOrderRespTypeEnum value);

enum class OrderListPlaceOtoSelfTradePreventionModeEnum {
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
to_string(OrderListPlaceOtoSelfTradePreventionModeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOtoSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOtoSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOtoSelfTradePreventionModeEnum value);

enum class OrderListPlaceOtoWorkingTimeInForceEnum {
    Gtc,
    Ioc,
    Fok,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOtoWorkingTimeInForceEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOtoWorkingTimeInForceEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOtoWorkingTimeInForceEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOtoWorkingTimeInForceEnum value);

enum class OrderListPlaceOtoWorkingPegPriceTypeEnum {
    PrimaryPeg,
    MarketPeg,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOtoWorkingPegPriceTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOtoWorkingPegPriceTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOtoWorkingPegPriceTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOtoWorkingPegPriceTypeEnum value);

enum class OrderListPlaceOtoWorkingPegOffsetTypeEnum {
    PriceLevel,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOtoWorkingPegOffsetTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOtoWorkingPegOffsetTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOtoWorkingPegOffsetTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOtoWorkingPegOffsetTypeEnum value);

enum class OrderListPlaceOtoPendingTimeInForceEnum {
    Gtc,
    Ioc,
    Fok,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOtoPendingTimeInForceEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOtoPendingTimeInForceEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOtoPendingTimeInForceEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOtoPendingTimeInForceEnum value);

enum class OrderListPlaceOtoPendingPegOffsetTypeEnum {
    PriceLevel,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOtoPendingPegOffsetTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOtoPendingPegOffsetTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOtoPendingPegOffsetTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOtoPendingPegOffsetTypeEnum value);

enum class OrderListPlaceOtoPendingPegPriceTypeEnum {
    PrimaryPeg,
    MarketPeg,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOtoPendingPegPriceTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOtoPendingPegPriceTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOtoPendingPegPriceTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOtoPendingPegPriceTypeEnum value);

enum class OrderListPlaceOtocoWorkingTypeEnum {
    Limit,
    LimitMaker,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOtocoWorkingTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOtocoWorkingTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOtocoWorkingTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOtocoWorkingTypeEnum value);

enum class OrderListPlaceOtocoWorkingSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOtocoWorkingSideEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOtocoWorkingSideEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOtocoWorkingSideEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOtocoWorkingSideEnum value);

enum class OrderListPlaceOtocoPendingSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOtocoPendingSideEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOtocoPendingSideEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOtocoPendingSideEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOtocoPendingSideEnum value);

enum class OrderListPlaceOtocoPendingAboveTypeEnum {
    StopLossLimit,
    StopLoss,
    LimitMaker,
    TakeProfit,
    TakeProfitLimit,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOtocoPendingAboveTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOtocoPendingAboveTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOtocoPendingAboveTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOtocoPendingAboveTypeEnum value);

enum class OrderListPlaceOtocoNewOrderRespTypeEnum {
    Ack,
    Result,
    Full,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOtocoNewOrderRespTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOtocoNewOrderRespTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOtocoNewOrderRespTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOtocoNewOrderRespTypeEnum value);

enum class OrderListPlaceOtocoSelfTradePreventionModeEnum {
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
to_string(OrderListPlaceOtocoSelfTradePreventionModeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOtocoSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOtocoSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOtocoSelfTradePreventionModeEnum value);

enum class OrderListPlaceOtocoWorkingTimeInForceEnum {
    Gtc,
    Ioc,
    Fok,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOtocoWorkingTimeInForceEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOtocoWorkingTimeInForceEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOtocoWorkingTimeInForceEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOtocoWorkingTimeInForceEnum value);

enum class OrderListPlaceOtocoWorkingPegPriceTypeEnum {
    PrimaryPeg,
    MarketPeg,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOtocoWorkingPegPriceTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOtocoWorkingPegPriceTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOtocoWorkingPegPriceTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOtocoWorkingPegPriceTypeEnum value);

enum class OrderListPlaceOtocoWorkingPegOffsetTypeEnum {
    PriceLevel,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOtocoWorkingPegOffsetTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOtocoWorkingPegOffsetTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOtocoWorkingPegOffsetTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOtocoWorkingPegOffsetTypeEnum value);

enum class OrderListPlaceOtocoPendingAboveTimeInForceEnum {
    Gtc,
    Ioc,
    Fok,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOtocoPendingAboveTimeInForceEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOtocoPendingAboveTimeInForceEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOtocoPendingAboveTimeInForceEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOtocoPendingAboveTimeInForceEnum value);

enum class OrderListPlaceOtocoPendingAbovePegPriceTypeEnum {
    PrimaryPeg,
    MarketPeg,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOtocoPendingAbovePegPriceTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOtocoPendingAbovePegPriceTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOtocoPendingAbovePegPriceTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOtocoPendingAbovePegPriceTypeEnum value);

enum class OrderListPlaceOtocoPendingAbovePegOffsetTypeEnum {
    PriceLevel,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOtocoPendingAbovePegOffsetTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOtocoPendingAbovePegOffsetTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOtocoPendingAbovePegOffsetTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOtocoPendingAbovePegOffsetTypeEnum value);

enum class OrderListPlaceOtocoPendingBelowTypeEnum {
    StopLoss,
    StopLossLimit,
    TakeProfit,
    TakeProfitLimit,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOtocoPendingBelowTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOtocoPendingBelowTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOtocoPendingBelowTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOtocoPendingBelowTypeEnum value);

enum class OrderListPlaceOtocoPendingBelowTimeInForceEnum {
    Gtc,
    Ioc,
    Fok,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOtocoPendingBelowTimeInForceEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOtocoPendingBelowTimeInForceEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOtocoPendingBelowTimeInForceEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOtocoPendingBelowTimeInForceEnum value);

enum class OrderListPlaceOtocoPendingBelowPegPriceTypeEnum {
    PrimaryPeg,
    MarketPeg,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOtocoPendingBelowPegPriceTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOtocoPendingBelowPegPriceTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOtocoPendingBelowPegPriceTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOtocoPendingBelowPegPriceTypeEnum value);

enum class OrderListPlaceOtocoPendingBelowPegOffsetTypeEnum {
    PriceLevel,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderListPlaceOtocoPendingBelowPegOffsetTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderListPlaceOtocoPendingBelowPegOffsetTypeEnum
tag_invoke(boost::json::value_to_tag<OrderListPlaceOtocoPendingBelowPegOffsetTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderListPlaceOtocoPendingBelowPegOffsetTypeEnum value);

enum class OrderPlaceSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view to_string(OrderPlaceSideEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderPlaceSideEnum
tag_invoke(boost::json::value_to_tag<OrderPlaceSideEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderPlaceSideEnum value);

enum class OrderPlaceTypeEnum {
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

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view to_string(OrderPlaceTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderPlaceTypeEnum
tag_invoke(boost::json::value_to_tag<OrderPlaceTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderPlaceTypeEnum value);

enum class OrderPlaceTimeInForceEnum {
    Gtc,
    Ioc,
    Fok,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderPlaceTimeInForceEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderPlaceTimeInForceEnum tag_invoke(
    boost::json::value_to_tag<OrderPlaceTimeInForceEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderPlaceTimeInForceEnum value);

enum class OrderPlaceNewOrderRespTypeEnum {
    Ack,
    Result,
    Full,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderPlaceNewOrderRespTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderPlaceNewOrderRespTypeEnum
tag_invoke(boost::json::value_to_tag<OrderPlaceNewOrderRespTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderPlaceNewOrderRespTypeEnum value);

enum class OrderPlaceSelfTradePreventionModeEnum {
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
to_string(OrderPlaceSelfTradePreventionModeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderPlaceSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<OrderPlaceSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderPlaceSelfTradePreventionModeEnum value);

enum class OrderPlacePegPriceTypeEnum {
    PrimaryPeg,
    MarketPeg,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderPlacePegPriceTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderPlacePegPriceTypeEnum tag_invoke(
    boost::json::value_to_tag<OrderPlacePegPriceTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderPlacePegPriceTypeEnum value);

enum class OrderPlacePegOffsetTypeEnum {
    PriceLevel,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(OrderPlacePegOffsetTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT OrderPlacePegOffsetTypeEnum tag_invoke(
    boost::json::value_to_tag<OrderPlacePegOffsetTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    OrderPlacePegOffsetTypeEnum value);

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

enum class SorOrderPlaceSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view to_string(SorOrderPlaceSideEnum value) noexcept;
BINANCE_SPOT_EXPORT SorOrderPlaceSideEnum
tag_invoke(boost::json::value_to_tag<SorOrderPlaceSideEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    SorOrderPlaceSideEnum value);

enum class SorOrderPlaceTypeEnum {
    Market,
    Limit,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view to_string(SorOrderPlaceTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT SorOrderPlaceTypeEnum
tag_invoke(boost::json::value_to_tag<SorOrderPlaceTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    SorOrderPlaceTypeEnum value);

enum class SorOrderPlaceTimeInForceEnum {
    Gtc,
    Ioc,
    Fok,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(SorOrderPlaceTimeInForceEnum value) noexcept;
BINANCE_SPOT_EXPORT SorOrderPlaceTimeInForceEnum tag_invoke(
    boost::json::value_to_tag<SorOrderPlaceTimeInForceEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    SorOrderPlaceTimeInForceEnum value);

enum class SorOrderPlaceNewOrderRespTypeEnum {
    Ack,
    Result,
    Full,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(SorOrderPlaceNewOrderRespTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT SorOrderPlaceNewOrderRespTypeEnum
tag_invoke(boost::json::value_to_tag<SorOrderPlaceNewOrderRespTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    SorOrderPlaceNewOrderRespTypeEnum value);

enum class SorOrderPlaceSelfTradePreventionModeEnum {
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
to_string(SorOrderPlaceSelfTradePreventionModeEnum value) noexcept;
BINANCE_SPOT_EXPORT SorOrderPlaceSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<SorOrderPlaceSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    SorOrderPlaceSelfTradePreventionModeEnum value);

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

struct OpenOrdersCancelAllParams {
    common::Required<std::string> symbol;
    /// Client-generated request identifier.
    std::optional<std::string> id = std::nullopt;
    /// Supports up to three decimal places of precision (e.g., 6000.346) so that microseconds may
    /// be specified.
    std::optional<common::Decimal> recv_window = std::nullopt;
};

struct OrderAmendKeepPriorityParams {
    common::Required<std::string> symbol;
    /// `newQty` must be greater than 0 and less than the order's quantity.
    common::Required<common::Decimal> new_qty;
    /// Client-generated request identifier.
    std::optional<std::string> id = std::nullopt;
    /// `orderId` or `origClientOrderId` must be sent
    std::optional<std::int64_t> order_id = std::nullopt;
    /// `orderId` or `origClientOrderId` must be sent
    std::optional<std::string> orig_client_order_id = std::nullopt;
    /// The new client order ID for the order after being amended.
    /// If not sent, one will be randomly generated.
    /// It is possible to reuse the current clientOrderId by sending it as the `newClientOrderId`.
    std::optional<std::string> new_client_order_id = std::nullopt;
    /// Supports up to three decimal places of precision (e.g., 6000.346) so that microseconds may
    /// be specified.
    std::optional<common::Decimal> recv_window = std::nullopt;
};

struct OrderCancelParams {
    common::Required<std::string> symbol;
    /// Client-generated request identifier.
    std::optional<std::string> id = std::nullopt;
    std::optional<std::int64_t> order_id = std::nullopt;
    std::optional<std::string> orig_client_order_id = std::nullopt;
    /// Used to uniquely identify this cancel. Automatically generated by default.
    std::optional<std::string> new_client_order_id = std::nullopt;
    /// Supported values:
    /// `ONLY_NEW` - Cancel will succeed if the order status is `NEW`.
    /// `ONLY_PARTIALLY_FILLED` - Cancel will succeed if order status is `PARTIALLY_FILLED`. For
    /// more information please refer to Regarding `cancelRestrictions`.
    std::optional<OrderCancelCancelRestrictionsEnum> cancel_restrictions = std::nullopt;
    /// Supports up to three decimal places of precision (e.g., 6000.346) so that microseconds may
    /// be specified.
    std::optional<common::Decimal> recv_window = std::nullopt;
};

struct OrderCancelReplaceParams {
    common::Required<std::string> symbol;
    /// The allowed values are:
    /// `STOP_ON_FAILURE` - If the cancel request fails, the new order placement will not be
    /// attempted. `ALLOW_FAILURE` - new order placement will be attempted even if cancel request
    /// fails.
    common::Required<OrderCancelReplaceCancelReplaceModeEnum> cancel_replace_mode;
    common::Required<OrderCancelReplaceSideEnum> side;
    common::Required<OrderCancelReplaceTypeEnum> type;
    /// Client-generated request identifier.
    std::optional<std::string> id = std::nullopt;
    /// Either `cancelOrderId` or `cancelOrigClientOrderId` must be sent.
    ///
    /// If both `cancelOrderId` and `cancelOrigClientOrderId` parameters are provided, the
    /// `cancelOrderId` is searched first, then the `cancelOrigClientOrderId` from that result is
    /// checked against that order.
    ///
    /// If both conditions are not met the request will be rejected.
    std::optional<std::int64_t> cancel_order_id = std::nullopt;
    /// Either `cancelOrderId` or `cancelOrigClientOrderId` must be sent.
    ///
    /// If both `cancelOrderId` and `cancelOrigClientOrderId` parameters are provided, the
    /// `cancelOrderId` is searched first, then the `cancelOrigClientOrderId` from that result is
    /// checked against that order.
    ///
    /// If both conditions are not met the request will be rejected.
    std::optional<std::string> cancel_orig_client_order_id = std::nullopt;
    /// Used to uniquely identify this cancel. Automatically generated by default.
    std::optional<std::string> cancel_new_client_order_id = std::nullopt;
    std::optional<OrderCancelReplaceTimeInForceEnum> time_in_force = std::nullopt;
    std::optional<common::Decimal> price = std::nullopt;
    std::optional<common::Decimal> quantity = std::nullopt;
    std::optional<common::Decimal> quote_order_qty = std::nullopt;
    /// Used to identify the new order.
    std::optional<std::string> new_client_order_id = std::nullopt;
    /// Allowed values:
    /// `ACK`, `RESULT`, `FULL`
    /// `MARKET` and `LIMIT` orders types default to `FULL`; all other orders default to `ACK`
    std::optional<OrderCancelReplaceNewOrderRespTypeEnum> new_order_resp_type = std::nullopt;
    /// Used with `STOP_LOSS`, `STOP_LOSS_LIMIT`, `TAKE_PROFIT`, and `TAKE_PROFIT_LIMIT` orders.
    std::optional<common::Decimal> stop_price = std::nullopt;
    /// See Trailing Stop order FAQ
    std::optional<common::Decimal> trailing_delta = std::nullopt;
    /// Used with `LIMIT`, `STOP_LOSS_LIMIT`, and `TAKE_PROFIT_LIMIT` to create an iceberg order.
    std::optional<common::Decimal> iceberg_qty = std::nullopt;
    std::optional<std::int64_t> strategy_id = std::nullopt;
    /// The value cannot be less than `1000000`.
    std::optional<std::int64_t> strategy_type = std::nullopt;
    /// The allowed enums is dependent on what is configured on the symbol. The possible supported
    /// values are: STP Modes.
    std::optional<OrderCancelReplaceSelfTradePreventionModeEnum> self_trade_prevention_mode =
        std::nullopt;
    /// Supported values:
    /// `ONLY_NEW` - Cancel will succeed if the order status is `NEW`.
    /// `ONLY_PARTIALLY_FILLED` - Cancel will succeed if order status is `PARTIALLY_FILLED`. For
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
    /// See Pegged Orders
    std::optional<OrderCancelReplacePegOffsetTypeEnum> peg_offset_type = std::nullopt;
    /// For replacement orders on the BUY side only. Maximum quote-asset notional the replacement
    /// order may consume. See Quote Notional Limit.
    std::optional<common::Decimal> quote_notional_limit = std::nullopt;
    /// Supports up to three decimal places of precision (e.g., 6000.346) so that microseconds may
    /// be specified.
    std::optional<common::Decimal> recv_window = std::nullopt;
};

struct OrderListCancelParams {
    common::Required<std::string> symbol;
    /// Client-generated request identifier.
    std::optional<std::string> id = std::nullopt;
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

struct OrderListPlaceParams {
    common::Required<std::string> symbol;
    common::Required<OrderListPlaceSideEnum> side;
    common::Required<common::Decimal> price;
    common::Required<common::Decimal> quantity;
    /// Client-generated request identifier.
    std::optional<std::string> id = std::nullopt;
    /// A unique Id for the entire orderList
    std::optional<std::string> list_client_order_id = std::nullopt;
    /// A unique Id for the limit order
    std::optional<std::string> limit_client_order_id = std::nullopt;
    /// Used to make the `LIMIT_MAKER` leg an iceberg order.
    std::optional<common::Decimal> limit_iceberg_qty = std::nullopt;
    std::optional<std::int64_t> limit_strategy_id = std::nullopt;
    /// The value cannot be less than `1000000`.
    std::optional<std::int64_t> limit_strategy_type = std::nullopt;
    std::optional<common::Decimal> stop_price = std::nullopt;
    std::optional<std::int64_t> trailing_delta = std::nullopt;
    /// A unique Id for the stop loss/stop loss limit leg
    std::optional<std::string> stop_client_order_id = std::nullopt;
    /// If provided, `stopLimitTimeInForce` is required.
    std::optional<common::Decimal> stop_limit_price = std::nullopt;
    /// Valid values are `GTC`/`FOK`/`IOC`
    std::optional<OrderListPlaceStopLimitTimeInForceEnum> stop_limit_time_in_force = std::nullopt;
    /// Used with `STOP_LOSS_LIMIT` leg to make an iceberg order.
    std::optional<common::Decimal> stop_iceberg_qty = std::nullopt;
    std::optional<std::int64_t> stop_strategy_id = std::nullopt;
    /// The value cannot be less than `1000000`.
    std::optional<std::int64_t> stop_strategy_type = std::nullopt;
    /// Format of the JSON response. Supported values: Order Response Type
    std::optional<OrderListPlaceNewOrderRespTypeEnum> new_order_resp_type = std::nullopt;
    /// The allowed values are dependent on what is configured on the symbol. Supported values: STP
    /// Modes
    std::optional<OrderListPlaceSelfTradePreventionModeEnum> self_trade_prevention_mode =
        std::nullopt;
    /// Supports up to three decimal places of precision (e.g., 6000.346) so that microseconds may
    /// be specified.
    std::optional<common::Decimal> recv_window = std::nullopt;
};

struct OrderListPlaceOcoParams {
    common::Required<std::string> symbol;
    /// `BUY` or `SELL`
    common::Required<OrderListPlaceOcoSideEnum> side;
    /// Quantity for both orders of the order list.
    common::Required<common::Decimal> quantity;
    common::Required<OrderListPlaceOcoAboveTypeEnum> above_type;
    /// Supported values: `STOP_LOSS`, `STOP_LOSS_LIMIT`, `TAKE_PROFIT`, `TAKE_PROFIT_LIMIT`
    common::Required<OrderListPlaceOcoBelowTypeEnum> below_type;
    /// Client-generated request identifier.
    std::optional<std::string> id = std::nullopt;
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
    std::optional<OrderListPlaceOcoAboveTimeInForceEnum> above_time_in_force = std::nullopt;
    /// Arbitrary numeric value identifying the above order within an order strategy.
    std::optional<std::int64_t> above_strategy_id = std::nullopt;
    /// Arbitrary numeric value identifying the above order strategy. Values smaller than `1000000`
    /// are reserved and cannot be used.
    std::optional<std::int64_t> above_strategy_type = std::nullopt;
    /// `PRIMARY_PEG` or `MARKET_PEG`. See Pegged Orders
    std::optional<OrderListPlaceOcoAbovePegPriceTypeEnum> above_peg_price_type = std::nullopt;
    std::optional<OrderListPlaceOcoAbovePegOffsetTypeEnum> above_peg_offset_type = std::nullopt;
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
    std::optional<OrderListPlaceOcoBelowTimeInForceEnum> below_time_in_force = std::nullopt;
    /// Arbitrary numeric value identifying the below order within an order strategy.
    std::optional<std::int64_t> below_strategy_id = std::nullopt;
    /// Arbitrary numeric value identifying the below order strategy. Values smaller than `1000000`
    /// are reserved and cannot be used.
    std::optional<std::int64_t> below_strategy_type = std::nullopt;
    /// See Pegged Orders
    std::optional<OrderListPlaceOcoBelowPegPriceTypeEnum> below_peg_price_type = std::nullopt;
    std::optional<OrderListPlaceOcoBelowPegOffsetTypeEnum> below_peg_offset_type = std::nullopt;
    std::optional<std::int64_t> below_peg_offset_value = std::nullopt;
    /// Select response format: `ACK`, `RESULT`, `FULL`.
    std::optional<OrderListPlaceOcoNewOrderRespTypeEnum> new_order_resp_type = std::nullopt;
    /// The allowed enums is dependent on what is configured on the symbol. Supported values: STP
    /// Modes
    std::optional<OrderListPlaceOcoSelfTradePreventionModeEnum> self_trade_prevention_mode =
        std::nullopt;
    /// Quote notional limit for the above order (only for orders on the BUY side). See Quote
    /// Notional Limit.
    std::optional<common::Decimal> above_quote_notional_limit = std::nullopt;
    /// Quote notional limit for the below order (only for orders on the BUY side). See Quote
    /// Notional Limit.
    std::optional<common::Decimal> below_quote_notional_limit = std::nullopt;
    /// Supports up to three decimal places of precision (e.g., 6000.346) so that microseconds may
    /// be specified.
    std::optional<common::Decimal> recv_window = std::nullopt;
};

struct OrderListPlaceOpoParams {
    common::Required<std::string> symbol;
    /// Supported values: `LIMIT`, `LIMIT_MAKER`
    common::Required<OrderListPlaceOpoWorkingTypeEnum> working_type;
    /// Supported values: Order Side
    common::Required<OrderListPlaceOpoWorkingSideEnum> working_side;
    /// Price for the working order.
    common::Required<common::Decimal> working_price;
    /// Sets the quantity for the working order.
    common::Required<common::Decimal> working_quantity;
    /// Supported values: Order Types. Note that `MARKET` orders using `quoteOrderQty` are not
    /// supported.
    common::Required<OrderListPlaceOpoPendingTypeEnum> pending_type;
    /// Supported values: Order Side
    common::Required<OrderListPlaceOpoPendingSideEnum> pending_side;
    /// Client-generated request identifier.
    std::optional<std::string> id = std::nullopt;
    /// Arbitrary unique ID among open order lists. Automatically generated if not sent. A new order
    /// list with the same `listClientOrderId` is accepted only when the previous one is filled or
    /// completely expired. `listClientOrderId` is distinct from the `workingClientOrderId` and the
    /// `pendingClientOrderId`.
    std::optional<std::string> list_client_order_id = std::nullopt;
    /// Format of the JSON response. Supported values: Order Response Type
    std::optional<OrderListPlaceOpoNewOrderRespTypeEnum> new_order_resp_type = std::nullopt;
    /// The allowed enums is dependent on what is configured on the symbol. Supported values: STP
    /// Modes
    std::optional<OrderListPlaceOpoSelfTradePreventionModeEnum> self_trade_prevention_mode =
        std::nullopt;
    /// Arbitrary unique ID among open orders for the working order. Automatically generated if not
    /// sent.
    std::optional<std::string> working_client_order_id = std::nullopt;
    /// This can only be used if `workingTimeInForce` is `GTC`, or if `workingType` is
    /// `LIMIT_MAKER`.
    std::optional<common::Decimal> working_iceberg_qty = std::nullopt;
    /// Supported values: Time In Force
    std::optional<OrderListPlaceOpoWorkingTimeInForceEnum> working_time_in_force = std::nullopt;
    /// Arbitrary numeric value identifying the working order within an order strategy.
    std::optional<std::int64_t> working_strategy_id = std::nullopt;
    /// Arbitrary numeric value identifying the working order strategy. Values smaller than
    /// `1000000` are reserved and cannot be used.
    std::optional<std::int64_t> working_strategy_type = std::nullopt;
    /// See Pegged Orders
    std::optional<OrderListPlaceOpoWorkingPegPriceTypeEnum> working_peg_price_type = std::nullopt;
    std::optional<OrderListPlaceOpoWorkingPegOffsetTypeEnum> working_peg_offset_type = std::nullopt;
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
    std::optional<OrderListPlaceOpoPendingTimeInForceEnum> pending_time_in_force = std::nullopt;
    /// Arbitrary numeric value identifying the pending order within an order strategy.
    std::optional<std::int64_t> pending_strategy_id = std::nullopt;
    /// Arbitrary numeric value identifying the pending order strategy. Values smaller than
    /// `1000000` are reserved and cannot be used.
    std::optional<std::int64_t> pending_strategy_type = std::nullopt;
    /// See Pegged Orders
    std::optional<OrderListPlaceOpoPendingPegPriceTypeEnum> pending_peg_price_type = std::nullopt;
    std::optional<OrderListPlaceOpoPendingPegOffsetTypeEnum> pending_peg_offset_type = std::nullopt;
    std::optional<std::int64_t> pending_peg_offset_value = std::nullopt;
    /// Quote notional limit for the working LIMIT order on the BUY side. See Quote Notional Limit.
    std::optional<common::Decimal> working_quote_notional_limit = std::nullopt;
    /// Supports up to three decimal places of precision (e.g., 6000.346) so that microseconds may
    /// be specified.
    std::optional<common::Decimal> recv_window = std::nullopt;
};

struct OrderListPlaceOpocoParams {
    common::Required<std::string> symbol;
    /// Supported values: `LIMIT`, `LIMIT_MAKER`
    common::Required<OrderListPlaceOpocoWorkingTypeEnum> working_type;
    /// Supported values: Order Side
    common::Required<OrderListPlaceOpocoWorkingSideEnum> working_side;
    /// Price for the working order.
    common::Required<common::Decimal> working_price;
    /// Sets the quantity for the working order.
    common::Required<common::Decimal> working_quantity;
    /// Supported values: Order Side
    common::Required<OrderListPlaceOpocoPendingSideEnum> pending_side;
    /// Supported values: `STOP_LOSS_LIMIT`, `STOP_LOSS`, `LIMIT_MAKER`, `TAKE_PROFIT`,
    /// `TAKE_PROFIT_LIMIT`
    common::Required<OrderListPlaceOpocoPendingAboveTypeEnum> pending_above_type;
    /// Client-generated request identifier.
    std::optional<std::string> id = std::nullopt;
    /// Arbitrary unique ID among open order lists. Automatically generated if not sent. A new order
    /// list with the same `listClientOrderId` is accepted only when the previous one is filled or
    /// completely expired. `listClientOrderId` is distinct from the `workingClientOrderId`,
    /// `pendingAboveClientOrderId`, and the `pendingBelowClientOrderId`.
    std::optional<std::string> list_client_order_id = std::nullopt;
    /// Format of the JSON response. Supported values: Order Response Type
    std::optional<OrderListPlaceOpocoNewOrderRespTypeEnum> new_order_resp_type = std::nullopt;
    /// The allowed enums is dependent on what is configured on the symbol. Supported values: STP
    /// Modes
    std::optional<OrderListPlaceOpocoSelfTradePreventionModeEnum> self_trade_prevention_mode =
        std::nullopt;
    /// Arbitrary unique ID among open orders for the working order. Automatically generated if not
    /// sent.
    std::optional<std::string> working_client_order_id = std::nullopt;
    /// This can only be used if `workingTimeInForce` is `GTC`, or if `workingType` is
    /// `LIMIT_MAKER`.
    std::optional<common::Decimal> working_iceberg_qty = std::nullopt;
    /// Supported values: Time In Force
    std::optional<OrderListPlaceOpocoWorkingTimeInForceEnum> working_time_in_force = std::nullopt;
    /// Arbitrary numeric value identifying the working order within an order strategy.
    std::optional<std::int64_t> working_strategy_id = std::nullopt;
    /// Arbitrary numeric value identifying the working order strategy. Values smaller than
    /// `1000000` are reserved and cannot be used.
    std::optional<std::int64_t> working_strategy_type = std::nullopt;
    /// See Pegged Orders
    std::optional<OrderListPlaceOpocoWorkingPegPriceTypeEnum> working_peg_price_type = std::nullopt;
    /// See Pegged Orders
    std::optional<OrderListPlaceOpocoWorkingPegOffsetTypeEnum> working_peg_offset_type =
        std::nullopt;
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
    std::optional<OrderListPlaceOpocoPendingAboveTimeInForceEnum> pending_above_time_in_force =
        std::nullopt;
    /// Arbitrary numeric value identifying the pending above order within an order strategy.
    std::optional<std::int64_t> pending_above_strategy_id = std::nullopt;
    /// Arbitrary numeric value identifying the pending above order strategy. Values smaller than
    /// `1000000` are reserved and cannot be used.
    std::optional<std::int64_t> pending_above_strategy_type = std::nullopt;
    /// See Pegged Orders
    std::optional<OrderListPlaceOpocoPendingAbovePegPriceTypeEnum> pending_above_peg_price_type =
        std::nullopt;
    /// See Pegged Orders
    std::optional<OrderListPlaceOpocoPendingAbovePegOffsetTypeEnum> pending_above_peg_offset_type =
        std::nullopt;
    /// Price level for pegging (max: 100). See Pegged Orders
    std::optional<std::int64_t> pending_above_peg_offset_value = std::nullopt;
    /// Supported values: `STOP_LOSS`, `STOP_LOSS_LIMIT`, `TAKE_PROFIT`, `TAKE_PROFIT_LIMIT`
    std::optional<OrderListPlaceOpocoPendingBelowTypeEnum> pending_below_type = std::nullopt;
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
    std::optional<OrderListPlaceOpocoPendingBelowTimeInForceEnum> pending_below_time_in_force =
        std::nullopt;
    /// Arbitrary numeric value identifying the pending below order within an order strategy.
    std::optional<std::int64_t> pending_below_strategy_id = std::nullopt;
    /// Arbitrary numeric value identifying the pending below order strategy. Values smaller than
    /// `1000000` are reserved and cannot be used.
    std::optional<std::int64_t> pending_below_strategy_type = std::nullopt;
    /// See Pegged Orders
    std::optional<OrderListPlaceOpocoPendingBelowPegPriceTypeEnum> pending_below_peg_price_type =
        std::nullopt;
    std::optional<OrderListPlaceOpocoPendingBelowPegOffsetTypeEnum> pending_below_peg_offset_type =
        std::nullopt;
    std::optional<std::int64_t> pending_below_peg_offset_value = std::nullopt;
    /// Quote notional limit for the working LIMIT order on the BUY side. See Quote Notional Limit.
    std::optional<common::Decimal> working_quote_notional_limit = std::nullopt;
    /// Supports up to three decimal places of precision (e.g., 6000.346) so that microseconds may
    /// be specified.
    std::optional<common::Decimal> recv_window = std::nullopt;
};

struct OrderListPlaceOtoParams {
    common::Required<std::string> symbol;
    /// Supported values: `LIMIT`, `LIMIT_MAKER`
    common::Required<OrderListPlaceOtoWorkingTypeEnum> working_type;
    /// Supported values: Order Side
    common::Required<OrderListPlaceOtoWorkingSideEnum> working_side;
    common::Required<common::Decimal> working_price;
    /// Sets the quantity for the working order.
    common::Required<common::Decimal> working_quantity;
    /// Supported values: Order Types. Note that `MARKET` orders using `quoteOrderQty` are not
    /// supported.
    common::Required<OrderListPlaceOtoPendingTypeEnum> pending_type;
    /// Supported values: Order Side
    common::Required<OrderListPlaceOtoPendingSideEnum> pending_side;
    /// Sets the quantity for the pending order.
    common::Required<common::Decimal> pending_quantity;
    /// Client-generated request identifier.
    std::optional<std::string> id = std::nullopt;
    /// Arbitrary unique ID among open order lists. Automatically generated if not sent. A new order
    /// list with the same `listClientOrderId` is accepted only when the previous one is filled or
    /// completely expired. `listClientOrderId` is distinct from the `workingClientOrderId` and the
    /// `pendingClientOrderId`.
    std::optional<std::string> list_client_order_id = std::nullopt;
    /// Format of the JSON response. Supported values: Order Response Type
    std::optional<OrderListPlaceOtoNewOrderRespTypeEnum> new_order_resp_type = std::nullopt;
    /// The allowed enums is dependent on what is configured on the symbol. Supported values: STP
    /// Modes
    std::optional<OrderListPlaceOtoSelfTradePreventionModeEnum> self_trade_prevention_mode =
        std::nullopt;
    /// Arbitrary unique ID among open orders for the working order. Automatically generated if not
    /// sent.
    std::optional<std::string> working_client_order_id = std::nullopt;
    /// This can only be used if `workingTimeInForce` is `GTC`, or if `workingType` is
    /// `LIMIT_MAKER`.
    std::optional<common::Decimal> working_iceberg_qty = std::nullopt;
    /// Supported values: Time In Force
    std::optional<OrderListPlaceOtoWorkingTimeInForceEnum> working_time_in_force = std::nullopt;
    /// Arbitrary numeric value identifying the working order within an order strategy.
    std::optional<std::int64_t> working_strategy_id = std::nullopt;
    /// Arbitrary numeric value identifying the working order strategy. Values smaller than
    /// `1000000` are reserved and cannot be used.
    std::optional<std::int64_t> working_strategy_type = std::nullopt;
    /// See Pegged Orders
    std::optional<OrderListPlaceOtoWorkingPegPriceTypeEnum> working_peg_price_type = std::nullopt;
    std::optional<OrderListPlaceOtoWorkingPegOffsetTypeEnum> working_peg_offset_type = std::nullopt;
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
    std::optional<OrderListPlaceOtoPendingTimeInForceEnum> pending_time_in_force = std::nullopt;
    /// Arbitrary numeric value identifying the pending order within an order strategy.
    std::optional<std::int64_t> pending_strategy_id = std::nullopt;
    /// Arbitrary numeric value identifying the pending order strategy. Values smaller than
    /// `1000000` are reserved and cannot be used.
    std::optional<std::int64_t> pending_strategy_type = std::nullopt;
    std::optional<OrderListPlaceOtoPendingPegOffsetTypeEnum> pending_peg_offset_type = std::nullopt;
    /// See Pegged Orders
    std::optional<OrderListPlaceOtoPendingPegPriceTypeEnum> pending_peg_price_type = std::nullopt;
    std::optional<std::int64_t> pending_peg_offset_value = std::nullopt;
    /// Quote notional limit for the working order (only for orders on the BUY side). See Quote
    /// Notional Limit.
    std::optional<common::Decimal> working_quote_notional_limit = std::nullopt;
    /// Quote notional limit for the pending order (only for orders on the BUY side). See Quote
    /// Notional Limit.
    std::optional<common::Decimal> pending_quote_notional_limit = std::nullopt;
    /// Supports up to three decimal places of precision (e.g., 6000.346) so that microseconds may
    /// be specified.
    std::optional<common::Decimal> recv_window = std::nullopt;
};

struct OrderListPlaceOtocoParams {
    common::Required<std::string> symbol;
    /// Supported values: `LIMIT`, `LIMIT_MAKER`
    common::Required<OrderListPlaceOtocoWorkingTypeEnum> working_type;
    /// Supported values: Order Side
    common::Required<OrderListPlaceOtocoWorkingSideEnum> working_side;
    common::Required<common::Decimal> working_price;
    /// Sets the quantity for the working order.
    common::Required<common::Decimal> working_quantity;
    /// Supported values: Order Side
    common::Required<OrderListPlaceOtocoPendingSideEnum> pending_side;
    /// Sets the quantity for the pending orders.
    common::Required<common::Decimal> pending_quantity;
    /// Supported values: `STOP_LOSS_LIMIT`, `STOP_LOSS`, `LIMIT_MAKER`, `TAKE_PROFIT`,
    /// `TAKE_PROFIT_LIMIT`
    common::Required<OrderListPlaceOtocoPendingAboveTypeEnum> pending_above_type;
    /// Client-generated request identifier.
    std::optional<std::string> id = std::nullopt;
    /// Arbitrary unique ID among open order lists. Automatically generated if not sent. A new order
    /// list with the same `listClientOrderId` is accepted only when the previous one is filled or
    /// completely expired. `listClientOrderId` is distinct from the `workingClientOrderId`,
    /// `pendingAboveClientOrderId`, and the `pendingBelowClientOrderId`.
    std::optional<std::string> list_client_order_id = std::nullopt;
    /// Format of the JSON response. Supported values: Order Response Type
    std::optional<OrderListPlaceOtocoNewOrderRespTypeEnum> new_order_resp_type = std::nullopt;
    /// The allowed enums is dependent on what is configured on the symbol. Supported values: STP
    /// Modes
    std::optional<OrderListPlaceOtocoSelfTradePreventionModeEnum> self_trade_prevention_mode =
        std::nullopt;
    /// Arbitrary unique ID among open orders for the working order. Automatically generated if not
    /// sent.
    std::optional<std::string> working_client_order_id = std::nullopt;
    /// This can only be used if `workingTimeInForce` is `GTC`, or if `workingType` is
    /// `LIMIT_MAKER`.
    std::optional<common::Decimal> working_iceberg_qty = std::nullopt;
    /// Supported values: Time In Force
    std::optional<OrderListPlaceOtocoWorkingTimeInForceEnum> working_time_in_force = std::nullopt;
    /// Arbitrary numeric value identifying the working order within an order strategy.
    std::optional<std::int64_t> working_strategy_id = std::nullopt;
    /// Arbitrary numeric value identifying the working order strategy. Values smaller than
    /// `1000000` are reserved and cannot be used.
    std::optional<std::int64_t> working_strategy_type = std::nullopt;
    /// See Pegged Orders
    std::optional<OrderListPlaceOtocoWorkingPegPriceTypeEnum> working_peg_price_type = std::nullopt;
    std::optional<OrderListPlaceOtocoWorkingPegOffsetTypeEnum> working_peg_offset_type =
        std::nullopt;
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
    std::optional<OrderListPlaceOtocoPendingAboveTimeInForceEnum> pending_above_time_in_force =
        std::nullopt;
    /// Arbitrary numeric value identifying the pending above order within an order strategy.
    std::optional<std::int64_t> pending_above_strategy_id = std::nullopt;
    /// Arbitrary numeric value identifying the pending above order strategy. Values smaller than
    /// `1000000` are reserved and cannot be used.
    std::optional<std::int64_t> pending_above_strategy_type = std::nullopt;
    /// See Pegged Orders
    std::optional<OrderListPlaceOtocoPendingAbovePegPriceTypeEnum> pending_above_peg_price_type =
        std::nullopt;
    std::optional<OrderListPlaceOtocoPendingAbovePegOffsetTypeEnum> pending_above_peg_offset_type =
        std::nullopt;
    std::optional<std::int64_t> pending_above_peg_offset_value = std::nullopt;
    /// Supported values: `STOP_LOSS`, `STOP_LOSS_LIMIT`, `TAKE_PROFIT`, `TAKE_PROFIT_LIMIT`
    std::optional<OrderListPlaceOtocoPendingBelowTypeEnum> pending_below_type = std::nullopt;
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
    std::optional<OrderListPlaceOtocoPendingBelowTimeInForceEnum> pending_below_time_in_force =
        std::nullopt;
    /// Arbitrary numeric value identifying the pending below order within an order strategy.
    std::optional<std::int64_t> pending_below_strategy_id = std::nullopt;
    /// Arbitrary numeric value identifying the pending below order strategy. Values smaller than
    /// `1000000` are reserved and cannot be used.
    std::optional<std::int64_t> pending_below_strategy_type = std::nullopt;
    /// See Pegged Orders
    std::optional<OrderListPlaceOtocoPendingBelowPegPriceTypeEnum> pending_below_peg_price_type =
        std::nullopt;
    std::optional<OrderListPlaceOtocoPendingBelowPegOffsetTypeEnum> pending_below_peg_offset_type =
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
    /// Supports up to three decimal places of precision (e.g., 6000.346) so that microseconds may
    /// be specified.
    std::optional<common::Decimal> recv_window = std::nullopt;
};

struct OrderPlaceParams {
    common::Required<std::string> symbol;
    common::Required<OrderPlaceSideEnum> side;
    common::Required<OrderPlaceTypeEnum> type;
    /// Client-generated request identifier.
    std::optional<std::string> id = std::nullopt;
    std::optional<OrderPlaceTimeInForceEnum> time_in_force = std::nullopt;
    std::optional<common::Decimal> price = std::nullopt;
    std::optional<common::Decimal> quantity = std::nullopt;
    std::optional<common::Decimal> quote_order_qty = std::nullopt;
    /// A unique id among open orders. Automatically generated if not sent.
    /// Orders with the same `newClientOrderID` can be accepted only when the previous one is
    /// filled, otherwise the order will be rejected.
    std::optional<std::string> new_client_order_id = std::nullopt;
    /// `MARKET` and `LIMIT` order types default to `FULL`, all other orders default to `ACK`.
    std::optional<OrderPlaceNewOrderRespTypeEnum> new_order_resp_type = std::nullopt;
    /// Used with `STOP_LOSS`, `STOP_LOSS_LIMIT`, `TAKE_PROFIT`, and `TAKE_PROFIT_LIMIT` orders.
    std::optional<common::Decimal> stop_price = std::nullopt;
    /// See Trailing Stop order FAQ
    std::optional<std::int64_t> trailing_delta = std::nullopt;
    /// Used with `LIMIT`, `STOP_LOSS_LIMIT`, and `TAKE_PROFIT_LIMIT` to create an iceberg order.
    std::optional<common::Decimal> iceberg_qty = std::nullopt;
    std::optional<std::int64_t> strategy_id = std::nullopt;
    /// The value cannot be less than `1000000`.
    std::optional<std::int64_t> strategy_type = std::nullopt;
    /// The allowed enums is dependent on what is configured on the symbol.
    std::optional<OrderPlaceSelfTradePreventionModeEnum> self_trade_prevention_mode = std::nullopt;
    /// See Pegged Orders Info
    std::optional<OrderPlacePegPriceTypeEnum> peg_price_type = std::nullopt;
    /// Price level to peg the price to (max: 100). See Pegged Orders Info
    std::optional<std::int64_t> peg_offset_value = std::nullopt;
    /// Only `PRICE_LEVEL` is supported. See Pegged Orders Info
    std::optional<OrderPlacePegOffsetTypeEnum> peg_offset_type = std::nullopt;
    /// For orders on the BUY side only. Maximum quote-asset notional the order may consume. See
    /// Quote Notional Limit.
    std::optional<common::Decimal> quote_notional_limit = std::nullopt;
    /// Supports up to three decimal places of precision (e.g., 6000.346) so that microseconds may
    /// be specified.
    std::optional<common::Decimal> recv_window = std::nullopt;
};

struct OrderTestParams {
    common::Required<std::string> symbol;
    common::Required<OrderTestSideEnum> side;
    common::Required<OrderTestTypeEnum> type;
    /// Client-generated request identifier.
    std::optional<std::string> id = std::nullopt;
    /// Default: `false`
    /// See Commissions FAQ to learn more.
    std::optional<bool> compute_commission_rates = std::nullopt;
    std::optional<OrderTestTimeInForceEnum> time_in_force = std::nullopt;
    std::optional<common::Decimal> price = std::nullopt;
    std::optional<common::Decimal> quantity = std::nullopt;
    std::optional<common::Decimal> quote_order_qty = std::nullopt;
    /// A unique id among open orders. Automatically generated if not sent. Orders with the same
    /// `newClientOrderID` can be accepted only when the previous one is filled, otherwise the order
    /// will be rejected.
    std::optional<std::string> new_client_order_id = std::nullopt;
    /// Set the response JSON. `ACK`, `RESULT`, or `FULL`; `MARKET` and `LIMIT` order types default
    /// to `FULL`, all other orders default to `ACK`.
    std::optional<OrderTestNewOrderRespTypeEnum> new_order_resp_type = std::nullopt;
    /// Used with `STOP_LOSS`, `STOP_LOSS_LIMIT`, `TAKE_PROFIT`, and `TAKE_PROFIT_LIMIT` orders.
    std::optional<common::Decimal> stop_price = std::nullopt;
    /// See Trailing Stop order FAQ
    std::optional<std::int64_t> trailing_delta = std::nullopt;
    /// Used with `LIMIT`, `STOP_LOSS_LIMIT`, and `TAKE_PROFIT_LIMIT` to create an iceberg order.
    std::optional<common::Decimal> iceberg_qty = std::nullopt;
    std::optional<std::int64_t> strategy_id = std::nullopt;
    /// The value cannot be less than `1000000`.
    std::optional<std::int64_t> strategy_type = std::nullopt;
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
    /// Supports up to three decimal places of precision (e.g., 6000.346) so that microseconds may
    /// be specified.
    std::optional<common::Decimal> recv_window = std::nullopt;
};

struct SorOrderPlaceParams {
    common::Required<std::string> symbol;
    /// `BUY` or `SELL`
    common::Required<SorOrderPlaceSideEnum> side;
    /// Only `LIMIT` and `MARKET` orders are supported.
    common::Required<SorOrderPlaceTypeEnum> type;
    common::Required<common::Decimal> quantity;
    /// Client-generated request identifier.
    std::optional<std::string> id = std::nullopt;
    /// Applicable only to `LIMIT` order type.
    std::optional<SorOrderPlaceTimeInForceEnum> time_in_force = std::nullopt;
    std::optional<common::Decimal> price = std::nullopt;
    /// A unique id among open orders. Automatically generated if not sent.
    /// Orders with the same `newClientOrderID` can be accepted only when the previous one is
    /// filled, otherwise the order will be rejected.
    std::optional<std::string> new_client_order_id = std::nullopt;
    /// Set the response JSON. `ACK`, `RESULT`, or `FULL`. Default to `FULL`
    std::optional<SorOrderPlaceNewOrderRespTypeEnum> new_order_resp_type = std::nullopt;
    /// Used with `LIMIT` to create an iceberg order.
    std::optional<common::Decimal> iceberg_qty = std::nullopt;
    std::optional<std::int64_t> strategy_id = std::nullopt;
    /// The value cannot be less than `1000000`.
    std::optional<std::int64_t> strategy_type = std::nullopt;
    /// The allowed enums is dependent on what is configured on the symbol. The possible supported
    /// values are: STP Modes.
    std::optional<SorOrderPlaceSelfTradePreventionModeEnum> self_trade_prevention_mode =
        std::nullopt;
    /// Supports up to three decimal places of precision (e.g., 6000.346) so that microseconds may
    /// be specified.
    std::optional<common::Decimal> recv_window = std::nullopt;
};

struct SorOrderTestParams {
    common::Required<std::string> symbol;
    common::Required<SorOrderTestSideEnum> side;
    common::Required<SorOrderTestTypeEnum> type;
    common::Required<common::Decimal> quantity;
    /// Client-generated request identifier.
    std::optional<std::string> id = std::nullopt;
    /// Default: `false`
    std::optional<bool> compute_commission_rates = std::nullopt;
    std::optional<SorOrderTestTimeInForceEnum> time_in_force = std::nullopt;
    std::optional<common::Decimal> price = std::nullopt;
    /// A unique id among open orders. Automatically generated if not sent. Orders with the same
    /// `newClientOrderID` can be accepted only when the previous one is filled, otherwise the order
    /// will be rejected.
    std::optional<std::string> new_client_order_id = std::nullopt;
    /// Set the response JSON. `ACK`, `RESULT`, or `FULL`. Default to `FULL`.
    std::optional<SorOrderTestNewOrderRespTypeEnum> new_order_resp_type = std::nullopt;
    /// Used with `LIMIT` to create an iceberg order.
    std::optional<common::Decimal> iceberg_qty = std::nullopt;
    std::optional<std::int64_t> strategy_id = std::nullopt;
    /// The value cannot be less than `1000000`.
    std::optional<std::int64_t> strategy_type = std::nullopt;
    /// The allowed enums is dependent on what is configured on the symbol. Supported values: STP
    /// Modes
    std::optional<SorOrderTestSelfTradePreventionModeEnum> self_trade_prevention_mode =
        std::nullopt;
    /// Supports up to three decimal places of precision (e.g., 6000.346) so that microseconds may
    /// be specified.
    std::optional<common::Decimal> recv_window = std::nullopt;
};

class BINANCE_SPOT_EXPORT TradeApi {
public:
    explicit TradeApi(std::shared_ptr<common::WebsocketApi> client);

    /// Cancel open orders (TRADE)
    ///
    /// `openOrders.cancelAll`.
    ///
    /// Cancel all open orders on a symbol.
    /// This includes orders that are part of an order list.
    ///
    /// Weight(IP): 1
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
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/trade#open-orders-cancel-all
    [[nodiscard]] common::WebsocketApiResponse<std::vector<OpenOrdersCancelAllResponseResultInner>>
    open_orders_cancel_all(const OpenOrdersCancelAllParams& params) const;

    /// Asynchronous `open_orders_cancel_all()`. Completes with
    /// `void(std::exception_ptr,
    /// common::WebsocketApiResponse<std::vector<OpenOrdersCancelAllResponseResultInner>>)`.
    template <class CompletionToken>
    auto async_open_orders_cancel_all(const OpenOrdersCancelAllParams& params,
                                      CompletionToken&& token) const {
        return common::async_send<std::vector<OpenOrdersCancelAllResponseResultInner>>(
            client_, "openOrders.cancelAll", open_orders_cancel_all_payload(params),
            make_options(false, true, false, false), std::forward<CompletionToken>(token));
    }

    /// Order Amend Keep Priority (TRADE)
    ///
    /// `order.amend.keepPriority`.
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
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/trade#order-amend-keep-priority
    [[nodiscard]] common::WebsocketApiResponse<OrderAmendKeepPriorityResponseResult>
    order_amend_keep_priority(const OrderAmendKeepPriorityParams& params) const;

    /// Asynchronous `order_amend_keep_priority()`. Completes with
    /// `void(std::exception_ptr,
    /// common::WebsocketApiResponse<OrderAmendKeepPriorityResponseResult>)`.
    template <class CompletionToken>
    auto async_order_amend_keep_priority(const OrderAmendKeepPriorityParams& params,
                                         CompletionToken&& token) const {
        return common::async_send<OrderAmendKeepPriorityResponseResult>(
            client_, "order.amend.keepPriority", order_amend_keep_priority_payload(params),
            make_options(false, true, false, false), std::forward<CompletionToken>(token));
    }

    /// Cancel order (TRADE)
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
    /// **Data Source:** Matching Engine
    ///
    /// Notes:
    ///
    /// * If both `orderId` and `origClientOrderId` parameters are provided, the `orderId` is
    /// searched first, then the `origClientOrderId` from that result is checked against that order.
    /// If both conditions are not met the request will be rejected.
    ///
    /// * `newClientOrderId` will replace `clientOrderId` of the canceled order, freeing it up for
    /// new orders.
    ///
    /// * If you cancel an order that is a part of an order list, the entire order list is canceled.
    ///
    /// * The performance for canceling an order (single cancel or as part of a cancel-replace) is
    /// always better when only `orderId` is sent. Sending `origClientOrderId` or both `orderId` +
    /// `origClientOrderId` will be slower.
    ///
    /// Response Notes:
    /// **Note:** The payload above does not show all fields that can appear. Please refer to
    /// Conditional fields in Order Responses.
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
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/trade#order-cancel
    [[nodiscard]] common::WebsocketApiResponse<OrderCancelResponseResult>
    order_cancel(const OrderCancelParams& params) const;

    /// Asynchronous `order_cancel()`. Completes with
    /// `void(std::exception_ptr, common::WebsocketApiResponse<OrderCancelResponseResult>)`.
    template <class CompletionToken>
    auto async_order_cancel(const OrderCancelParams& params, CompletionToken&& token) const {
        return common::async_send<OrderCancelResponseResult>(
            client_, "order.cancel", order_cancel_payload(params),
            make_options(false, true, false, false), std::forward<CompletionToken>(token));
    }

    /// Cancel and replace order (TRADE)
    ///
    /// `order.cancelReplace`.
    ///
    /// * Cancel an existing order and immediately place a new order instead of the canceled one.
    /// * A new order that was not attempted (i.e. when `newOrderResult: NOT_ATTEMPTED`), will still
    /// increase the unfilled order count by 1.
    /// * You can only cancel an individual order from an orderList using this method, but the
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
    /// Similar to the `order.place` request,
    /// additional mandatory parameters (*) are determined by the new order `type`.
    ///
    /// Available `cancelReplaceMode` options:
    ///
    /// * `STOP_ON_FAILURE` – if cancellation request fails, new order placement will not be
    /// attempted.
    /// * `ALLOW_FAILURE` – new order placement will be attempted even if the cancel request fails.
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
    /// - `ALLOW_FAILURE` | `CANCEL_ONLY` | Exceeds Limits | ✅ `SUCCESS` | ✅ `SUCCESS` | `200`
    /// - `ALLOW_FAILURE` | `CANCEL_ONLY` | Exceeds Limits | ❌ `FAILURE` | ❌ `FAILURE` | `400`
    /// - `ALLOW_FAILURE` | `CANCEL_ONLY` | Exceeds Limits | ❌ `FAILURE` | ✅ `SUCCESS` | N/A
    /// - `ALLOW_FAILURE` | `CANCEL_ONLY` | Exceeds Limits | ✅ `SUCCESS` | ❌ `FAILURE` | `409`
    ///
    /// Notes:
    ///
    /// * If both `cancelOrderId` and `cancelOrigClientOrderId` parameters are provided, the
    /// `cancelOrderId` is searched first, then the `cancelOrigClientOrderId` from that result is
    /// checked against that order. If both conditions are not met the request will be rejected.
    ///
    /// * `cancelNewClientOrderId` will replace `clientOrderId` of the canceled order, freeing it up
    /// for new orders.
    ///
    /// * `newClientOrderId` specifies `clientOrderId` value for the placed order.
    ///
    ///   A new order with the same `clientOrderId` is accepted only when the previous one is filled
    ///   or expired.
    ///
    ///   The new order can reuse old `clientOrderId` of the canceled order.
    ///
    /// * This cancel-replace operation is **not transactional**.
    ///
    ///   If one operation succeeds but the other one fails, the successful operation is still
    ///   executed.
    ///
    ///   For example, in `STOP_ON_FAILURE` mode, if the new order placement fails, the old order is
    ///   still canceled.
    ///
    /// * Filters and order count limits are evaluated before cancellation and order placement
    /// occurs.
    ///
    /// * If new order placement is not attempted, your order count is still incremented.
    ///
    /// * Like `order.cancel`, if you cancel an individual order from an order list, the entire
    /// order list is canceled.
    ///
    /// * The performance for canceling an order (single cancel or as part of a cancel-replace) is
    /// always better when only `orderId` is sent. Sending `origClientOrderId` or both `orderId` +
    /// `origClientOrderId` will be slower.
    ///
    /// Response Notes:
    /// **Note:** The payload above does not show all fields that can appear. Please refer to
    /// Conditional fields in Order Responses.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/trade#order-cancel-replace
    [[nodiscard]] common::WebsocketApiResponse<OrderCancelReplaceResponseResult>
    order_cancel_replace(const OrderCancelReplaceParams& params) const;

    /// Asynchronous `order_cancel_replace()`. Completes with
    /// `void(std::exception_ptr, common::WebsocketApiResponse<OrderCancelReplaceResponseResult>)`.
    template <class CompletionToken>
    auto async_order_cancel_replace(const OrderCancelReplaceParams& params,
                                    CompletionToken&& token) const {
        return common::async_send<OrderCancelReplaceResponseResult>(
            client_, "order.cancelReplace", order_cancel_replace_payload(params),
            make_options(false, true, false, false), std::forward<CompletionToken>(token));
    }

    /// Cancel Order list (TRADE)
    ///
    /// `orderList.cancel`.
    ///
    /// Cancel an active order list.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// **Data Source:** Matching Engine
    ///
    /// Notes:
    ///
    /// * If both `orderListId` and `listClientOrderId` parameters are provided, the `orderListId`
    /// is searched first, then the `listClientOrderId` from that result is checked against that
    /// order. If both conditions are not met the request will be rejected.
    ///
    /// * Canceling an individual order with `order.cancel` will cancel the entire order list as
    /// well.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/trade#order-list-cancel
    [[nodiscard]] common::WebsocketApiResponse<OrderListCancelResponseResult>
    order_list_cancel(const OrderListCancelParams& params) const;

    /// Asynchronous `order_list_cancel()`. Completes with
    /// `void(std::exception_ptr, common::WebsocketApiResponse<OrderListCancelResponseResult>)`.
    template <class CompletionToken>
    auto async_order_list_cancel(const OrderListCancelParams& params,
                                 CompletionToken&& token) const {
        return common::async_send<OrderListCancelResponseResult>(
            client_, "orderList.cancel", order_list_cancel_payload(params),
            make_options(false, true, false, false), std::forward<CompletionToken>(token));
    }

    /// Place new OCO - Deprecated (TRADE)
    ///
    /// `orderList.place`.
    ///
    /// Send in a new one-cancels-the-other (OCO) pair:
    /// `LIMIT_MAKER` + `STOP_LOSS`/`STOP_LOSS_LIMIT` orders (called *legs*),
    /// where activation of one order immediately cancels the other.
    ///
    /// This adds 1 order to `EXCHANGE_MAX_ORDERS` filter and the `MAX_NUM_ORDERS` filter
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
    /// Notes:
    ///
    /// * `listClientOrderId` parameter specifies `listClientOrderId` for the OCO pair.
    ///
    ///   A new OCO with the same `listClientOrderId` is accepted only when the previous one is
    ///   filled or completely expired.
    ///
    ///   `listClientOrderId` is distinct from `clientOrderId` of individual orders.
    ///
    /// * `limitClientOrderId` and `stopClientOrderId` specify `clientOrderId` values for both legs
    /// of the OCO.
    ///
    ///   A new order with the same `clientOrderId` is accepted only when the previous one is filled
    ///   or expired.
    ///
    /// * Price restrictions on the legs:
    ///
    ///   | `side` | Price relation |
    ///   | ------ | -------------- |
    ///   | `BUY`  | `price` < market price < `stopPrice` |
    ///   | `SELL` | `price` > market price > `stopPrice` |
    ///
    /// * Both legs have the same `quantity`.
    ///
    ///   However, you can set different iceberg quantity for individual legs.
    ///
    ///   If `stopIcebergQty` is used, `stopLimitTimeInForce` must be `GTC`.
    ///
    /// * `trailingDelta` applies only to the `STOP_LOSS`/`STOP_LOSS_LIMIT` leg of the OCO.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/trade#order-list-place
    ///
    /// Deprecated: this endpoint may be removed in a future version.
    [[nodiscard]] common::WebsocketApiResponse<OrderListPlaceResponseResult>
    order_list_place(const OrderListPlaceParams& params) const;

    /// Asynchronous `order_list_place()`. Completes with
    /// `void(std::exception_ptr, common::WebsocketApiResponse<OrderListPlaceResponseResult>)`.
    template <class CompletionToken>
    auto async_order_list_place(const OrderListPlaceParams& params, CompletionToken&& token) const {
        return common::async_send<OrderListPlaceResponseResult>(
            client_, "orderList.place", order_list_place_payload(params),
            make_options(false, true, false, false), std::forward<CompletionToken>(token));
    }

    /// Place new Order list - OCO (TRADE)
    ///
    /// `orderList.place.oco`.
    ///
    /// Send in an one-cancels-the-other (OCO) pair, where activation of one order immediately
    /// cancels the other.
    ///
    /// * An OCO has 2 orders called the **above order** and **below order**.
    ///
    /// * One of the orders must be a `LIMIT_MAKER/TAKE_PROFIT/TAKE_PROFIT_LIMIT` order and the
    /// other must be `STOP_LOSS` or `STOP_LOSS_LIMIT` order.
    ///
    /// * Price restrictions:
    ///   * If the OCO is on the `SELL` side:
    ///     * `LIMIT_MAKER/TAKE_PROFIT_LIMIT` `price` > Last Traded Price >
    ///     `STOP_LOSS/STOP_LOSS_LIMIT`
    /// `stopPrice`
    ///     * `TAKE_PROFIT stopPrice` > Last Traded Price > `STOP_LOSS/STOP_LOSS_LIMIT
    /// stopPrice`
    ///   * If the OCO is on the `BUY` side:
    ///     * `LIMIT_MAKER` `price` < Last Traded Price < `STOP_LOSS/STOP_LOSS_LIMIT` `stopPrice`
    ///     * `TAKE_PROFIT stopPrice` > Last Traded Price > `STOP_LOSS/STOP_LOSS_LIMIT stopPrice`
    /// *  OCOs add **2 orders** to the `EXCHANGE_MAX_ORDERS` filter and `MAX_NUM_ORDERS` filter.
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
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/trade#order-list-place-oco
    [[nodiscard]] common::WebsocketApiResponse<OrderListPlaceOcoResponseResult>
    order_list_place_oco(const OrderListPlaceOcoParams& params) const;

    /// Asynchronous `order_list_place_oco()`. Completes with
    /// `void(std::exception_ptr, common::WebsocketApiResponse<OrderListPlaceOcoResponseResult>)`.
    template <class CompletionToken>
    auto async_order_list_place_oco(const OrderListPlaceOcoParams& params,
                                    CompletionToken&& token) const {
        return common::async_send<OrderListPlaceOcoResponseResult>(
            client_, "orderList.place.oco", order_list_place_oco_payload(params),
            make_options(false, true, false, false), std::forward<CompletionToken>(token));
    }

    /// OPO (TRADE)
    ///
    /// `orderList.place.opo`.
    ///
    /// Place an OPO.
    ///
    /// * The working order must be `LIMIT` or `LIMIT_MAKER`.
    /// * OPOs add 2 orders to the EXCHANGE_MAX_NUM_ORDERS filter and MAX_NUM_ORDERS filter.
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
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/trade#order-list-place-opo
    [[nodiscard]] common::WebsocketApiResponse<OrderListPlaceOpoResponseResult>
    order_list_place_opo(const OrderListPlaceOpoParams& params) const;

    /// Asynchronous `order_list_place_opo()`. Completes with
    /// `void(std::exception_ptr, common::WebsocketApiResponse<OrderListPlaceOpoResponseResult>)`.
    template <class CompletionToken>
    auto async_order_list_place_opo(const OrderListPlaceOpoParams& params,
                                    CompletionToken&& token) const {
        return common::async_send<OrderListPlaceOpoResponseResult>(
            client_, "orderList.place.opo", order_list_place_opo_payload(params),
            make_options(false, true, false, false), std::forward<CompletionToken>(token));
    }

    /// OPOCO (TRADE)
    ///
    /// `orderList.place.opoco`.
    ///
    /// Place an OPOCO.
    ///
    /// * The working order must be `LIMIT` or `LIMIT_MAKER`.
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
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/trade#order-list-place-opoco
    [[nodiscard]] common::WebsocketApiResponse<OrderListPlaceOpocoResponseResult>
    order_list_place_opoco(const OrderListPlaceOpocoParams& params) const;

    /// Asynchronous `order_list_place_opoco()`. Completes with
    /// `void(std::exception_ptr, common::WebsocketApiResponse<OrderListPlaceOpocoResponseResult>)`.
    template <class CompletionToken>
    auto async_order_list_place_opoco(const OrderListPlaceOpocoParams& params,
                                      CompletionToken&& token) const {
        return common::async_send<OrderListPlaceOpocoResponseResult>(
            client_, "orderList.place.opoco", order_list_place_opoco_payload(params),
            make_options(false, true, false, false), std::forward<CompletionToken>(token));
    }

    /// Place new Order list - OTO (TRADE)
    ///
    /// `orderList.place.oto`.
    ///
    /// Places an OTO.
    ///
    /// * An OTO (One-Triggers-the-Other) is an order list comprised of 2 orders.
    ///
    /// * The first order is called the **working order** and must be `LIMIT` or `LIMIT_MAKER`.
    /// Initially, only the working order goes on the order book.
    ///
    /// * The second order is called the **pending order**. It can be any order type except for
    /// `MARKET` orders using parameter `quoteOrderQty`. The pending order is only placed on the
    /// order book when the working order gets
    /// **fully filled**.
    ///
    /// * If either the working order or the pending order is cancelled individually, the other
    /// order in the order list will also be canceled or expired.
    ///
    /// * When the order list is placed, if the working order gets **immediately fully filled**, the
    /// placement response will show the working order as `FILLED` but the pending order will still
    /// appear as `PENDING_NEW`. You need to query the status of the pending order again to see its
    /// updated status.
    ///
    /// * OTOs add **2 orders** to the `EXCHANGE_MAX_NUM_ORDERS` filter and `MAX_NUM_ORDERS` filter.
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
    /// |`pendingType` =`STOP_LOSS_LIMIT` or `TAKE_PROFIT_LIMIT`|`pendingPrice`, `pendingStopPrice`
    /// and/or `pendingTrailingDelta`, `pendingTimeInForce`|
    ///
    /// Response Notes:
    /// **Note:** The payload above does not show all fields that can appear. Please refer to
    /// Conditional fields in Order Responses.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/trade#order-list-place-oto
    [[nodiscard]] common::WebsocketApiResponse<OrderListPlaceOtoResponseResult>
    order_list_place_oto(const OrderListPlaceOtoParams& params) const;

    /// Asynchronous `order_list_place_oto()`. Completes with
    /// `void(std::exception_ptr, common::WebsocketApiResponse<OrderListPlaceOtoResponseResult>)`.
    template <class CompletionToken>
    auto async_order_list_place_oto(const OrderListPlaceOtoParams& params,
                                    CompletionToken&& token) const {
        return common::async_send<OrderListPlaceOtoResponseResult>(
            client_, "orderList.place.oto", order_list_place_oto_payload(params),
            make_options(false, true, false, false), std::forward<CompletionToken>(token));
    }

    /// Place new Order list - OTOCO (TRADE)
    ///
    /// `orderList.place.otoco`.
    ///
    /// Place an OTOCO.
    ///
    /// * An OTOCO (One-Triggers-One-Cancels-the-Other) is an order list comprised of 3 orders.
    /// * The first order is called the **working order** and must be `LIMIT` or `LIMIT_MAKER`.
    /// Initially, only the working order goes on the order book.
    ///   * The behavior of the working order is the same as the OTO.
    /// * OTOCO has 2 pending orders (pending above and pending below), forming an OCO pair. The
    /// pending orders are only placed on the order book when the working order gets **fully
    /// filled**.
    ///   * The rules of the pending above and pending below follow the same rules as the Order list
    ///   OCO.
    /// * OTOCOs add **3 orders** to the `EXCHANGE_MAX_NUM_ORDERS` filter and `MAX_NUM_ORDERS`
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
    /// |`pendingAboveType`= `LIMIT_MAKER`                                |`pendingAbovePrice` |
    /// |`pendingAboveType` = `STOP_LOSS/TAKE_PROFIT`         |`pendingAboveStopPrice` and/or
    /// `pendingAboveTrailingDelta`|
    /// |`pendingAboveType=STOP_LOSS_LIMIT/TAKE_PROFIT_LIMIT`|`pendingAbovePrice`,
    /// `pendingAboveStopPrice` and/or `pendingAboveTrailingDelta`, `pendingAboveTimeInForce`|
    /// |`pendingBelowType`= `LIMIT_MAKER`                                |`pendingBelowPrice` |
    /// `pendingBelowType= STOP_LOSS/TAKE_PROFIT`         |`pendingBelowStopPrice` and/or
    /// `pendingBelowTrailingDelta`|
    /// |`pendingBelowType=STOP_LOSS_LIMIT/TAKE_PROFIT_LIMIT`|`pendingBelowPrice`,
    /// `pendingBelowStopPrice` and/or `pendingBelowTrailingDelta`, `pendingBelowTimeInForce`|
    ///
    /// Response Notes:
    /// **Note:** The payload above does not show all fields that can appear. Please refer to
    /// Conditional fields in Order Responses.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/trade#order-list-place-otoco
    [[nodiscard]] common::WebsocketApiResponse<OrderListPlaceOtocoResponseResult>
    order_list_place_otoco(const OrderListPlaceOtocoParams& params) const;

    /// Asynchronous `order_list_place_otoco()`. Completes with
    /// `void(std::exception_ptr, common::WebsocketApiResponse<OrderListPlaceOtocoResponseResult>)`.
    template <class CompletionToken>
    auto async_order_list_place_otoco(const OrderListPlaceOtocoParams& params,
                                      CompletionToken&& token) const {
        return common::async_send<OrderListPlaceOtocoResponseResult>(
            client_, "orderList.place.otoco", order_list_place_otoco_payload(params),
            make_options(false, true, false, false), std::forward<CompletionToken>(token));
    }

    /// Place new order (TRADE)
    ///
    /// `order.place`.
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
    /// Certain parameters (*) become mandatory based on the order `type`:
    ///
    /// - Order `type` | Mandatory parameters
    /// - `LIMIT` |
    /// ,
    /// - `timeInForce`,
    /// - `price`,
    /// - `quantity`,
    ///
    /// - `LIMIT_MAKER` |
    /// ,
    /// - `price`,
    /// - `quantity`,
    ///
    /// - `MARKET` |
    /// ,
    /// - `quantity` or `quoteOrderQty`,
    ///
    /// - `STOP_LOSS` |
    /// ,
    /// - `quantity`,
    /// - `stopPrice` or `trailingDelta`,
    ///
    /// - `STOP_LOSS_LIMIT` |
    /// ,
    /// - `timeInForce`,
    /// - `price`,
    /// - `quantity`,
    /// - `stopPrice` or `trailingDelta`,
    ///
    /// - `TAKE_PROFIT` |
    /// ,
    /// - `quantity`,
    /// - `stopPrice` or `trailingDelta`,
    ///
    /// - `TAKE_PROFIT_LIMIT` |
    /// ,
    /// - `timeInForce`,
    /// - `price`,
    /// - `quantity`,
    /// - `stopPrice` or `trailingDelta`,
    ///
    /// Supported order types:
    ///
    /// - Order `type` | Description
    /// - `LIMIT` |
    ///
    /// , Buy or sell `quantity` at the specified `price` or better.,
    ///
    /// - `LIMIT_MAKER` |
    ///
    /// , `LIMIT` order that will be rejected if it immediately matches and trades as a taker.,
    ///
    /// ,
    ///
    /// , This order type is also known as a POST-ONLY order.,
    ///
    /// - `MARKET` |
    ///
    /// , Buy or sell at the best available market price.,
    ///
    /// ,
    /// ,
    /// - ,
    ///
    /// , `MARKET` order with `quantity` parameter, specifies the amount of the *base asset* you
    /// want to buy or sell., Actually executed quantity of the quote asset will be determined by
    /// available market liquidity.,
    ///
    /// ,
    ///
    /// , E.g., a MARKET BUY order on BTCUSDT for `"quantity": "0.1000"`, specifies that you want to
    /// buy 0.1 BTC at the best available price., If there is not enough BTC at the best price, keep
    /// buying at the next best price,, until either your order is filled, or you run out of USDT,
    /// or market runs out of BTC.,
    ///
    /// , ,
    /// - ,
    ///
    /// , `MARKET` order with `quoteOrderQty` parameter, specifies the amount of the *quote asset*
    /// you want to spend (when buying) or receive (when selling)., Actually executed quantity of
    /// the base asset will be determined by available market liquidity.,
    ///
    /// ,
    ///
    /// , E.g., a MARKET BUY on BTCUSDT for `"quoteOrderQty": "100.00"`, specifies that you want to
    /// buy as much BTC as you can for 100 USDT at the best available price., Similarly, a SELL
    /// order will sell as much available BTC as needed for you to receive 100 USDT, (before
    /// commission).,
    ///
    /// , ,
    ///
    /// - `STOP_LOSS` |
    ///
    /// , Execute a `MARKET` order for given `quantity` when specified conditions are met.,
    ///
    /// ,
    ///
    /// , I.e., when `stopPrice` is reached, or when `trailingDelta` is activated.,
    ///
    /// - `STOP_LOSS_LIMIT` |
    ///
    /// , Place a `LIMIT` order with given parameters when specified conditions are met.,
    ///
    /// - `TAKE_PROFIT` |
    ///
    /// , Like `STOP_LOSS` but activates when market price moves in the favorable direction.,
    ///
    /// - `TAKE_PROFIT_LIMIT` |
    ///
    /// , Like `STOP_LOSS_LIMIT` but activates when market price moves in the favorable direction.,
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
    /// Available `timeInForce` options,
    /// setting how long the order should be active before expiration:
    ///
    /// TIF  | Description
    /// ----- | --------------
    /// `GTC` | **Good 'til Canceled** – the order will remain on the book until you cancel it, or
    /// the order is completely filled. `IOC` | **Immediate or Cancel** – the order will be filled
    /// for as much as possible, the unfilled quantity immediately expires. `FOK` | **Fill or Kill**
    /// – the order will expire unless it cannot be immediately filled for the entire quantity.
    ///
    /// Notes:
    ///
    /// * `newClientOrderId` specifies `clientOrderId` value for the order.
    ///
    ///   A new order with the same `clientOrderId` is accepted only when the previous one is filled
    ///   or expired.
    ///
    /// * Any `LIMIT` or `LIMIT_MAKER` order can be made into an iceberg order by specifying the
    /// `icebergQty`.
    ///
    ///   An order with an `icebergQty` must have `timeInForce` set to `GTC`.
    ///
    /// * Trigger order price rules for `STOP_LOSS`/`TAKE_PROFIT` orders:
    ///
    ///   * `stopPrice` must be above market price: `STOP_LOSS BUY`, `TAKE_PROFIT SELL`
    ///   * `stopPrice` must be below market price: `STOP_LOSS SELL`, `TAKE_PROFIT BUY`
    ///
    /// * `MARKET` orders using `quoteOrderQty` follow `LOT_SIZE` filter rules.
    ///
    ///   The order will execute a quantity that has notional value as close as possible to
    ///   requested `quoteOrderQty`.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/trade#order-place
    [[nodiscard]] common::WebsocketApiResponse<OrderPlaceResponseResult>
    order_place(const OrderPlaceParams& params) const;

    /// Asynchronous `order_place()`. Completes with
    /// `void(std::exception_ptr, common::WebsocketApiResponse<OrderPlaceResponseResult>)`.
    template <class CompletionToken>
    auto async_order_place(const OrderPlaceParams& params, CompletionToken&& token) const {
        return common::async_send<OrderPlaceResponseResult>(
            client_, "order.place", order_place_payload(params),
            make_options(false, true, false, false), std::forward<CompletionToken>(token));
    }

    /// Test new order (TRADE)
    ///
    /// `order.test`.
    ///
    /// Test order placement.
    ///
    /// Validates new order parameters and verifies your signature
    /// but does not send the order into the matching engine.
    ///
    /// Weight: | Condition | Request Weight |
    /// | --- | --- |
    /// | Without `computeCommissionRates` | 1 |
    /// | With `computeCommissionRates` | 20 |
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// **Data Source:** Memory
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/trade#order-test
    [[nodiscard]] common::WebsocketApiResponse<OrderTestResponseResult>
    order_test(const OrderTestParams& params) const;

    /// Asynchronous `order_test()`. Completes with
    /// `void(std::exception_ptr, common::WebsocketApiResponse<OrderTestResponseResult>)`.
    template <class CompletionToken>
    auto async_order_test(const OrderTestParams& params, CompletionToken&& token) const {
        return common::async_send<OrderTestResponseResult>(
            client_, "order.test", order_test_payload(params),
            make_options(false, true, false, false), std::forward<CompletionToken>(token));
    }

    /// Place new order using SOR (TRADE)
    ///
    /// `sor.order.place`.
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
    /// **Note:** `sor.order.place` only supports `LIMIT` and `MARKET` orders. `quoteOrderQty` is
    /// not supported.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/trade#sor-order-place
    [[nodiscard]] common::WebsocketApiResponse<std::vector<SorOrderPlaceResponseResultInner>>
    sor_order_place(const SorOrderPlaceParams& params) const;

    /// Asynchronous `sor_order_place()`. Completes with
    /// `void(std::exception_ptr,
    /// common::WebsocketApiResponse<std::vector<SorOrderPlaceResponseResultInner>>)`.
    template <class CompletionToken>
    auto async_sor_order_place(const SorOrderPlaceParams& params, CompletionToken&& token) const {
        return common::async_send<std::vector<SorOrderPlaceResponseResultInner>>(
            client_, "sor.order.place", sor_order_place_payload(params),
            make_options(false, true, false, false), std::forward<CompletionToken>(token));
    }

    /// Test new order using SOR (TRADE)
    ///
    /// `sor.order.test`.
    ///
    /// Test new order creation and signature/recvWindow using smart order routing (SOR).
    /// Creates and validates a new order but does not send it into the matching engine.
    ///
    /// Weight: | Condition | Request Weight |
    /// | --- | --- |
    /// | Without `computeCommissionRates` | 1 |
    /// | With `computeCommissionRates` | 20 |
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// **Data Source:** Memory
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/trade#sor-order-test
    [[nodiscard]] common::WebsocketApiResponse<SorOrderTestResponseResult>
    sor_order_test(const SorOrderTestParams& params) const;

    /// Asynchronous `sor_order_test()`. Completes with
    /// `void(std::exception_ptr, common::WebsocketApiResponse<SorOrderTestResponseResult>)`.
    template <class CompletionToken>
    auto async_sor_order_test(const SorOrderTestParams& params, CompletionToken&& token) const {
        return common::async_send<SorOrderTestResponseResult>(
            client_, "sor.order.test", sor_order_test_payload(params),
            make_options(false, true, false, false), std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] static common::Params
    open_orders_cancel_all_payload(const OpenOrdersCancelAllParams& params);
    [[nodiscard]] static common::Params
    order_amend_keep_priority_payload(const OrderAmendKeepPriorityParams& params);
    [[nodiscard]] static common::Params order_cancel_payload(const OrderCancelParams& params);
    [[nodiscard]] static common::Params
    order_cancel_replace_payload(const OrderCancelReplaceParams& params);
    [[nodiscard]] static common::Params
    order_list_cancel_payload(const OrderListCancelParams& params);
    [[nodiscard]] static common::Params
    order_list_place_payload(const OrderListPlaceParams& params);
    [[nodiscard]] static common::Params
    order_list_place_oco_payload(const OrderListPlaceOcoParams& params);
    [[nodiscard]] static common::Params
    order_list_place_opo_payload(const OrderListPlaceOpoParams& params);
    [[nodiscard]] static common::Params
    order_list_place_opoco_payload(const OrderListPlaceOpocoParams& params);
    [[nodiscard]] static common::Params
    order_list_place_oto_payload(const OrderListPlaceOtoParams& params);
    [[nodiscard]] static common::Params
    order_list_place_otoco_payload(const OrderListPlaceOtocoParams& params);
    [[nodiscard]] static common::Params order_place_payload(const OrderPlaceParams& params);
    [[nodiscard]] static common::Params order_test_payload(const OrderTestParams& params);
    [[nodiscard]] static common::Params sor_order_place_payload(const SorOrderPlaceParams& params);
    [[nodiscard]] static common::Params sor_order_test_payload(const SorOrderTestParams& params);
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

} // namespace binance::spot::websocket_api
