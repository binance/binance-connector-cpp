//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/vip_loan/rest_api/models/query_vip_loan_fixed_rate_market_response_rows_inner.hpp>

namespace binance::vip_loan::rest_api {

QueryVIPLoanFixedRateMarketResponseRowsInner
tag_invoke(boost::json::value_to_tag<QueryVIPLoanFixedRateMarketResponseRowsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "QueryVIPLoanFixedRateMarketResponseRowsInner");
    QueryVIPLoanFixedRateMarketResponseRowsInner out;
    common::detail::json::read(obj, "requestId", out.request_id);
    common::detail::json::read(obj, "requestNo", out.request_no);
    common::detail::json::read(obj, "coin", out.coin);
    common::detail::json::read(obj, "interestRate", out.interest_rate);
    common::detail::json::read(obj, "duration", out.duration);
    common::detail::json::read(obj, "minimumAmount", out.minimum_amount);
    common::detail::json::read(obj, "availableAmount", out.available_amount);
    common::detail::json::read(obj, "estimatedInterest", out.estimated_interest);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryVIPLoanFixedRateMarketResponseRowsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "requestId", v.request_id);
    common::detail::json::write(obj, "requestNo", v.request_no);
    common::detail::json::write(obj, "coin", v.coin);
    common::detail::json::write(obj, "interestRate", v.interest_rate);
    common::detail::json::write(obj, "duration", v.duration);
    common::detail::json::write(obj, "minimumAmount", v.minimum_amount);
    common::detail::json::write(obj, "availableAmount", v.available_amount);
    common::detail::json::write(obj, "estimatedInterest", v.estimated_interest);
}

} // namespace binance::vip_loan::rest_api
