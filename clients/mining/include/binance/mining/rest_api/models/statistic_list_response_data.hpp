//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <cstdint>
#include <map>
#include <optional>
#include <string>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/mining/export.hpp>

namespace binance::mining::rest_api {

struct StatisticListResponseData {
    /// 15-minute hashrate
    std::optional<std::string> fifteen_min_hash_rate;
    /// 24H hashrate
    std::optional<std::string> day_hash_rate;
    /// Effective quantity
    std::optional<std::int64_t> valid_num;
    /// Invalid quantity
    std::optional<std::int64_t> invalid_num;
    /// Today's estimate. Keys are coin symbols (e.g. BTC, BSV, BCH), values are earning amounts as
    /// strings.
    std::optional<std::map<std::string, std::string>> profit_today;
    /// Yesterday's earnings. Keys are coin symbols (e.g. BTC, BSV, BCH), values are earning amounts
    /// as strings.
    std::optional<std::map<std::string, std::string>> profit_yesterday;
    /// Mining account
    std::optional<std::string> user_name;
    /// Unit
    std::optional<std::string> unit;
    /// Algorithm
    std::optional<std::string> algo;

    bool operator==(const StatisticListResponseData& /*other*/) const = default;
};

BINANCE_MINING_EXPORT StatisticListResponseData tag_invoke(
    boost::json::value_to_tag<StatisticListResponseData> /*tag*/, const boost::json::value& jv);
BINANCE_MINING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const StatisticListResponseData& v);

} // namespace binance::mining::rest_api
