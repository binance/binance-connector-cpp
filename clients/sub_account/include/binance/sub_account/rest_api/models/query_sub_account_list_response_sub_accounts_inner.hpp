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

struct QuerySubAccountListResponseSubAccountsInner {
    std::optional<std::int64_t> sub_user_id;
    std::optional<std::string> email;
    std::optional<std::string> remark;
    std::optional<bool> is_freeze;
    std::optional<std::int64_t> create_time;
    std::optional<bool> is_managed_sub_account;
    std::optional<bool> is_asset_management_sub_account;

    bool operator==(const QuerySubAccountListResponseSubAccountsInner& /*other*/) const = default;
};

BINANCE_SUB_ACCOUNT_EXPORT QuerySubAccountListResponseSubAccountsInner
tag_invoke(boost::json::value_to_tag<QuerySubAccountListResponseSubAccountsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_SUB_ACCOUNT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           const QuerySubAccountListResponseSubAccountsInner& v);

} // namespace binance::sub_account::rest_api
