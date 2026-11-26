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

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/derivatives_trading_options/export.hpp>

namespace binance::derivatives_trading_options::rest_api {

struct AccountFundingFlowResponseInner {
    /// id
    std::optional<std::int64_t> id;
    /// Asset type
    std::optional<std::string> asset;
    /// Amount (positive numbers represent inflow, negative numbers represent outflow)
    std::optional<std::string> amount;
    /// Option symbol the record relates to. Returned only for contract-related types (e.g.
    /// `CONTRACT`, `FEE`, `EXERCISE_PNL`, `EXERCISE_FEE`); omitted for other types such as
    /// `TRANSFER`. Older records may not include this field.
    std::optional<std::string> symbol;
    /// type (fees)
    std::optional<std::string> type;
    /// Time
    std::optional<std::int64_t> create_date;

    bool operator==(const AccountFundingFlowResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT AccountFundingFlowResponseInner
tag_invoke(boost::json::value_to_tag<AccountFundingFlowResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const AccountFundingFlowResponseInner& v);

} // namespace binance::derivatives_trading_options::rest_api
