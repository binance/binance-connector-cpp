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

struct DeleteIpListForASubAccountApiKeyResponse {
    std::optional<std::string> ip_restrict;
    std::optional<std::vector<std::string>> ip_list;
    std::optional<std::int64_t> update_time;
    std::optional<std::string> api_key;

    bool operator==(const DeleteIpListForASubAccountApiKeyResponse& /*other*/) const = default;
};

BINANCE_SUB_ACCOUNT_EXPORT DeleteIpListForASubAccountApiKeyResponse
tag_invoke(boost::json::value_to_tag<DeleteIpListForASubAccountApiKeyResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_SUB_ACCOUNT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           const DeleteIpListForASubAccountApiKeyResponse& v);

} // namespace binance::sub_account::rest_api
