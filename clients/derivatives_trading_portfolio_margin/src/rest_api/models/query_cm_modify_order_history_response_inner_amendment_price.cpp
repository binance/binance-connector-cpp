//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/query_cm_modify_order_history_response_inner_amendment_price.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

QueryCmModifyOrderHistoryResponseInnerAmendmentPrice
tag_invoke(boost::json::value_to_tag<QueryCmModifyOrderHistoryResponseInnerAmendmentPrice> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "QueryCmModifyOrderHistoryResponseInnerAmendmentPrice");
    QueryCmModifyOrderHistoryResponseInnerAmendmentPrice out;
    common::detail::json::read(obj, "before", out.before);
    common::detail::json::read(obj, "after", out.after);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryCmModifyOrderHistoryResponseInnerAmendmentPrice& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "before", v.before);
    common::detail::json::write(obj, "after", v.after);
}

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
