//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/margin_trading/rest_api/models/query_borrow_repay_records_in_margin_account_response_rows_inner.hpp>

namespace binance::margin_trading::rest_api {

QueryBorrowRepayRecordsInMarginAccountResponseRowsInner tag_invoke(
    boost::json::value_to_tag<QueryBorrowRepayRecordsInMarginAccountResponseRowsInner> /*tag*/,
    const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "QueryBorrowRepayRecordsInMarginAccountResponseRowsInner");
    QueryBorrowRepayRecordsInMarginAccountResponseRowsInner out;
    common::detail::json::read(obj, "type", out.type);
    common::detail::json::read(obj, "isolatedSymbol", out.isolated_symbol);
    common::detail::json::read(obj, "amount", out.amount);
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "interest", out.interest);
    common::detail::json::read(obj, "principal", out.principal);
    common::detail::json::read(obj, "status", out.status);
    common::detail::json::read(obj, "timestamp", out.timestamp);
    common::detail::json::read(obj, "txId", out.tx_id);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryBorrowRepayRecordsInMarginAccountResponseRowsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "type", v.type);
    common::detail::json::write(obj, "isolatedSymbol", v.isolated_symbol);
    common::detail::json::write(obj, "amount", v.amount);
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "interest", v.interest);
    common::detail::json::write(obj, "principal", v.principal);
    common::detail::json::write(obj, "status", v.status);
    common::detail::json::write(obj, "timestamp", v.timestamp);
    common::detail::json::write(obj, "txId", v.tx_id);
}

} // namespace binance::margin_trading::rest_api
