//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <cstdint>
#include <optional>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/sub_account/export.hpp>

namespace binance::sub_account::rest_api {

struct QuerySubAccountTransactionStatisticsResponseTradeInfoVosInner {
    std::optional<std::int64_t> user_id;
    std::optional<std::int64_t> btc;
    std::optional<std::int64_t> btc_futures;
    std::optional<std::int64_t> btc_margin;
    std::optional<std::int64_t> busd;
    std::optional<std::int64_t> busd_futures;
    std::optional<std::int64_t> busd_margin;
    std::optional<std::int64_t> date;

    bool operator==(const QuerySubAccountTransactionStatisticsResponseTradeInfoVosInner& /*other*/)
        const = default;
};

BINANCE_SUB_ACCOUNT_EXPORT QuerySubAccountTransactionStatisticsResponseTradeInfoVosInner
tag_invoke(boost::json::value_to_tag<
               QuerySubAccountTransactionStatisticsResponseTradeInfoVosInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_SUB_ACCOUNT_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const QuerySubAccountTransactionStatisticsResponseTradeInfoVosInner& v);

} // namespace binance::sub_account::rest_api
