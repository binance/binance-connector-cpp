//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin_pro/rest_api/models/get_margin_call_level_response.hpp>

namespace binance::derivatives_trading_portfolio_margin_pro::rest_api {

GetMarginCallLevelResponse tag_invoke(boost::json::value_to_tag<GetMarginCallLevelResponse> /*tag*/,
                                      const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetMarginCallLevelResponse");
    GetMarginCallLevelResponse out;
    common::detail::json::read(obj, "marginCallLevel", out.margin_call_level);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetMarginCallLevelResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "marginCallLevel", v.margin_call_level);
}

} // namespace binance::derivatives_trading_portfolio_margin_pro::rest_api
