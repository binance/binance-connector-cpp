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

#include <binance/derivatives_trading_options/export.hpp>

namespace binance::derivatives_trading_options::rest_api {

enum class NewBlockTradeOrderLegsParameterInnerSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT std::string_view
to_string(NewBlockTradeOrderLegsParameterInnerSideEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT NewBlockTradeOrderLegsParameterInnerSideEnum
tag_invoke(boost::json::value_to_tag<NewBlockTradeOrderLegsParameterInnerSideEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           NewBlockTradeOrderLegsParameterInnerSideEnum value);

enum class NewBlockTradeOrderLegsParameterInnerTypeEnum {
    Limit,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT std::string_view
to_string(NewBlockTradeOrderLegsParameterInnerTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT NewBlockTradeOrderLegsParameterInnerTypeEnum
tag_invoke(boost::json::value_to_tag<NewBlockTradeOrderLegsParameterInnerTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           NewBlockTradeOrderLegsParameterInnerTypeEnum value);

struct NewBlockTradeOrderLegsParameterInner {
    /// Option trading pair
    std::optional<std::string> symbol;
    /// Buy/sell direction
    std::optional<NewBlockTradeOrderLegsParameterInnerSideEnum> side;
    /// Order type
    std::optional<NewBlockTradeOrderLegsParameterInnerTypeEnum> type;
    /// Order quantity
    std::optional<std::string> quantity;
    /// Order price
    std::optional<std::string> price;

    bool operator==(const NewBlockTradeOrderLegsParameterInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT NewBlockTradeOrderLegsParameterInner
tag_invoke(boost::json::value_to_tag<NewBlockTradeOrderLegsParameterInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const NewBlockTradeOrderLegsParameterInner& v);

} // namespace binance::derivatives_trading_options::rest_api
