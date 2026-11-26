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

struct QueryManagedSubAccountListResponseManagerSubUserInfoVoListInner {
    std::optional<std::int64_t> root_user_id;
    std::optional<std::int64_t> managersub_user_id;
    std::optional<std::int64_t> bind_parent_user_id;
    std::optional<std::string> email;
    std::optional<std::int64_t> insert_time_stamp;
    std::optional<std::string> bind_parent_email;
    std::optional<bool> is_sub_user_enabled;
    std::optional<bool> is_user_active;
    std::optional<bool> is_margin_enabled;
    std::optional<bool> is_future_enabled;
    std::optional<bool> is_signed_lvt_risk_agreement;

    bool
    operator==(const QueryManagedSubAccountListResponseManagerSubUserInfoVoListInner& /*other*/)
        const = default;
};

BINANCE_SUB_ACCOUNT_EXPORT QueryManagedSubAccountListResponseManagerSubUserInfoVoListInner
tag_invoke(boost::json::value_to_tag<
               QueryManagedSubAccountListResponseManagerSubUserInfoVoListInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_SUB_ACCOUNT_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const QueryManagedSubAccountListResponseManagerSubUserInfoVoListInner& v);

} // namespace binance::sub_account::rest_api
