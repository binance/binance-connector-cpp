//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/sub_account/rest_api/models/query_sub_account_transaction_statistics_response.hpp>

namespace binance::sub_account::rest_api {

QuerySubAccountTransactionStatisticsResponse
tag_invoke(boost::json::value_to_tag<QuerySubAccountTransactionStatisticsResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "QuerySubAccountTransactionStatisticsResponse");
    QuerySubAccountTransactionStatisticsResponse out;
    common::detail::json::read(obj, "recent30BtcTotal", out.recent30_btc_total);
    common::detail::json::read(obj, "recent30BtcFuturesTotal", out.recent30_btc_futures_total);
    common::detail::json::read(obj, "recent30BtcMarginTotal", out.recent30_btc_margin_total);
    common::detail::json::read(obj, "recent30BusdTotal", out.recent30_busd_total);
    common::detail::json::read(obj, "recent30BusdFuturesTotal", out.recent30_busd_futures_total);
    common::detail::json::read(obj, "recent30BusdMarginTotal", out.recent30_busd_margin_total);
    common::detail::json::read(obj, "tradeInfoVos", out.trade_info_vos);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QuerySubAccountTransactionStatisticsResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "recent30BtcTotal", v.recent30_btc_total);
    common::detail::json::write(obj, "recent30BtcFuturesTotal", v.recent30_btc_futures_total);
    common::detail::json::write(obj, "recent30BtcMarginTotal", v.recent30_btc_margin_total);
    common::detail::json::write(obj, "recent30BusdTotal", v.recent30_busd_total);
    common::detail::json::write(obj, "recent30BusdFuturesTotal", v.recent30_busd_futures_total);
    common::detail::json::write(obj, "recent30BusdMarginTotal", v.recent30_busd_margin_total);
    common::detail::json::write(obj, "tradeInfoVos", v.trade_info_vos);
}

} // namespace binance::sub_account::rest_api
