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

struct GetFlexibleRedemptionRecordResponseRowsInner {
    std::optional<std::string> amount;
    std::optional<std::string> asset;
    std::optional<std::int64_t> time;
    std::optional<std::string> project_id;
    std::optional<std::int64_t> redeem_id;
    /// SPOT, FUNDING
    std::optional<std::string> dest_account;
    /// CREATED,PAID,FAILED
    std::optional<std::string> status;

    bool operator==(const GetFlexibleRedemptionRecordResponseRowsInner& /*other*/) const = default;
};

BINANCE_SIMPLE_EARN_EXPORT GetFlexibleRedemptionRecordResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetFlexibleRedemptionRecordResponseRowsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_SIMPLE_EARN_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           const GetFlexibleRedemptionRecordResponseRowsInner& v);

} // namespace binance::simple_earn::rest_api
