//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/stock_options/rest_api/models/option_settlement_event_history_response.hpp>

namespace binance::stock_options::rest_api {

OptionSettlementEventHistoryResponse
tag_invoke(boost::json::value_to_tag<OptionSettlementEventHistoryResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "OptionSettlementEventHistoryResponse");
    OptionSettlementEventHistoryResponse out;
    common::detail::json::read(obj, "rows", out.rows);
    common::detail::json::read(obj, "hasMore", out.has_more);
    common::detail::json::read(obj, "nextLastId", out.next_last_id);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const OptionSettlementEventHistoryResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "rows", v.rows);
    common::detail::json::write(obj, "hasMore", v.has_more);
    common::detail::json::write(obj, "nextLastId", v.next_last_id);
}

} // namespace binance::stock_options::rest_api
