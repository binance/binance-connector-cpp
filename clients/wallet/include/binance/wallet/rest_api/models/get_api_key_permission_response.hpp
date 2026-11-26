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

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/wallet/export.hpp>

namespace binance::wallet::rest_api {

struct GetApiKeyPermissionResponse {
    std::optional<bool> ip_restrict;
    std::optional<std::int64_t> create_time;
    std::optional<bool> enable_reading;
    /// This option allows you to withdraw via API. You must apply the IP Access Restriction filter
    /// in order to enable withdrawals
    std::optional<bool> enable_withdrawals;
    /// This option authorizes this key to transfer funds between your master account and your sub
    /// account instantly
    std::optional<bool> enable_internal_transfer;
    /// This option can be adjusted after the Cross Margin account transfer is completed
    std::optional<bool> enable_margin;
    /// The Futures API cannot be used if the API key was created before the Futures account was
    /// opened, or if you have enabled portfolio margin.
    std::optional<bool> enable_futures;
    /// Authorizes this key to be used for a dedicated universal transfer API to transfer multiple
    /// supported currencies. Each business's own transfer API rights are not affected by this
    /// authorization
    std::optional<bool> permits_universal_transfer;
    /// Authorizes this key to Vanilla options trading
    std::optional<bool> enable_vanilla_options;
    std::optional<bool> enable_fix_api_trade;
    std::optional<bool> enable_fix_read_only;
    /// Spot and margin trading
    std::optional<bool> enable_spot_and_margin_trading;
    /// API Key created before your activate portfolio margin does not support portfolio margin API
    /// service
    std::optional<bool> enable_portfolio_margin_trading;

    bool operator==(const GetApiKeyPermissionResponse& /*other*/) const = default;
};

BINANCE_WALLET_EXPORT GetApiKeyPermissionResponse tag_invoke(
    boost::json::value_to_tag<GetApiKeyPermissionResponse> /*tag*/, const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const GetApiKeyPermissionResponse& v);

} // namespace binance::wallet::rest_api
