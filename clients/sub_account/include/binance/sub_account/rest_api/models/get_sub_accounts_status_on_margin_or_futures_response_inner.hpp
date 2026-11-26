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

struct GetSubAccountsStatusOnMarginOrFuturesResponseInner {
    /// user email
    std::optional<std::string> email;
    /// true or false
    std::optional<bool> is_sub_user_enabled;
    /// true or false
    std::optional<bool> is_user_active;
    /// sub account create time
    std::optional<std::int64_t> insert_time;
    /// true or false for margin
    std::optional<bool> is_margin_enabled;
    /// true or false for futures.
    std::optional<bool> is_future_enabled;
    /// user mobile number
    std::optional<std::int64_t> mobile;

    bool
    operator==(const GetSubAccountsStatusOnMarginOrFuturesResponseInner& /*other*/) const = default;
};

BINANCE_SUB_ACCOUNT_EXPORT GetSubAccountsStatusOnMarginOrFuturesResponseInner
tag_invoke(boost::json::value_to_tag<GetSubAccountsStatusOnMarginOrFuturesResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_SUB_ACCOUNT_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetSubAccountsStatusOnMarginOrFuturesResponseInner& v);

} // namespace binance::sub_account::rest_api
