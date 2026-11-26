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

struct GetRateHistoryResponseRowsInner {
    std::optional<std::string> product_id;
    std::optional<std::string> asset;
    std::optional<std::string> annual_percentage_rate;
    std::optional<std::int64_t> time;

    bool operator==(const GetRateHistoryResponseRowsInner& /*other*/) const = default;
};

BINANCE_SIMPLE_EARN_EXPORT GetRateHistoryResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetRateHistoryResponseRowsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_SIMPLE_EARN_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           const GetRateHistoryResponseRowsInner& v);

} // namespace binance::simple_earn::rest_api
