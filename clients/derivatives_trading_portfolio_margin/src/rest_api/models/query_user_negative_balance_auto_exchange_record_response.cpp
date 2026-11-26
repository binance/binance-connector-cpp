//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/query_user_negative_balance_auto_exchange_record_response.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

QueryUserNegativeBalanceAutoExchangeRecordResponse
tag_invoke(boost::json::value_to_tag<QueryUserNegativeBalanceAutoExchangeRecordResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "QueryUserNegativeBalanceAutoExchangeRecordResponse");
    QueryUserNegativeBalanceAutoExchangeRecordResponse out;
    common::detail::json::read(obj, "total", out.total);
    common::detail::json::read(obj, "rows", out.rows);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryUserNegativeBalanceAutoExchangeRecordResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "total", v.total);
    common::detail::json::write(obj, "rows", v.rows);
}

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
