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

#include <binance/simple_earn/export.hpp>

namespace binance::simple_earn::rest_api {

struct GetLockedSubscriptionRecordResponseRowsInner {
    std::optional<std::int64_t> position_id;
    std::optional<std::string> purchase_id;
    std::optional<std::string> project_id;
    std::optional<std::int64_t> time;
    std::optional<std::string> asset;
    std::optional<std::string> amount;
    std::optional<std::string> lock_period;
    /// NORMAL for normal subscription, AUTO for auto-subscription order, ACTIVITY for activity
    /// order, TRIAL for trial fund order, RESTAKE for restake order
    std::optional<std::string> type;
    /// SPOT, FUNDING, SPOTANDFUNDING
    std::optional<std::string> source_account;
    /// Display if sourceAccount is SPOTANDFUNDING
    std::optional<std::string> amt_from_spot;
    /// Display if sourceAccount is SPOTANDFUNDING
    std::optional<std::string> amt_from_funding;
    /// PURCHASING/SUCCESS/FAILED
    std::optional<std::string> status;

    bool operator==(const GetLockedSubscriptionRecordResponseRowsInner& /*other*/) const = default;
};

BINANCE_SIMPLE_EARN_EXPORT GetLockedSubscriptionRecordResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetLockedSubscriptionRecordResponseRowsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_SIMPLE_EARN_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           const GetLockedSubscriptionRecordResponseRowsInner& v);

} // namespace binance::simple_earn::rest_api
