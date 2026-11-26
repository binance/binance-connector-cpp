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

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/sub_account/export.hpp>

namespace binance::sub_account::rest_api {

struct ModifySubAccountApiKeyPermissionResponse {
    std::optional<std::string> api_name;
    std::optional<std::string> apikey;
    std::optional<bool> can_trade;
    std::optional<bool> can_margin_loan_repay;
    std::optional<bool> can_futures_trade;
    std::optional<bool> can_universal_transfer;
    std::optional<bool> can_vanilla_options;
    std::optional<bool> can_fix_api_trading;
    std::optional<bool> can_fix_api_reading;
    std::optional<std::int64_t> timestamp;

    bool operator==(const ModifySubAccountApiKeyPermissionResponse& /*other*/) const = default;
};

BINANCE_SUB_ACCOUNT_EXPORT ModifySubAccountApiKeyPermissionResponse
tag_invoke(boost::json::value_to_tag<ModifySubAccountApiKeyPermissionResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_SUB_ACCOUNT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           const ModifySubAccountApiKeyPermissionResponse& v);

} // namespace binance::sub_account::rest_api
