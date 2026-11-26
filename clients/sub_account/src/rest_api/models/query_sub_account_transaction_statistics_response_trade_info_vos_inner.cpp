//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/sub_account/rest_api/models/query_sub_account_transaction_statistics_response_trade_info_vos_inner.hpp>

namespace binance::sub_account::rest_api {

QuerySubAccountTransactionStatisticsResponseTradeInfoVosInner
tag_invoke(boost::json::value_to_tag<
               QuerySubAccountTransactionStatisticsResponseTradeInfoVosInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "QuerySubAccountTransactionStatisticsResponseTradeInfoVosInner");
    QuerySubAccountTransactionStatisticsResponseTradeInfoVosInner out;
    common::detail::json::read(obj, "userId", out.user_id);
    common::detail::json::read(obj, "btc", out.btc);
    common::detail::json::read(obj, "btcFutures", out.btc_futures);
    common::detail::json::read(obj, "btcMargin", out.btc_margin);
    common::detail::json::read(obj, "busd", out.busd);
    common::detail::json::read(obj, "busdFutures", out.busd_futures);
    common::detail::json::read(obj, "busdMargin", out.busd_margin);
    common::detail::json::read(obj, "date", out.date);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QuerySubAccountTransactionStatisticsResponseTradeInfoVosInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "userId", v.user_id);
    common::detail::json::write(obj, "btc", v.btc);
    common::detail::json::write(obj, "btcFutures", v.btc_futures);
    common::detail::json::write(obj, "btcMargin", v.btc_margin);
    common::detail::json::write(obj, "busd", v.busd);
    common::detail::json::write(obj, "busdFutures", v.busd_futures);
    common::detail::json::write(obj, "busdMargin", v.busd_margin);
    common::detail::json::write(obj, "date", v.date);
}

} // namespace binance::sub_account::rest_api
