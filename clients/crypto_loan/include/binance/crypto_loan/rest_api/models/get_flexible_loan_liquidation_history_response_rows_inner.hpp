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

#include <binance/crypto_loan/export.hpp>

namespace binance::crypto_loan::rest_api {

struct GetFlexibleLoanLiquidationHistoryResponseRowsInner {
    std::optional<std::string> loan_coin;
    std::optional<std::string> liquidation_debt;
    std::optional<std::string> collateral_coin;
    std::optional<std::string> liquidation_collateral_amount;
    std::optional<std::string> return_collateral_amount;
    std::optional<std::string> liquidation_fee;
    std::optional<std::string> liquidation_starting_price;
    std::optional<std::int64_t> liquidation_starting_time;
    /// Liquidating
    std::optional<std::string> status;

    bool
    operator==(const GetFlexibleLoanLiquidationHistoryResponseRowsInner& /*other*/) const = default;
};

BINANCE_CRYPTO_LOAN_EXPORT GetFlexibleLoanLiquidationHistoryResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetFlexibleLoanLiquidationHistoryResponseRowsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_CRYPTO_LOAN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetFlexibleLoanLiquidationHistoryResponseRowsInner& v);

} // namespace binance::crypto_loan::rest_api
