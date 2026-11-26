//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/stock_options/rest_api/models/option_settlement_event_history_response_rows_inner_deliverables_inner.hpp>

namespace binance::stock_options::rest_api {

OptionSettlementEventHistoryResponseRowsInnerDeliverablesInner
tag_invoke(boost::json::value_to_tag<
               OptionSettlementEventHistoryResponseRowsInnerDeliverablesInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "OptionSettlementEventHistoryResponseRowsInnerDeliverablesInner");
    OptionSettlementEventHistoryResponseRowsInnerDeliverablesInner out;
    common::detail::json::read(obj, "type", out.type);
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "amount", out.amount);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const OptionSettlementEventHistoryResponseRowsInnerDeliverablesInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "type", v.type);
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "amount", v.amount);
}

} // namespace binance::stock_options::rest_api
