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
#include <binance/derivatives_trading_options/export.hpp>

namespace binance::derivatives_trading_options::rest_api {

enum class PlaceMultipleOrdersOrdersParameterInnerSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT std::string_view
to_string(PlaceMultipleOrdersOrdersParameterInnerSideEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT PlaceMultipleOrdersOrdersParameterInnerSideEnum
tag_invoke(boost::json::value_to_tag<PlaceMultipleOrdersOrdersParameterInnerSideEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           PlaceMultipleOrdersOrdersParameterInnerSideEnum value);

enum class PlaceMultipleOrdersOrdersParameterInnerTypeEnum {
    Limit,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT std::string_view
to_string(PlaceMultipleOrdersOrdersParameterInnerTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT PlaceMultipleOrdersOrdersParameterInnerTypeEnum
tag_invoke(boost::json::value_to_tag<PlaceMultipleOrdersOrdersParameterInnerTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           PlaceMultipleOrdersOrdersParameterInnerTypeEnum value);

enum class PlaceMultipleOrdersOrdersParameterInnerTimeInForceEnum {
    Gtc,
    Ioc,
    Fok,
    Gtx,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT std::string_view
to_string(PlaceMultipleOrdersOrdersParameterInnerTimeInForceEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT PlaceMultipleOrdersOrdersParameterInnerTimeInForceEnum
tag_invoke(
    boost::json::value_to_tag<PlaceMultipleOrdersOrdersParameterInnerTimeInForceEnum> /*tag*/,
    const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           PlaceMultipleOrdersOrdersParameterInnerTimeInForceEnum value);

enum class PlaceMultipleOrdersOrdersParameterInnerNewOrderRespTypeEnum {
    Ack,
    Result,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT std::string_view
to_string(PlaceMultipleOrdersOrdersParameterInnerNewOrderRespTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT
PlaceMultipleOrdersOrdersParameterInnerNewOrderRespTypeEnum tag_invoke(
    boost::json::value_to_tag<PlaceMultipleOrdersOrdersParameterInnerNewOrderRespTypeEnum> /*tag*/,
    const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           PlaceMultipleOrdersOrdersParameterInnerNewOrderRespTypeEnum value);

enum class PlaceMultipleOrdersOrdersParameterInnerSelfTradePreventionModeEnum {
    ExpireTaker,
    ExpireMaker,
    ExpireBoth,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT std::string_view
to_string(PlaceMultipleOrdersOrdersParameterInnerSelfTradePreventionModeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT
PlaceMultipleOrdersOrdersParameterInnerSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<
               PlaceMultipleOrdersOrdersParameterInnerSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           PlaceMultipleOrdersOrdersParameterInnerSelfTradePreventionModeEnum value);

struct PlaceMultipleOrdersOrdersParameterInner {
    std::optional<std::string> symbol;
    std::optional<PlaceMultipleOrdersOrdersParameterInnerSideEnum> side;
    std::optional<PlaceMultipleOrdersOrdersParameterInnerTypeEnum> type;
    /// Order Quantity
    std::optional<common::Decimal> quantity;
    /// Order Price
    std::optional<common::Decimal> price;
    std::optional<PlaceMultipleOrdersOrdersParameterInnerTimeInForceEnum> time_in_force;
    std::optional<bool> reduce_only;
    std::optional<bool> post_only;
    std::optional<PlaceMultipleOrdersOrdersParameterInnerNewOrderRespTypeEnum> new_order_resp_type;
    /// User-defined order ID cannot be repeated in pending orders
    std::optional<std::string> client_order_id;
    /// is market maker protection order
    std::optional<bool> is_mmp;
    /// EXPIRE_TAKER: expire taker order when STP triggers/ EXPIRE_MAKER: expire maker order when
    /// STP triggers/ EXPIRE_BOTH: expire both orders when STP triggers; Default EXPIRE_MAKER
    std::optional<PlaceMultipleOrdersOrdersParameterInnerSelfTradePreventionModeEnum>
        self_trade_prevention_mode;

    bool operator==(const PlaceMultipleOrdersOrdersParameterInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT PlaceMultipleOrdersOrdersParameterInner
tag_invoke(boost::json::value_to_tag<PlaceMultipleOrdersOrdersParameterInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const PlaceMultipleOrdersOrdersParameterInner& v);

} // namespace binance::derivatives_trading_options::rest_api
