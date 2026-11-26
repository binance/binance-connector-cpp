//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/query_user_negative_balance_auto_exchange_record_response_rows_inner.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

QueryUserNegativeBalanceAutoExchangeRecordResponseRowsInner tag_invoke(
    boost::json::value_to_tag<QueryUserNegativeBalanceAutoExchangeRecordResponseRowsInner> /*tag*/,
    const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "QueryUserNegativeBalanceAutoExchangeRecordResponseRowsInner");
    QueryUserNegativeBalanceAutoExchangeRecordResponseRowsInner out;
    common::detail::json::read(obj, "startTime", out.start_time);
    common::detail::json::read(obj, "endTime", out.end_time);
    common::detail::json::read(obj, "details", out.details);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryUserNegativeBalanceAutoExchangeRecordResponseRowsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "startTime", v.start_time);
    common::detail::json::write(obj, "endTime", v.end_time);
    common::detail::json::write(obj, "details", v.details);
}

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
