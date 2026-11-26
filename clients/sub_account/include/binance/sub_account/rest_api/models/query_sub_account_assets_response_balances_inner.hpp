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
#include <binance/sub_account/export.hpp>

namespace binance::sub_account::rest_api {

struct QuerySubAccountAssetsResponseBalancesInner {
    std::optional<std::int64_t> freeze;
    std::optional<std::int64_t> withdrawing;
    std::optional<std::string> asset;
    std::optional<common::Decimal> free;
    std::optional<std::int64_t> locked;

    bool operator==(const QuerySubAccountAssetsResponseBalancesInner& /*other*/) const = default;
};

BINANCE_SUB_ACCOUNT_EXPORT QuerySubAccountAssetsResponseBalancesInner
tag_invoke(boost::json::value_to_tag<QuerySubAccountAssetsResponseBalancesInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_SUB_ACCOUNT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           const QuerySubAccountAssetsResponseBalancesInner& v);

} // namespace binance::sub_account::rest_api
