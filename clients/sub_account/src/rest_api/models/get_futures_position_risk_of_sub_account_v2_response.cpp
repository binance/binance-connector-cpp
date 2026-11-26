//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/sub_account/rest_api/models/get_futures_position_risk_of_sub_account_v2_response.hpp>

namespace binance::sub_account::rest_api {

GetFuturesPositionRiskOfSubAccountV2Response
tag_invoke(boost::json::value_to_tag<GetFuturesPositionRiskOfSubAccountV2Response> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetFuturesPositionRiskOfSubAccountV2Response");
    GetFuturesPositionRiskOfSubAccountV2Response out;
    common::detail::json::read(obj, "futurePositionRiskVos", out.future_position_risk_vos);
    common::detail::json::read(obj, "deliveryPositionRiskVos", out.delivery_position_risk_vos);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetFuturesPositionRiskOfSubAccountV2Response& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "futurePositionRiskVos", v.future_position_risk_vos);
    common::detail::json::write(obj, "deliveryPositionRiskVos", v.delivery_position_risk_vos);
}

} // namespace binance::sub_account::rest_api
