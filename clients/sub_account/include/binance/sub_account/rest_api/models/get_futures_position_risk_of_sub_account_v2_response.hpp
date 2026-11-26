//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <optional>
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/sub_account/export.hpp>
#include <binance/sub_account/rest_api/models/get_futures_position_risk_of_sub_account_response_inner.hpp>
#include <binance/sub_account/rest_api/models/get_futures_position_risk_of_sub_account_v2_response_delivery_position_risk_vos_inner.hpp>

namespace binance::sub_account::rest_api {

struct GetFuturesPositionRiskOfSubAccountV2Response {
    std::optional<std::vector<GetFuturesPositionRiskOfSubAccountResponseInner>>
        future_position_risk_vos;
    std::optional<
        std::vector<GetFuturesPositionRiskOfSubAccountV2ResponseDeliveryPositionRiskVosInner>>
        delivery_position_risk_vos;

    bool operator==(const GetFuturesPositionRiskOfSubAccountV2Response& /*other*/) const = default;
};

BINANCE_SUB_ACCOUNT_EXPORT GetFuturesPositionRiskOfSubAccountV2Response
tag_invoke(boost::json::value_to_tag<GetFuturesPositionRiskOfSubAccountV2Response> /*tag*/,
           const boost::json::value& jv);
BINANCE_SUB_ACCOUNT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           const GetFuturesPositionRiskOfSubAccountV2Response& v);

} // namespace binance::sub_account::rest_api
