//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/get_um_futures_bnb_burn_status_response.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

GetUmFuturesBnbBurnStatusResponse
tag_invoke(boost::json::value_to_tag<GetUmFuturesBnbBurnStatusResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetUmFuturesBnbBurnStatusResponse");
    GetUmFuturesBnbBurnStatusResponse out;
    common::detail::json::read(obj, "feeBurn", out.fee_burn);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetUmFuturesBnbBurnStatusResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "feeBurn", v.fee_burn);
}

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
