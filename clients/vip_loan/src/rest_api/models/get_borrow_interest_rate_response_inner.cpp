//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/vip_loan/rest_api/models/get_borrow_interest_rate_response_inner.hpp>

namespace binance::vip_loan::rest_api {

GetBorrowInterestRateResponseInner
tag_invoke(boost::json::value_to_tag<GetBorrowInterestRateResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetBorrowInterestRateResponseInner");
    GetBorrowInterestRateResponseInner out;
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "flexibleDailyInterestRate", out.flexible_daily_interest_rate);
    common::detail::json::read(obj, "flexibleYearlyInterestRate",
                               out.flexible_yearly_interest_rate);
    common::detail::json::read(obj, "time", out.time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetBorrowInterestRateResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "flexibleDailyInterestRate", v.flexible_daily_interest_rate);
    common::detail::json::write(obj, "flexibleYearlyInterestRate", v.flexible_yearly_interest_rate);
    common::detail::json::write(obj, "time", v.time);
}

} // namespace binance::vip_loan::rest_api
