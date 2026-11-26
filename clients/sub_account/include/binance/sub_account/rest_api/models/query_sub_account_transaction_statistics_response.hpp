//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <optional>
#include <string>
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/sub_account/export.hpp>
#include <binance/sub_account/rest_api/models/query_sub_account_transaction_statistics_response_trade_info_vos_inner.hpp>

namespace binance::sub_account::rest_api {

struct QuerySubAccountTransactionStatisticsResponse {
    std::optional<std::string> recent30_btc_total;
    std::optional<std::string> recent30_btc_futures_total;
    std::optional<std::string> recent30_btc_margin_total;
    std::optional<std::string> recent30_busd_total;
    std::optional<std::string> recent30_busd_futures_total;
    std::optional<std::string> recent30_busd_margin_total;
    std::optional<std::vector<QuerySubAccountTransactionStatisticsResponseTradeInfoVosInner>>
        trade_info_vos;

    bool operator==(const QuerySubAccountTransactionStatisticsResponse& /*other*/) const = default;
};

BINANCE_SUB_ACCOUNT_EXPORT QuerySubAccountTransactionStatisticsResponse
tag_invoke(boost::json::value_to_tag<QuerySubAccountTransactionStatisticsResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_SUB_ACCOUNT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           const QuerySubAccountTransactionStatisticsResponse& v);

} // namespace binance::sub_account::rest_api
