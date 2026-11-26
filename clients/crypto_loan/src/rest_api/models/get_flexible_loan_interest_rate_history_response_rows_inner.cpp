//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/crypto_loan/rest_api/models/get_flexible_loan_interest_rate_history_response_rows_inner.hpp>

namespace binance::crypto_loan::rest_api {

GetFlexibleLoanInterestRateHistoryResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetFlexibleLoanInterestRateHistoryResponseRowsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetFlexibleLoanInterestRateHistoryResponseRowsInner");
    GetFlexibleLoanInterestRateHistoryResponseRowsInner out;
    common::detail::json::read(obj, "coin", out.coin);
    common::detail::json::read(obj, "annualizedInterestRate", out.annualized_interest_rate);
    common::detail::json::read(obj, "time", out.time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetFlexibleLoanInterestRateHistoryResponseRowsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "coin", v.coin);
    common::detail::json::write(obj, "annualizedInterestRate", v.annualized_interest_rate);
    common::detail::json::write(obj, "time", v.time);
}

} // namespace binance::crypto_loan::rest_api
