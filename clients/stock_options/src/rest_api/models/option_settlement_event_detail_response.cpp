//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/stock_options/rest_api/models/option_settlement_event_detail_response.hpp>

namespace binance::stock_options::rest_api {

OptionSettlementEventDetailResponse
tag_invoke(boost::json::value_to_tag<OptionSettlementEventDetailResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "OptionSettlementEventDetailResponse");
    OptionSettlementEventDetailResponse out;
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
    common::detail::json::read(obj, "settlementKind", out.settlement_kind);
    common::detail::json::read(obj, "underlyingPrice", out.underlying_price);
    common::detail::json::read(obj, "cashDirection", out.cash_direction);
    common::detail::json::read(obj, "amount", out.amount);
    common::detail::json::read(obj, "collateralRelease", out.collateral_release);
    common::detail::json::read(obj, "updatedTime", out.updated_time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const OptionSettlementEventDetailResponse& v) {
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
    common::detail::json::write(obj, "settlementKind", v.settlement_kind);
    common::detail::json::write(obj, "underlyingPrice", v.underlying_price);
    common::detail::json::write(obj, "cashDirection", v.cash_direction);
    common::detail::json::write(obj, "amount", v.amount);
    common::detail::json::write(obj, "collateralRelease", v.collateral_release);
    common::detail::json::write(obj, "updatedTime", v.updated_time);
}

} // namespace binance::stock_options::rest_api
