//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/wallet/rest_api/models/get_api_key_permission_response.hpp>

namespace binance::wallet::rest_api {

GetApiKeyPermissionResponse
tag_invoke(boost::json::value_to_tag<GetApiKeyPermissionResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetApiKeyPermissionResponse");
    GetApiKeyPermissionResponse out;
    common::detail::json::read(obj, "ipRestrict", out.ip_restrict);
    common::detail::json::read(obj, "createTime", out.create_time);
    common::detail::json::read(obj, "enableReading", out.enable_reading);
    common::detail::json::read(obj, "enableWithdrawals", out.enable_withdrawals);
    common::detail::json::read(obj, "enableInternalTransfer", out.enable_internal_transfer);
    common::detail::json::read(obj, "enableMargin", out.enable_margin);
    common::detail::json::read(obj, "enableFutures", out.enable_futures);
    common::detail::json::read(obj, "permitsUniversalTransfer", out.permits_universal_transfer);
    common::detail::json::read(obj, "enableVanillaOptions", out.enable_vanilla_options);
    common::detail::json::read(obj, "enableFixApiTrade", out.enable_fix_api_trade);
    common::detail::json::read(obj, "enableFixReadOnly", out.enable_fix_read_only);
    common::detail::json::read(obj, "enableSpotAndMarginTrading",
                               out.enable_spot_and_margin_trading);
    common::detail::json::read(obj, "enablePortfolioMarginTrading",
                               out.enable_portfolio_margin_trading);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetApiKeyPermissionResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "ipRestrict", v.ip_restrict);
    common::detail::json::write(obj, "createTime", v.create_time);
    common::detail::json::write(obj, "enableReading", v.enable_reading);
    common::detail::json::write(obj, "enableWithdrawals", v.enable_withdrawals);
    common::detail::json::write(obj, "enableInternalTransfer", v.enable_internal_transfer);
    common::detail::json::write(obj, "enableMargin", v.enable_margin);
    common::detail::json::write(obj, "enableFutures", v.enable_futures);
    common::detail::json::write(obj, "permitsUniversalTransfer", v.permits_universal_transfer);
    common::detail::json::write(obj, "enableVanillaOptions", v.enable_vanilla_options);
    common::detail::json::write(obj, "enableFixApiTrade", v.enable_fix_api_trade);
    common::detail::json::write(obj, "enableFixReadOnly", v.enable_fix_read_only);
    common::detail::json::write(obj, "enableSpotAndMarginTrading",
                                v.enable_spot_and_margin_trading);
    common::detail::json::write(obj, "enablePortfolioMarginTrading",
                                v.enable_portfolio_margin_trading);
}

} // namespace binance::wallet::rest_api
