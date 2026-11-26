//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/sub_account/export.hpp>
#include <binance/sub_account/rest_api/models/get_detail_on_sub_accounts_futures_account_v2_response_delivery_account_resp_assets_inner.hpp>

namespace binance::sub_account::rest_api {

struct GetDetailOnSubAccountsFuturesAccountV2ResponseDeliveryAccountResp {
    std::optional<std::string> email;
    std::optional<
        std::vector<GetDetailOnSubAccountsFuturesAccountV2ResponseDeliveryAccountRespAssetsInner>>
        assets;
    std::optional<bool> can_deposit;
    std::optional<bool> can_trade;
    std::optional<bool> can_withdraw;
    std::optional<std::int64_t> fee_tier;
    std::optional<std::int64_t> update_time;

    bool
    operator==(const GetDetailOnSubAccountsFuturesAccountV2ResponseDeliveryAccountResp& /*other*/)
        const = default;
};

BINANCE_SUB_ACCOUNT_EXPORT GetDetailOnSubAccountsFuturesAccountV2ResponseDeliveryAccountResp
tag_invoke(boost::json::value_to_tag<
               GetDetailOnSubAccountsFuturesAccountV2ResponseDeliveryAccountResp> /*tag*/,
           const boost::json::value& jv);
BINANCE_SUB_ACCOUNT_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetDetailOnSubAccountsFuturesAccountV2ResponseDeliveryAccountResp& v);

} // namespace binance::sub_account::rest_api
