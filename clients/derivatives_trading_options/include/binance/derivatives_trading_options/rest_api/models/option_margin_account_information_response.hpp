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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/derivatives_trading_options/export.hpp>
#include <binance/derivatives_trading_options/rest_api/models/option_margin_account_information_response_asset_inner.hpp>
#include <binance/derivatives_trading_options/rest_api/models/option_margin_account_information_response_greek_inner.hpp>

namespace binance::derivatives_trading_options::rest_api {

struct OptionMarginAccountInformationResponse {
    /// asset
    std::optional<std::vector<OptionMarginAccountInformationResponseAssetInner>> asset;
    /// greek
    std::optional<std::vector<OptionMarginAccountInformationResponseGreekInner>> greek;
    /// time
    std::optional<std::int64_t> time;
    /// can Trade
    std::optional<bool> can_trade;
    /// can Deposit
    std::optional<bool> can_deposit;
    /// can Withdraw
    std::optional<bool> can_withdraw;
    /// reduce Only
    std::optional<bool> reduce_only;
    /// Trade group ID
    std::optional<std::int64_t> trade_group_id;

    bool operator==(const OptionMarginAccountInformationResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT OptionMarginAccountInformationResponse
tag_invoke(boost::json::value_to_tag<OptionMarginAccountInformationResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const OptionMarginAccountInformationResponse& v);

} // namespace binance::derivatives_trading_options::rest_api
