//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/margin_trading/rest_api/models/query_borrow_repay_records_in_margin_account_response.hpp>

namespace binance::margin_trading::rest_api {

QueryBorrowRepayRecordsInMarginAccountResponse
tag_invoke(boost::json::value_to_tag<QueryBorrowRepayRecordsInMarginAccountResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "QueryBorrowRepayRecordsInMarginAccountResponse");
    QueryBorrowRepayRecordsInMarginAccountResponse out;
    common::detail::json::read(obj, "rows", out.rows);
    common::detail::json::read(obj, "total", out.total);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryBorrowRepayRecordsInMarginAccountResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "rows", v.rows);
    common::detail::json::write(obj, "total", v.total);
}

} // namespace binance::margin_trading::rest_api
