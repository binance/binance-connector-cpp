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

#include <binance/vip_loan/export.hpp>

namespace binance::vip_loan::rest_api {

struct CheckVIPLoanCollateralAccountResponseRowsInner {
    std::optional<std::string> collateral_account_id;
    std::optional<std::string> collateral_coin;

    bool
    operator==(const CheckVIPLoanCollateralAccountResponseRowsInner& /*other*/) const = default;
};

BINANCE_VIP_LOAN_EXPORT CheckVIPLoanCollateralAccountResponseRowsInner
tag_invoke(boost::json::value_to_tag<CheckVIPLoanCollateralAccountResponseRowsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_VIP_LOAN_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                        const CheckVIPLoanCollateralAccountResponseRowsInner& v);

} // namespace binance::vip_loan::rest_api
