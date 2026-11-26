//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/margin_trading/rest_api/models/query_max_borrow_response.hpp>

namespace binance::margin_trading::rest_api {

QueryMaxBorrowResponse tag_invoke(boost::json::value_to_tag<QueryMaxBorrowResponse> /*tag*/,
                                  const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "QueryMaxBorrowResponse");
    QueryMaxBorrowResponse out;
    common::detail::json::read(obj, "amount", out.amount);
    common::detail::json::read(obj, "borrowLimit", out.borrow_limit);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryMaxBorrowResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "amount", v.amount);
    common::detail::json::write(obj, "borrowLimit", v.borrow_limit);
}

} // namespace binance::margin_trading::rest_api
