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
#include <binance/spot/websocket_api/models/account_commission_response_result_discount.hpp>
#include <binance/spot/websocket_api/models/account_commission_response_result_special_commission.hpp>
#include <binance/spot/websocket_api/models/account_commission_response_result_standard_commission.hpp>
#include <binance/spot/websocket_api/models/account_commission_response_result_tax_commission.hpp>

namespace binance::spot::websocket_api {

struct AccountCommissionResponseResult {
    std::optional<std::string> symbol;
    std::optional<AccountCommissionResponseResultStandardCommission> standard_commission;
    std::optional<AccountCommissionResponseResultSpecialCommission> special_commission;
    std::optional<AccountCommissionResponseResultTaxCommission> tax_commission;
    std::optional<AccountCommissionResponseResultDiscount> discount;

    bool operator==(const AccountCommissionResponseResult& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT AccountCommissionResponseResult
tag_invoke(boost::json::value_to_tag<AccountCommissionResponseResult> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const AccountCommissionResponseResult& v);

} // namespace binance::spot::websocket_api
