//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/get_income_history_response_inner.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

GetIncomeHistoryResponseInner
tag_invoke(boost::json::value_to_tag<GetIncomeHistoryResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetIncomeHistoryResponseInner");
    GetIncomeHistoryResponseInner out;
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "incomeType", out.income_type);
    common::detail::json::read(obj, "income", out.income);
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "info", out.info);
    common::detail::json::read(obj, "time", out.time);
    common::detail::json::read(obj, "tranId", out.tran_id);
    common::detail::json::read(obj, "tradeId", out.trade_id);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetIncomeHistoryResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "incomeType", v.income_type);
    common::detail::json::write(obj, "income", v.income);
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "info", v.info);
    common::detail::json::write(obj, "time", v.time);
    common::detail::json::write(obj, "tranId", v.tran_id);
    common::detail::json::write(obj, "tradeId", v.trade_id);
}

} // namespace binance::derivatives_trading_usds_futures::rest_api
