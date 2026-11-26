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

struct GetBfusdSubscriptionHistoryResponseRowsInner {
    std::optional<std::int64_t> time;
    std::optional<std::string> asset;
    std::optional<std::string> amount;
    std::optional<std::string> receive_asset;
    std::optional<std::string> receive_amount;
    std::optional<std::string> status;

    bool operator==(const GetBfusdSubscriptionHistoryResponseRowsInner& /*other*/) const = default;
};

BINANCE_SIMPLE_EARN_EXPORT GetBfusdSubscriptionHistoryResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetBfusdSubscriptionHistoryResponseRowsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_SIMPLE_EARN_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           const GetBfusdSubscriptionHistoryResponseRowsInner& v);

} // namespace binance::simple_earn::rest_api
