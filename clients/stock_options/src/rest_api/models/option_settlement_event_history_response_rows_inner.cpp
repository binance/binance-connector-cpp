//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/stock_options/rest_api/models/option_settlement_event_history_response_rows_inner.hpp>

namespace binance::stock_options::rest_api {

OptionSettlementEventHistoryResponseRowsInner
tag_invoke(boost::json::value_to_tag<OptionSettlementEventHistoryResponseRowsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "OptionSettlementEventHistoryResponseRowsInner");
    OptionSettlementEventHistoryResponseRowsInner out;
    common::detail::json::read(obj, "eventId", out.event_id);
    common::detail::json::read(obj, "eventType", out.event_type);
    common::detail::json::read(obj, "status", out.status);
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "underlyingSymbol", out.underlying_symbol);
    common::detail::json::read(obj, "contractType", out.contract_type);
    common::detail::json::read(obj, "contracts", out.contracts);
    common::detail::json::read(obj, "expirationDate", out.expiration_date);
    common::detail::json::read(obj, "strikePrice", out.strike_price);
    common::detail::json::read(obj, "shareDelta", out.share_delta);
    common::detail::json::read(obj, "deliverables", out.deliverables);
    common::detail::json::read(obj, "eventTime", out.event_time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const OptionSettlementEventHistoryResponseRowsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "eventId", v.event_id);
    common::detail::json::write(obj, "eventType", v.event_type);
    common::detail::json::write(obj, "status", v.status);
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "underlyingSymbol", v.underlying_symbol);
    common::detail::json::write(obj, "contractType", v.contract_type);
    common::detail::json::write(obj, "contracts", v.contracts);
    common::detail::json::write(obj, "expirationDate", v.expiration_date);
    common::detail::json::write(obj, "strikePrice", v.strike_price);
    common::detail::json::write(obj, "shareDelta", v.share_delta);
    common::detail::json::write(obj, "deliverables", v.deliverables);
    common::detail::json::write(obj, "eventTime", v.event_time);
}

} // namespace binance::stock_options::rest_api
