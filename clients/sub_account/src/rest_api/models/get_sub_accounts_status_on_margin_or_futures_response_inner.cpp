//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/sub_account/rest_api/models/get_sub_accounts_status_on_margin_or_futures_response_inner.hpp>

namespace binance::sub_account::rest_api {

GetSubAccountsStatusOnMarginOrFuturesResponseInner
tag_invoke(boost::json::value_to_tag<GetSubAccountsStatusOnMarginOrFuturesResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetSubAccountsStatusOnMarginOrFuturesResponseInner");
    GetSubAccountsStatusOnMarginOrFuturesResponseInner out;
    common::detail::json::read(obj, "email", out.email);
    common::detail::json::read(obj, "isSubUserEnabled", out.is_sub_user_enabled);
    common::detail::json::read(obj, "isUserActive", out.is_user_active);
    common::detail::json::read(obj, "insertTime", out.insert_time);
    common::detail::json::read(obj, "isMarginEnabled", out.is_margin_enabled);
    common::detail::json::read(obj, "isFutureEnabled", out.is_future_enabled);
    common::detail::json::read(obj, "mobile", out.mobile);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetSubAccountsStatusOnMarginOrFuturesResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "email", v.email);
    common::detail::json::write(obj, "isSubUserEnabled", v.is_sub_user_enabled);
    common::detail::json::write(obj, "isUserActive", v.is_user_active);
    common::detail::json::write(obj, "insertTime", v.insert_time);
    common::detail::json::write(obj, "isMarginEnabled", v.is_margin_enabled);
    common::detail::json::write(obj, "isFutureEnabled", v.is_future_enabled);
    common::detail::json::write(obj, "mobile", v.mobile);
}

} // namespace binance::sub_account::rest_api
