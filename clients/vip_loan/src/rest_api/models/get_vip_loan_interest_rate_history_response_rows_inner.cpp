//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/vip_loan/rest_api/models/get_vip_loan_interest_rate_history_response_rows_inner.hpp>

namespace binance::vip_loan::rest_api {

GetVIPLoanInterestRateHistoryResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetVIPLoanInterestRateHistoryResponseRowsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetVIPLoanInterestRateHistoryResponseRowsInner");
    GetVIPLoanInterestRateHistoryResponseRowsInner out;
    common::detail::json::read(obj, "coin", out.coin);
    common::detail::json::read(obj, "annualizedInterestRate", out.annualized_interest_rate);
    common::detail::json::read(obj, "time", out.time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetVIPLoanInterestRateHistoryResponseRowsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "coin", v.coin);
    common::detail::json::write(obj, "annualizedInterestRate", v.annualized_interest_rate);
    common::detail::json::write(obj, "time", v.time);
}

} // namespace binance::vip_loan::rest_api
