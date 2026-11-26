//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/wallet/rest_api/models/toggle_bnb_burn_on_spot_trade_and_margin_interest_response.hpp>

namespace binance::wallet::rest_api {

ToggleBnbBurnOnSpotTradeAndMarginInterestResponse
tag_invoke(boost::json::value_to_tag<ToggleBnbBurnOnSpotTradeAndMarginInterestResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "ToggleBnbBurnOnSpotTradeAndMarginInterestResponse");
    ToggleBnbBurnOnSpotTradeAndMarginInterestResponse out;
    common::detail::json::read(obj, "spotBNBBurn", out.spot_bnb_burn);
    common::detail::json::read(obj, "interestBNBBurn", out.interest_bnb_burn);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const ToggleBnbBurnOnSpotTradeAndMarginInterestResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "spotBNBBurn", v.spot_bnb_burn);
    common::detail::json::write(obj, "interestBNBBurn", v.interest_bnb_burn);
}

} // namespace binance::wallet::rest_api
