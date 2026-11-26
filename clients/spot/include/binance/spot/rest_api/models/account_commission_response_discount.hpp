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

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/spot/export.hpp>

namespace binance::spot::rest_api {

/// Discount commission when paying in BNB
struct AccountCommissionResponseDiscount {
    std::optional<bool> enabled_for_account;
    std::optional<bool> enabled_for_symbol;
    std::optional<std::string> discount_asset;
    /// Multiplier applied to the standard commission when paying commission in BNB (e.g. 0.75 = 75%
    /// of the standard commission is charged).
    std::optional<std::string> discount;

    bool operator==(const AccountCommissionResponseDiscount& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT AccountCommissionResponseDiscount
tag_invoke(boost::json::value_to_tag<AccountCommissionResponseDiscount> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const AccountCommissionResponseDiscount& v);

} // namespace binance::spot::rest_api
