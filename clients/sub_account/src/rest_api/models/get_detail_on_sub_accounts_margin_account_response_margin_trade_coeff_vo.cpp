//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/sub_account/rest_api/models/get_detail_on_sub_accounts_margin_account_response_margin_trade_coeff_vo.hpp>

namespace binance::sub_account::rest_api {

GetDetailOnSubAccountsMarginAccountResponseMarginTradeCoeffVo
tag_invoke(boost::json::value_to_tag<
               GetDetailOnSubAccountsMarginAccountResponseMarginTradeCoeffVo> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "GetDetailOnSubAccountsMarginAccountResponseMarginTradeCoeffVo");
    GetDetailOnSubAccountsMarginAccountResponseMarginTradeCoeffVo out;
    common::detail::json::read(obj, "forceLiquidationBar", out.force_liquidation_bar);
    common::detail::json::read(obj, "marginCallBar", out.margin_call_bar);
    common::detail::json::read(obj, "normalBar", out.normal_bar);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetDetailOnSubAccountsMarginAccountResponseMarginTradeCoeffVo& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "forceLiquidationBar", v.force_liquidation_bar);
    common::detail::json::write(obj, "marginCallBar", v.margin_call_bar);
    common::detail::json::write(obj, "normalBar", v.normal_bar);
}

} // namespace binance::sub_account::rest_api
