//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/margin_trading/rest_api/models/query_isolated_margin_fee_data_response_inner.hpp>

namespace binance::margin_trading::rest_api {

QueryIsolatedMarginFeeDataResponseInner
tag_invoke(boost::json::value_to_tag<QueryIsolatedMarginFeeDataResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "QueryIsolatedMarginFeeDataResponseInner");
    QueryIsolatedMarginFeeDataResponseInner out;
    common::detail::json::read(obj, "vipLevel", out.vip_level);
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "leverage", out.leverage);
    common::detail::json::read(obj, "data", out.data);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryIsolatedMarginFeeDataResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "vipLevel", v.vip_level);
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "leverage", v.leverage);
    common::detail::json::write(obj, "data", v.data);
}

} // namespace binance::margin_trading::rest_api
