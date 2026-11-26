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
#include <binance/derivatives_trading_coin_futures/export.hpp>

namespace binance::derivatives_trading_coin_futures::rest_api {

enum class ModifyMultipleOrdersBatchOrdersParameterInnerSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT std::string_view
to_string(ModifyMultipleOrdersBatchOrdersParameterInnerSideEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT
ModifyMultipleOrdersBatchOrdersParameterInnerSideEnum
tag_invoke(boost::json::value_to_tag<ModifyMultipleOrdersBatchOrdersParameterInnerSideEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           ModifyMultipleOrdersBatchOrdersParameterInnerSideEnum value);

struct ModifyMultipleOrdersBatchOrdersParameterInner {
    /// Sub-order ID, required when clientOrderId is not sent.
    std::optional<std::int64_t> order_id;
    /// Client order ID, required when orderId is not sent. Only support letters, numbers and
    /// underscores, and must be unique within 24 hours.
    std::optional<std::string> orig_client_order_id;
    /// Trading symbol
    std::optional<std::string> symbol;
    /// Trading side
    std::optional<ModifyMultipleOrdersBatchOrdersParameterInnerSideEnum> side;
    /// Order quantity, cannot be sent with closePosition=true. **After CM migration, this parameter
    /// becomes mandatory** (each batch element must send both `price` and `quantity`).
    std::optional<common::Decimal> quantity;
    /// Latest token price. **After CM migration, this parameter becomes mandatory** (each batch
    /// element must send both `price` and `quantity`).
    std::optional<common::Decimal> price;
    /// User-defined modification identifier, returned as-is in the response. Optional; not
    /// validated for uniqueness.
    std::optional<std::int64_t> modify_id;
    std::optional<std::int64_t> recv_window;
    /// Unix timestamp in milliseconds used to sign the request. The value must reflect the current
    /// client time and is validated by the server for signed endpoints.
    std::optional<std::int64_t> timestamp;

    bool operator==(const ModifyMultipleOrdersBatchOrdersParameterInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT ModifyMultipleOrdersBatchOrdersParameterInner
tag_invoke(boost::json::value_to_tag<ModifyMultipleOrdersBatchOrdersParameterInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const ModifyMultipleOrdersBatchOrdersParameterInner& v);

} // namespace binance::derivatives_trading_coin_futures::rest_api
