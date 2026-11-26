//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_options/rest_api/models/historical_exercise_records_response_inner.hpp>

namespace binance::derivatives_trading_options::rest_api {

HistoricalExerciseRecordsResponseInner
tag_invoke(boost::json::value_to_tag<HistoricalExerciseRecordsResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "HistoricalExerciseRecordsResponseInner");
    HistoricalExerciseRecordsResponseInner out;
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "strikePrice", out.strike_price);
    common::detail::json::read(obj, "realStrikePrice", out.real_strike_price);
    common::detail::json::read(obj, "expiryDate", out.expiry_date);
    common::detail::json::read(obj, "strikeResult", out.strike_result);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const HistoricalExerciseRecordsResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "strikePrice", v.strike_price);
    common::detail::json::write(obj, "realStrikePrice", v.real_strike_price);
    common::detail::json::write(obj, "expiryDate", v.expiry_date);
    common::detail::json::write(obj, "strikeResult", v.strike_result);
}

} // namespace binance::derivatives_trading_options::rest_api
