//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/wallet/rest_api/models/account_info_response.hpp>

namespace binance::wallet::rest_api {

AccountInfoResponse tag_invoke(boost::json::value_to_tag<AccountInfoResponse> /*tag*/,
                               const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "AccountInfoResponse");
    AccountInfoResponse out;
    common::detail::json::read(obj, "vipLevel", out.vip_level);
    common::detail::json::read(obj, "isMarginEnabled", out.is_margin_enabled);
    common::detail::json::read(obj, "isFutureEnabled", out.is_future_enabled);
    common::detail::json::read(obj, "isOptionsEnabled", out.is_options_enabled);
    common::detail::json::read(obj, "isPortfolioMarginRetailEnabled",
                               out.is_portfolio_margin_retail_enabled);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const AccountInfoResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "vipLevel", v.vip_level);
    common::detail::json::write(obj, "isMarginEnabled", v.is_margin_enabled);
    common::detail::json::write(obj, "isFutureEnabled", v.is_future_enabled);
    common::detail::json::write(obj, "isOptionsEnabled", v.is_options_enabled);
    common::detail::json::write(obj, "isPortfolioMarginRetailEnabled",
                                v.is_portfolio_margin_retail_enabled);
}

} // namespace binance::wallet::rest_api
