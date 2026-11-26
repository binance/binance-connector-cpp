//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/margin_trading/rest_api/models/get_interest_history_response_rows_inner.hpp>

namespace binance::margin_trading::rest_api {

GetInterestHistoryResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetInterestHistoryResponseRowsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetInterestHistoryResponseRowsInner");
    GetInterestHistoryResponseRowsInner out;
    common::detail::json::read(obj, "txId", out.tx_id);
    common::detail::json::read(obj, "interestAccuredTime", out.interest_accured_time);
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "rawAsset", out.raw_asset);
    common::detail::json::read(obj, "principal", out.principal);
    common::detail::json::read(obj, "interest", out.interest);
    common::detail::json::read(obj, "interestRate", out.interest_rate);
    common::detail::json::read(obj, "type", out.type);
    common::detail::json::read(obj, "isolatedSymbol", out.isolated_symbol);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetInterestHistoryResponseRowsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "txId", v.tx_id);
    common::detail::json::write(obj, "interestAccuredTime", v.interest_accured_time);
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "rawAsset", v.raw_asset);
    common::detail::json::write(obj, "principal", v.principal);
    common::detail::json::write(obj, "interest", v.interest);
    common::detail::json::write(obj, "interestRate", v.interest_rate);
    common::detail::json::write(obj, "type", v.type);
    common::detail::json::write(obj, "isolatedSymbol", v.isolated_symbol);
}

} // namespace binance::margin_trading::rest_api
