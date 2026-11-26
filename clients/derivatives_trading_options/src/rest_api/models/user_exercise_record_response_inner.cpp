//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_options/rest_api/models/user_exercise_record_response_inner.hpp>

namespace binance::derivatives_trading_options::rest_api {

UserExerciseRecordResponseInner
tag_invoke(boost::json::value_to_tag<UserExerciseRecordResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "UserExerciseRecordResponseInner");
    UserExerciseRecordResponseInner out;
    common::detail::json::read(obj, "id", out.id);
    common::detail::json::read(obj, "currency", out.currency);
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "exercisePrice", out.exercise_price);
    common::detail::json::read(obj, "quantity", out.quantity);
    common::detail::json::read(obj, "amount", out.amount);
    common::detail::json::read(obj, "fee", out.fee);
    common::detail::json::read(obj, "createDate", out.create_date);
    common::detail::json::read(obj, "priceScale", out.price_scale);
    common::detail::json::read(obj, "quantityScale", out.quantity_scale);
    common::detail::json::read(obj, "optionSide", out.option_side);
    common::detail::json::read(obj, "positionSide", out.position_side);
    common::detail::json::read(obj, "quoteAsset", out.quote_asset);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const UserExerciseRecordResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "id", v.id);
    common::detail::json::write(obj, "currency", v.currency);
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "exercisePrice", v.exercise_price);
    common::detail::json::write(obj, "quantity", v.quantity);
    common::detail::json::write(obj, "amount", v.amount);
    common::detail::json::write(obj, "fee", v.fee);
    common::detail::json::write(obj, "createDate", v.create_date);
    common::detail::json::write(obj, "priceScale", v.price_scale);
    common::detail::json::write(obj, "quantityScale", v.quantity_scale);
    common::detail::json::write(obj, "optionSide", v.option_side);
    common::detail::json::write(obj, "positionSide", v.position_side);
    common::detail::json::write(obj, "quoteAsset", v.quote_asset);
}

} // namespace binance::derivatives_trading_options::rest_api
