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

struct QueryApplicationStatusResponseRowsInner {
    /// Loan receiving account.
    std::optional<std::string> loan_account_id;
    std::optional<std::string> order_id;
    std::optional<std::string> request_id;
    std::optional<std::string> loan_coin;
    std::optional<std::string> loan_amount;
    std::optional<std::string> collateral_account_id;
    /// Includes `<ASSET>-Earn` entries when a Simple Earn Flexible position is pledged.
    std::optional<std::string> collateral_coin;
    std::optional<std::string> loan_term;
    /// Order status (`Accruing_Interest`, `Overdue`, `Liquidating`, `Repaying`, `Repaid`,
    /// `Liquidated`, `Pending`, `Failed`).
    std::optional<std::string> status;
    std::optional<std::string> loan_date;

    bool operator==(const QueryApplicationStatusResponseRowsInner& /*other*/) const = default;
};

BINANCE_VIP_LOAN_EXPORT QueryApplicationStatusResponseRowsInner
tag_invoke(boost::json::value_to_tag<QueryApplicationStatusResponseRowsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_VIP_LOAN_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                        const QueryApplicationStatusResponseRowsInner& v);

} // namespace binance::vip_loan::rest_api
