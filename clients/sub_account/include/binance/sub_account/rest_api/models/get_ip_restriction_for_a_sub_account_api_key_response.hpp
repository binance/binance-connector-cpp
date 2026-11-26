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

namespace binance::sub_account::rest_api {

struct GetIpRestrictionForASubAccountApiKeyResponse {
    std::optional<std::string> ip_restrict;
    std::optional<std::vector<std::string>> ip_list;
    std::optional<std::int64_t> update_time;
    std::optional<std::string> api_key;

    bool operator==(const GetIpRestrictionForASubAccountApiKeyResponse& /*other*/) const = default;
};

BINANCE_SUB_ACCOUNT_EXPORT GetIpRestrictionForASubAccountApiKeyResponse
tag_invoke(boost::json::value_to_tag<GetIpRestrictionForASubAccountApiKeyResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_SUB_ACCOUNT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           const GetIpRestrictionForASubAccountApiKeyResponse& v);

} // namespace binance::sub_account::rest_api
