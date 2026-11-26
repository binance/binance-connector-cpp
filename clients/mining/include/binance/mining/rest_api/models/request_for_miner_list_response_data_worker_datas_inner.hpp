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

#include <binance/common/decimal.hpp>
#include <binance/mining/export.hpp>

namespace binance::mining::rest_api {

struct RequestForMinerListResponseDataWorkerDatasInner {
    /// Miner ID
    std::optional<std::string> worker_id;
    /// Miner name
    std::optional<std::string> worker_name;
    /// Status: 1 Valid, 2 Invalid, 3 No longer valid
    std::optional<std::int64_t> status;
    /// Real-time rate
    std::optional<std::int64_t> hash_rate;
    /// 24H hashrate
    std::optional<common::Decimal> day_hash_rate;
    /// Real-time rejection rate
    std::optional<std::int64_t> reject_rate;
    /// Last share time
    std::optional<std::int64_t> last_share_time;

    bool
    operator==(const RequestForMinerListResponseDataWorkerDatasInner& /*other*/) const = default;
};

BINANCE_MINING_EXPORT RequestForMinerListResponseDataWorkerDatasInner
tag_invoke(boost::json::value_to_tag<RequestForMinerListResponseDataWorkerDatasInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_MINING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const RequestForMinerListResponseDataWorkerDatasInner& v);

} // namespace binance::mining::rest_api
