//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/mining/rest_api/models/account_list_response_data_inner.hpp>

namespace binance::mining::rest_api {

AccountListResponseDataInner
tag_invoke(boost::json::value_to_tag<AccountListResponseDataInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "AccountListResponseDataInner");
    AccountListResponseDataInner out;
    common::detail::json::read(obj, "type", out.type);
    common::detail::json::read(obj, "userName", out.user_name);
    common::detail::json::read(obj, "list", out.list);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const AccountListResponseDataInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "type", v.type);
    common::detail::json::write(obj, "userName", v.user_name);
    common::detail::json::write(obj, "list", v.list);
}

} // namespace binance::mining::rest_api
