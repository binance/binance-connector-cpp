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
#include <binance/spot/rest_api/models/account_commission_response_discount.hpp>
#include <binance/spot/rest_api/models/account_commission_response_special_commission.hpp>
#include <binance/spot/rest_api/models/account_commission_response_standard_commission.hpp>
#include <binance/spot/rest_api/models/account_commission_response_tax_commission.hpp>

namespace binance::spot::rest_api {

struct AccountCommissionResponse {
    std::optional<std::string> symbol;
    std::optional<AccountCommissionResponseStandardCommission> standard_commission;
    std::optional<AccountCommissionResponseSpecialCommission> special_commission;
    std::optional<AccountCommissionResponseTaxCommission> tax_commission;
    std::optional<AccountCommissionResponseDiscount> discount;

    bool operator==(const AccountCommissionResponse& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT AccountCommissionResponse tag_invoke(
    boost::json::value_to_tag<AccountCommissionResponse> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const AccountCommissionResponse& v);

} // namespace binance::spot::rest_api
