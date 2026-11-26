//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/margin_trading/rest_api/models/get_bnb_burn_status_response.hpp>

namespace binance::margin_trading::rest_api {

GetBnbBurnStatusResponse tag_invoke(boost::json::value_to_tag<GetBnbBurnStatusResponse> /*tag*/,
                                    const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetBnbBurnStatusResponse");
    GetBnbBurnStatusResponse out;
    common::detail::json::read(obj, "spotBNBBurn", out.spot_bnb_burn);
    common::detail::json::read(obj, "interestBNBBurn", out.interest_bnb_burn);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetBnbBurnStatusResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "spotBNBBurn", v.spot_bnb_burn);
    common::detail::json::write(obj, "interestBNBBurn", v.interest_bnb_burn);
}

} // namespace binance::margin_trading::rest_api
