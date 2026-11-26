//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/query_margin_loan_record_response_rows_inner.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

QueryMarginLoanRecordResponseRowsInner
tag_invoke(boost::json::value_to_tag<QueryMarginLoanRecordResponseRowsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "QueryMarginLoanRecordResponseRowsInner");
    QueryMarginLoanRecordResponseRowsInner out;
    common::detail::json::read(obj, "txId", out.tx_id);
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "principal", out.principal);
    common::detail::json::read(obj, "timestamp", out.timestamp);
    common::detail::json::read(obj, "status", out.status);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryMarginLoanRecordResponseRowsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "txId", v.tx_id);
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "principal", v.principal);
    common::detail::json::write(obj, "timestamp", v.timestamp);
    common::detail::json::write(obj, "status", v.status);
}

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
