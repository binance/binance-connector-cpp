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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/margin_trading/export.hpp>

namespace binance::margin_trading::rest_api {

struct QueryCrossMarginFeeDataResponseInner {
    /// vip Level.
    std::optional<std::int64_t> vip_level;
    /// coin.
    std::optional<std::string> coin;
    /// transfer In.
    std::optional<bool> transfer_in;
    /// borrowable.
    std::optional<bool> borrowable;
    /// daily Interest.
    std::optional<std::string> daily_interest;
    /// yearly Interest.
    std::optional<std::string> yearly_interest;
    /// borrow Limit.
    std::optional<std::string> borrow_limit;
    /// marginable Pairs list.
    std::optional<std::vector<std::string>> marginable_pairs;

    bool operator==(const QueryCrossMarginFeeDataResponseInner& /*other*/) const = default;
};

BINANCE_MARGIN_TRADING_EXPORT QueryCrossMarginFeeDataResponseInner
tag_invoke(boost::json::value_to_tag<QueryCrossMarginFeeDataResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const QueryCrossMarginFeeDataResponseInner& v);

} // namespace binance::margin_trading::rest_api
