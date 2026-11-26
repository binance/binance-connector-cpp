//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/sub_account/rest_api/models/query_managed_sub_account_asset_details_response_inner.hpp>

namespace binance::sub_account::rest_api {

QueryManagedSubAccountAssetDetailsResponseInner
tag_invoke(boost::json::value_to_tag<QueryManagedSubAccountAssetDetailsResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "QueryManagedSubAccountAssetDetailsResponseInner");
    QueryManagedSubAccountAssetDetailsResponseInner out;
    common::detail::json::read(obj, "coin", out.coin);
    common::detail::json::read(obj, "name", out.name);
    common::detail::json::read(obj, "totalBalance", out.total_balance);
    common::detail::json::read(obj, "availableBalance", out.available_balance);
    common::detail::json::read(obj, "inOrder", out.in_order);
    common::detail::json::read(obj, "btcValue", out.btc_value);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryManagedSubAccountAssetDetailsResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "coin", v.coin);
    common::detail::json::write(obj, "name", v.name);
    common::detail::json::write(obj, "totalBalance", v.total_balance);
    common::detail::json::write(obj, "availableBalance", v.available_balance);
    common::detail::json::write(obj, "inOrder", v.in_order);
    common::detail::json::write(obj, "btcValue", v.btc_value);
}

} // namespace binance::sub_account::rest_api
