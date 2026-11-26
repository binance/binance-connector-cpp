//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_options/rest_api/models/option_margin_account_information_response_asset_inner.hpp>

namespace binance::derivatives_trading_options::rest_api {

OptionMarginAccountInformationResponseAssetInner
tag_invoke(boost::json::value_to_tag<OptionMarginAccountInformationResponseAssetInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "OptionMarginAccountInformationResponseAssetInner");
    OptionMarginAccountInformationResponseAssetInner out;
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "marginBalance", out.margin_balance);
    common::detail::json::read(obj, "equity", out.equity);
    common::detail::json::read(obj, "available", out.available);
    common::detail::json::read(obj, "initialMargin", out.initial_margin);
    common::detail::json::read(obj, "maintMargin", out.maint_margin);
    common::detail::json::read(obj, "unrealizedPNL", out.unrealized_pnl);
    common::detail::json::read(obj, "adjustedEquity", out.adjusted_equity);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const OptionMarginAccountInformationResponseAssetInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "marginBalance", v.margin_balance);
    common::detail::json::write(obj, "equity", v.equity);
    common::detail::json::write(obj, "available", v.available);
    common::detail::json::write(obj, "initialMargin", v.initial_margin);
    common::detail::json::write(obj, "maintMargin", v.maint_margin);
    common::detail::json::write(obj, "unrealizedPNL", v.unrealized_pnl);
    common::detail::json::write(obj, "adjustedEquity", v.adjusted_equity);
}

} // namespace binance::derivatives_trading_options::rest_api
