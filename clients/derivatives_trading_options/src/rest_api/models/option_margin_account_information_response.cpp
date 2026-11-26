//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_options/rest_api/models/option_margin_account_information_response.hpp>

namespace binance::derivatives_trading_options::rest_api {

OptionMarginAccountInformationResponse
tag_invoke(boost::json::value_to_tag<OptionMarginAccountInformationResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "OptionMarginAccountInformationResponse");
    OptionMarginAccountInformationResponse out;
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "greek", out.greek);
    common::detail::json::read(obj, "time", out.time);
    common::detail::json::read(obj, "canTrade", out.can_trade);
    common::detail::json::read(obj, "canDeposit", out.can_deposit);
    common::detail::json::read(obj, "canWithdraw", out.can_withdraw);
    common::detail::json::read(obj, "reduceOnly", out.reduce_only);
    common::detail::json::read(obj, "tradeGroupId", out.trade_group_id);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const OptionMarginAccountInformationResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "greek", v.greek);
    common::detail::json::write(obj, "time", v.time);
    common::detail::json::write(obj, "canTrade", v.can_trade);
    common::detail::json::write(obj, "canDeposit", v.can_deposit);
    common::detail::json::write(obj, "canWithdraw", v.can_withdraw);
    common::detail::json::write(obj, "reduceOnly", v.reduce_only);
    common::detail::json::write(obj, "tradeGroupId", v.trade_group_id);
}

} // namespace binance::derivatives_trading_options::rest_api
