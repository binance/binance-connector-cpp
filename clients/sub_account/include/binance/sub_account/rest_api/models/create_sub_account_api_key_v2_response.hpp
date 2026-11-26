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

struct CreateSubAccountApiKeyV2Response {
    std::optional<std::string> api_name;
    std::optional<std::string> api_key;
    /// Secret Key. Returned only once on creation, please keep it safe.
    std::optional<std::string> secret_key;
    std::optional<bool> can_trade;
    std::optional<bool> can_margin_loan_repay;
    std::optional<bool> can_futures_trade;
    std::optional<bool> can_universal_transfer;
    std::optional<bool> can_vanilla_options;
    std::optional<bool> can_fix_api_trading;
    std::optional<bool> can_fix_api_reading;
    std::optional<std::int64_t> status;
    std::optional<std::vector<std::string>> ip_list;

    bool operator==(const CreateSubAccountApiKeyV2Response& /*other*/) const = default;
};

BINANCE_SUB_ACCOUNT_EXPORT CreateSubAccountApiKeyV2Response
tag_invoke(boost::json::value_to_tag<CreateSubAccountApiKeyV2Response> /*tag*/,
           const boost::json::value& jv);
BINANCE_SUB_ACCOUNT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           const CreateSubAccountApiKeyV2Response& v);

} // namespace binance::sub_account::rest_api
