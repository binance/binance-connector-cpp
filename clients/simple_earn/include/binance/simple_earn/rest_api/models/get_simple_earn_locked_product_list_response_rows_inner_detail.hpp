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

struct GetSimpleEarnLockedProductListResponseRowsInnerDetail {
    std::optional<std::string> asset;
    std::optional<std::string> reward_asset;
    std::optional<std::int64_t> duration;
    std::optional<bool> renewable;
    std::optional<bool> is_sold_out;
    std::optional<std::string> apr;
    std::optional<std::string> status;
    std::optional<std::int64_t> subscription_start_time;
    std::optional<std::string> extra_reward_asset;
    std::optional<std::string> extra_reward_apr;
    std::optional<std::string> boost_reward_asset;
    std::optional<std::string> boost_apr;
    std::optional<std::int64_t> boost_end_time;

    bool operator==(const GetSimpleEarnLockedProductListResponseRowsInnerDetail& /*other*/) const =
        default;
};

BINANCE_SIMPLE_EARN_EXPORT GetSimpleEarnLockedProductListResponseRowsInnerDetail
tag_invoke(boost::json::value_to_tag<GetSimpleEarnLockedProductListResponseRowsInnerDetail> /*tag*/,
           const boost::json::value& jv);
BINANCE_SIMPLE_EARN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetSimpleEarnLockedProductListResponseRowsInnerDetail& v);

} // namespace binance::simple_earn::rest_api
