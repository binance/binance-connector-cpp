//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/query_user_negative_balance_auto_exchange_record_response_rows_inner_details_inner.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

QueryUserNegativeBalanceAutoExchangeRecordResponseRowsInnerDetailsInner
tag_invoke(boost::json::value_to_tag<
               QueryUserNegativeBalanceAutoExchangeRecordResponseRowsInnerDetailsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "QueryUserNegativeBalanceAutoExchangeRecordResponseRowsInnerDetailsInner");
    QueryUserNegativeBalanceAutoExchangeRecordResponseRowsInnerDetailsInner out;
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "negativeBalance", out.negative_balance);
    common::detail::json::read(obj, "negativeMaxThreshold", out.negative_max_threshold);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryUserNegativeBalanceAutoExchangeRecordResponseRowsInnerDetailsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "negativeBalance", v.negative_balance);
    common::detail::json::write(obj, "negativeMaxThreshold", v.negative_max_threshold);
}

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
