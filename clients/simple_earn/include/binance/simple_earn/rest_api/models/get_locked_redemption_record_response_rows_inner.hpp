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

struct GetLockedRedemptionRecordResponseRowsInner {
    std::optional<std::int64_t> position_id;
    std::optional<std::int64_t> redeem_id;
    std::optional<std::int64_t> time;
    std::optional<std::string> asset;
    std::optional<std::string> lock_period;
    std::optional<std::string> amount;
    std::optional<std::string> original_amount;
    /// MATURE for redeem to Spot Wallet, NEW_TRANSFERRED for redeem to Flexible product, AHEAD for
    /// early redemption
    std::optional<std::string> type;
    std::optional<std::int64_t> deliver_date;
    /// Loss of profit on early redemption
    std::optional<std::string> loss_amount;
    std::optional<bool> is_complete;
    std::optional<std::string> reward_asset;
    std::optional<std::string> reward_amt;
    std::optional<std::string> extra_reward_asset;
    std::optional<std::string> est_extra_reward_amt;
    std::optional<std::string> status;

    bool operator==(const GetLockedRedemptionRecordResponseRowsInner& /*other*/) const = default;
};

BINANCE_SIMPLE_EARN_EXPORT GetLockedRedemptionRecordResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetLockedRedemptionRecordResponseRowsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_SIMPLE_EARN_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           const GetLockedRedemptionRecordResponseRowsInner& v);

} // namespace binance::simple_earn::rest_api
