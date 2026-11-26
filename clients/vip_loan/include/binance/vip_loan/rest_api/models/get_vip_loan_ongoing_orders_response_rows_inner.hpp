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

#include <binance/vip_loan/export.hpp>

namespace binance::vip_loan::rest_api {

struct GetVIPLoanOngoingOrdersResponseRowsInner {
    std::optional<std::int64_t> order_id;
    std::optional<std::string> loan_coin;
    std::optional<std::string> total_debt;
    /// For flexible loans, this is the flexible rate.
    std::optional<std::string> loan_rate;
    std::optional<std::string> residual_interest;
    std::optional<std::string> collateral_account_id;
    /// Includes `<ASSET>-Earn` entries when a Simple Earn Flexible position is pledged.
    std::optional<std::string> collateral_coin;
    std::optional<std::string> total_collateral_value_after_haircut;
    std::optional<std::string> locked_collateral_value;
    std::optional<std::string> current_ltv;
    /// For flexible loans, this value is `0`.
    std::optional<std::int64_t> expiration_time;
    std::optional<std::string> loan_date;
    /// For flexible loans, this value is `open term`.
    std::optional<std::string> loan_term;

    bool operator==(const GetVIPLoanOngoingOrdersResponseRowsInner& /*other*/) const = default;
};

BINANCE_VIP_LOAN_EXPORT GetVIPLoanOngoingOrdersResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetVIPLoanOngoingOrdersResponseRowsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_VIP_LOAN_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                        const GetVIPLoanOngoingOrdersResponseRowsInner& v);

} // namespace binance::vip_loan::rest_api
