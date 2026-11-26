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

#include <binance/mining/export.hpp>

namespace binance::mining::rest_api {

struct HashrateResaleListResponseDataConfigDetailsInner {
    /// Configuration ID
    std::optional<std::int64_t> config_id;
    /// Transfer-out sub-account
    std::optional<std::string> pool_username;
    /// Transfer-in sub-account
    std::optional<std::string> to_pool_username;
    /// Transfer algorithm name
    std::optional<std::string> algo_name;
    /// Transferred hashrate
    std::optional<std::int64_t> hash_rate;
    /// Start date
    std::optional<std::int64_t> start_day;
    /// End date
    std::optional<std::int64_t> end_day;
    /// Status: 0 Processing, 1 Cancelled, 2 Terminated
    std::optional<std::int64_t> status;
    /// Type: 0 Hashrate transfer record, 1 Hashrate receive record
    std::optional<std::int64_t> type;

    bool
    operator==(const HashrateResaleListResponseDataConfigDetailsInner& /*other*/) const = default;
};

BINANCE_MINING_EXPORT HashrateResaleListResponseDataConfigDetailsInner
tag_invoke(boost::json::value_to_tag<HashrateResaleListResponseDataConfigDetailsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_MINING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const HashrateResaleListResponseDataConfigDetailsInner& v);

} // namespace binance::mining::rest_api
