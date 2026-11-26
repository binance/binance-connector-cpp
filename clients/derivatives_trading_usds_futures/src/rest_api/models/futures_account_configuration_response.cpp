//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/futures_account_configuration_response.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

FuturesAccountConfigurationResponse
tag_invoke(boost::json::value_to_tag<FuturesAccountConfigurationResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "FuturesAccountConfigurationResponse");
    FuturesAccountConfigurationResponse out;
    common::detail::json::read(obj, "feeTier", out.fee_tier);
    common::detail::json::read(obj, "canTrade", out.can_trade);
    common::detail::json::read(obj, "canDeposit", out.can_deposit);
    common::detail::json::read(obj, "canWithdraw", out.can_withdraw);
    common::detail::json::read(obj, "dualSidePosition", out.dual_side_position);
    common::detail::json::read(obj, "updateTime", out.update_time);
    common::detail::json::read(obj, "multiAssetsMargin", out.multi_assets_margin);
    common::detail::json::read(obj, "tradeGroupId", out.trade_group_id);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const FuturesAccountConfigurationResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "feeTier", v.fee_tier);
    common::detail::json::write(obj, "canTrade", v.can_trade);
    common::detail::json::write(obj, "canDeposit", v.can_deposit);
    common::detail::json::write(obj, "canWithdraw", v.can_withdraw);
    common::detail::json::write(obj, "dualSidePosition", v.dual_side_position);
    common::detail::json::write(obj, "updateTime", v.update_time);
    common::detail::json::write(obj, "multiAssetsMargin", v.multi_assets_margin);
    common::detail::json::write(obj, "tradeGroupId", v.trade_group_id);
}

} // namespace binance::derivatives_trading_usds_futures::rest_api
