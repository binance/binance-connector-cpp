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

struct GetWbethUnwrapHistoryResponseRowsInner {
    std::optional<std::int64_t> time;
    std::optional<std::string> from_asset;
    std::optional<std::string> from_amount;
    std::optional<std::string> to_asset;
    std::optional<std::string> to_amount;
    /// BETH value per 1 WBETH
    std::optional<std::string> exchange_rate;
    /// PENDING,SUCCESS,FAILED
    std::optional<std::string> status;

    bool operator==(const GetWbethUnwrapHistoryResponseRowsInner& /*other*/) const = default;
};

BINANCE_STAKING_EXPORT GetWbethUnwrapHistoryResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetWbethUnwrapHistoryResponseRowsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_STAKING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                       const GetWbethUnwrapHistoryResponseRowsInner& v);

} // namespace binance::staking::rest_api
