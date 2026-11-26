//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/margin_trading/rest_api/models/query_enabled_isolated_margin_account_limit_response.hpp>

namespace binance::margin_trading::rest_api {

QueryEnabledIsolatedMarginAccountLimitResponse
tag_invoke(boost::json::value_to_tag<QueryEnabledIsolatedMarginAccountLimitResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "QueryEnabledIsolatedMarginAccountLimitResponse");
    QueryEnabledIsolatedMarginAccountLimitResponse out;
    common::detail::json::read(obj, "enabledAccount", out.enabled_account);
    common::detail::json::read(obj, "maxAccount", out.max_account);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryEnabledIsolatedMarginAccountLimitResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "enabledAccount", v.enabled_account);
    common::detail::json::write(obj, "maxAccount", v.max_account);
}

} // namespace binance::margin_trading::rest_api
