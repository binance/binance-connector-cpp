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

struct AccountInfoResponse {
    std::optional<std::int64_t> vip_level;
    /// true or false for margin.
    std::optional<bool> is_margin_enabled;
    /// true or false for futures.
    std::optional<bool> is_future_enabled;
    /// true or false for options.
    std::optional<bool> is_options_enabled;
    /// true or false for portfolio margin retail.
    std::optional<bool> is_portfolio_margin_retail_enabled;

    bool operator==(const AccountInfoResponse& /*other*/) const = default;
};

BINANCE_WALLET_EXPORT AccountInfoResponse
tag_invoke(boost::json::value_to_tag<AccountInfoResponse> /*tag*/, const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const AccountInfoResponse& v);

} // namespace binance::wallet::rest_api
