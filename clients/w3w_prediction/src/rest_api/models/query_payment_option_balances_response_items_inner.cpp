//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/w3w_prediction/rest_api/models/query_payment_option_balances_response_items_inner.hpp>

namespace binance::w3w_prediction::rest_api {

QueryPaymentOptionBalancesResponseItemsInner
tag_invoke(boost::json::value_to_tag<QueryPaymentOptionBalancesResponseItemsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "QueryPaymentOptionBalancesResponseItemsInner");
    QueryPaymentOptionBalancesResponseItemsInner out;
    common::detail::json::read(obj, "accountType", out.account_type);
    common::detail::json::read(obj, "availableBalanceDisplay", out.available_balance_display);
    common::detail::json::read(obj, "enabled", out.enabled);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryPaymentOptionBalancesResponseItemsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "accountType", v.account_type);
    common::detail::json::write(obj, "availableBalanceDisplay", v.available_balance_display);
    common::detail::json::write(obj, "enabled", v.enabled);
}

} // namespace binance::w3w_prediction::rest_api
