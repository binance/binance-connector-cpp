//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/margin_trading/rest_api/models/query_cross_margin_fee_data_response_inner.hpp>

namespace binance::margin_trading::rest_api {

QueryCrossMarginFeeDataResponseInner
tag_invoke(boost::json::value_to_tag<QueryCrossMarginFeeDataResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "QueryCrossMarginFeeDataResponseInner");
    QueryCrossMarginFeeDataResponseInner out;
    common::detail::json::read(obj, "vipLevel", out.vip_level);
    common::detail::json::read(obj, "coin", out.coin);
    common::detail::json::read(obj, "transferIn", out.transfer_in);
    common::detail::json::read(obj, "borrowable", out.borrowable);
    common::detail::json::read(obj, "dailyInterest", out.daily_interest);
    common::detail::json::read(obj, "yearlyInterest", out.yearly_interest);
    common::detail::json::read(obj, "borrowLimit", out.borrow_limit);
    common::detail::json::read(obj, "marginablePairs", out.marginable_pairs);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryCrossMarginFeeDataResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "vipLevel", v.vip_level);
    common::detail::json::write(obj, "coin", v.coin);
    common::detail::json::write(obj, "transferIn", v.transfer_in);
    common::detail::json::write(obj, "borrowable", v.borrowable);
    common::detail::json::write(obj, "dailyInterest", v.daily_interest);
    common::detail::json::write(obj, "yearlyInterest", v.yearly_interest);
    common::detail::json::write(obj, "borrowLimit", v.borrow_limit);
    common::detail::json::write(obj, "marginablePairs", v.marginable_pairs);
}

} // namespace binance::margin_trading::rest_api
