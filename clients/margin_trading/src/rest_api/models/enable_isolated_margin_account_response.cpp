//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/margin_trading/rest_api/models/enable_isolated_margin_account_response.hpp>

namespace binance::margin_trading::rest_api {

EnableIsolatedMarginAccountResponse
tag_invoke(boost::json::value_to_tag<EnableIsolatedMarginAccountResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "EnableIsolatedMarginAccountResponse");
    EnableIsolatedMarginAccountResponse out;
    common::detail::json::read(obj, "success", out.success);
    common::detail::json::read(obj, "symbol", out.symbol);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const EnableIsolatedMarginAccountResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "success", v.success);
    common::detail::json::write(obj, "symbol", v.symbol);
}

} // namespace binance::margin_trading::rest_api
