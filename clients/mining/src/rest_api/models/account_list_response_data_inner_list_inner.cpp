//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/mining/rest_api/models/account_list_response_data_inner_list_inner.hpp>

namespace binance::mining::rest_api {

AccountListResponseDataInnerListInner
tag_invoke(boost::json::value_to_tag<AccountListResponseDataInnerListInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "AccountListResponseDataInnerListInner");
    AccountListResponseDataInnerListInner out;
    common::detail::json::read(obj, "time", out.time);
    common::detail::json::read(obj, "hashrate", out.hashrate);
    common::detail::json::read(obj, "reject", out.reject);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const AccountListResponseDataInnerListInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "time", v.time);
    common::detail::json::write(obj, "hashrate", v.hashrate);
    common::detail::json::write(obj, "reject", v.reject);
}

} // namespace binance::mining::rest_api
