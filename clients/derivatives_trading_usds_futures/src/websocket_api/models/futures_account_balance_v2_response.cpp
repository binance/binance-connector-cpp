//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_api/models/futures_account_balance_v2_response.hpp>

namespace binance::derivatives_trading_usds_futures::websocket_api {

FuturesAccountBalanceV2Response
tag_invoke(boost::json::value_to_tag<FuturesAccountBalanceV2Response> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "FuturesAccountBalanceV2Response");
    FuturesAccountBalanceV2Response out;
    common::detail::json::read(obj, "id", out.id);
    common::detail::json::read(obj, "status", out.status);
    common::detail::json::read(obj, "result", out.result);
    common::detail::json::read(obj, "rateLimits", out.rate_limits);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const FuturesAccountBalanceV2Response& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "id", v.id);
    common::detail::json::write(obj, "status", v.status);
    common::detail::json::write(obj, "result", v.result);
    common::detail::json::write(obj, "rateLimits", v.rate_limits);
}

} // namespace binance::derivatives_trading_usds_futures::websocket_api
