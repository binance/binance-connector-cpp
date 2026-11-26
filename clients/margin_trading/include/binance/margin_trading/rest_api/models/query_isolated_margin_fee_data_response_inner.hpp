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
#include <binance/margin_trading/rest_api/models/query_isolated_margin_fee_data_response_inner_data_inner.hpp>

namespace binance::margin_trading::rest_api {

struct QueryIsolatedMarginFeeDataResponseInner {
    /// vip Level.
    std::optional<std::int64_t> vip_level;
    /// symbol.
    std::optional<std::string> symbol;
    /// leverage.
    std::optional<std::string> leverage;
    /// data list.
    std::optional<std::vector<QueryIsolatedMarginFeeDataResponseInnerDataInner>> data;

    bool operator==(const QueryIsolatedMarginFeeDataResponseInner& /*other*/) const = default;
};

BINANCE_MARGIN_TRADING_EXPORT QueryIsolatedMarginFeeDataResponseInner
tag_invoke(boost::json::value_to_tag<QueryIsolatedMarginFeeDataResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const QueryIsolatedMarginFeeDataResponseInner& v);

} // namespace binance::margin_trading::rest_api
