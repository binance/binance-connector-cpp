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

#include <binance/staking/export.hpp>

namespace binance::staking::rest_api {

struct GetWbethRateHistoryResponseRowsInner {
    /// BETH APR
    std::optional<std::string> annual_percentage_rate;
    /// BETH value per 1 WBETH
    std::optional<std::string> exchange_rate;
    std::optional<std::int64_t> time;

    bool operator==(const GetWbethRateHistoryResponseRowsInner& /*other*/) const = default;
};

BINANCE_STAKING_EXPORT GetWbethRateHistoryResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetWbethRateHistoryResponseRowsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_STAKING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                       const GetWbethRateHistoryResponseRowsInner& v);

} // namespace binance::staking::rest_api
