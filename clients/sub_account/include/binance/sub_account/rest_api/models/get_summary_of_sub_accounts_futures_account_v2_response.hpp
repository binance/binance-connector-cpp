//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <optional>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/sub_account/export.hpp>
#include <binance/sub_account/rest_api/models/get_summary_of_sub_accounts_futures_account_v2_response_delivery_account_summary_resp.hpp>
#include <binance/sub_account/rest_api/models/get_summary_of_sub_accounts_futures_account_v2_response_future_account_summary_resp.hpp>

namespace binance::sub_account::rest_api {

struct GetSummaryOfSubAccountsFuturesAccountV2Response {
    std::optional<GetSummaryOfSubAccountsFuturesAccountV2ResponseFutureAccountSummaryResp>
        future_account_summary_resp;
    std::optional<GetSummaryOfSubAccountsFuturesAccountV2ResponseDeliveryAccountSummaryResp>
        delivery_account_summary_resp;

    bool
    operator==(const GetSummaryOfSubAccountsFuturesAccountV2Response& /*other*/) const = default;
};

BINANCE_SUB_ACCOUNT_EXPORT GetSummaryOfSubAccountsFuturesAccountV2Response
tag_invoke(boost::json::value_to_tag<GetSummaryOfSubAccountsFuturesAccountV2Response> /*tag*/,
           const boost::json::value& jv);
BINANCE_SUB_ACCOUNT_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetSummaryOfSubAccountsFuturesAccountV2Response& v);

} // namespace binance::sub_account::rest_api
