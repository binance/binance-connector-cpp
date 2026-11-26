//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/wallet/rest_api/models/fetch_withdraw_quota_response.hpp>

namespace binance::wallet::rest_api {

FetchWithdrawQuotaResponse tag_invoke(boost::json::value_to_tag<FetchWithdrawQuotaResponse> /*tag*/,
                                      const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "FetchWithdrawQuotaResponse");
    FetchWithdrawQuotaResponse out;
    common::detail::json::read(obj, "wdQuota", out.wd_quota);
    common::detail::json::read(obj, "usedWdQuota", out.used_wd_quota);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const FetchWithdrawQuotaResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "wdQuota", v.wd_quota);
    common::detail::json::write(obj, "usedWdQuota", v.used_wd_quota);
}

} // namespace binance::wallet::rest_api
