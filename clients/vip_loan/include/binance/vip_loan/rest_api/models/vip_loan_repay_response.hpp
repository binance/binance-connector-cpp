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

struct VipLoanRepayResponse {
    std::optional<std::string> loan_coin;
    std::optional<std::string> repay_amount;
    std::optional<std::string> remaining_principal;
    std::optional<std::string> remaining_interest;
    std::optional<std::string> collateral_coin;
    std::optional<std::string> current_ltv;
    /// Repayment status (`Repaid`, `Repaying`, `Failed`).
    std::optional<std::string> repay_status;

    bool operator==(const VipLoanRepayResponse& /*other*/) const = default;
};

BINANCE_VIP_LOAN_EXPORT VipLoanRepayResponse
tag_invoke(boost::json::value_to_tag<VipLoanRepayResponse> /*tag*/, const boost::json::value& jv);
BINANCE_VIP_LOAN_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                        const VipLoanRepayResponse& v);

} // namespace binance::vip_loan::rest_api
