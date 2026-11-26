//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/stock_options/rest_api/models/option_exercise_detail_response.hpp>

namespace binance::stock_options::rest_api {

OptionExerciseDetailResponse
tag_invoke(boost::json::value_to_tag<OptionExerciseDetailResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "OptionExerciseDetailResponse");
    OptionExerciseDetailResponse out;
    common::detail::json::read(obj, "tranId", out.tran_id);
    common::detail::json::read(obj, "clientOrderId", out.client_order_id);
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "underlyingSymbol", out.underlying_symbol);
    common::detail::json::read(obj, "rootSymbol", out.root_symbol);
    common::detail::json::read(obj, "contractType", out.contract_type);
    common::detail::json::read(obj, "strikePrice", out.strike_price);
    common::detail::json::read(obj, "expirationDate", out.expiration_date);
    common::detail::json::read(obj, "requestedQty", out.requested_qty);
    common::detail::json::read(obj, "status", out.status);
    common::detail::json::read(obj, "requestedTime", out.requested_time);
    common::detail::json::read(obj, "updateTime", out.update_time);
    common::detail::json::read(obj, "optionEventId", out.option_event_id);
    common::detail::json::read(obj, "underlyingEventId", out.underlying_event_id);
    common::detail::json::read(obj, "multiplier", out.multiplier);
    common::detail::json::read(obj, "errorCode", out.error_code);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const OptionExerciseDetailResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "tranId", v.tran_id);
    common::detail::json::write(obj, "clientOrderId", v.client_order_id);
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "underlyingSymbol", v.underlying_symbol);
    common::detail::json::write(obj, "rootSymbol", v.root_symbol);
    common::detail::json::write(obj, "contractType", v.contract_type);
    common::detail::json::write(obj, "strikePrice", v.strike_price);
    common::detail::json::write(obj, "expirationDate", v.expiration_date);
    common::detail::json::write(obj, "requestedQty", v.requested_qty);
    common::detail::json::write(obj, "status", v.status);
    common::detail::json::write(obj, "requestedTime", v.requested_time);
    common::detail::json::write(obj, "updateTime", v.update_time);
    common::detail::json::write(obj, "optionEventId", v.option_event_id);
    common::detail::json::write(obj, "underlyingEventId", v.underlying_event_id);
    common::detail::json::write(obj, "multiplier", v.multiplier);
    common::detail::json::write(obj, "errorCode", v.error_code);
}

} // namespace binance::stock_options::rest_api
