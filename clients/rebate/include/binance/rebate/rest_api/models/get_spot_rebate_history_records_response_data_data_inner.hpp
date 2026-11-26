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

#include <binance/rebate/export.hpp>

namespace binance::rebate::rest_api {

struct GetSpotRebateHistoryRecordsResponseDataDataInner {
    /// Rebate asset.
    std::optional<std::string> asset;
    /// 1 is commission rebate, 2 is referral kickback
    std::optional<std::int64_t> type;
    /// Rebate amount.
    std::optional<std::string> amount;
    /// Update timestamp.
    std::optional<std::int64_t> update_time;

    bool
    operator==(const GetSpotRebateHistoryRecordsResponseDataDataInner& /*other*/) const = default;
};

BINANCE_REBATE_EXPORT GetSpotRebateHistoryRecordsResponseDataDataInner
tag_invoke(boost::json::value_to_tag<GetSpotRebateHistoryRecordsResponseDataDataInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_REBATE_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const GetSpotRebateHistoryRecordsResponseDataDataInner& v);

} // namespace binance::rebate::rest_api
