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

#include <binance/margin_trading/export.hpp>

namespace binance::margin_trading::rest_api {

struct QueryMarginAvailableInventoryResponse {
    /// Available inventory per asset. Keys are asset symbols, values are available amounts.
    std::optional<std::map<std::string, std::string>> assets;
    /// update Time.
    std::optional<std::int64_t> update_time;

    bool operator==(const QueryMarginAvailableInventoryResponse& /*other*/) const = default;
};

BINANCE_MARGIN_TRADING_EXPORT QueryMarginAvailableInventoryResponse
tag_invoke(boost::json::value_to_tag<QueryMarginAvailableInventoryResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const QueryMarginAvailableInventoryResponse& v);

} // namespace binance::margin_trading::rest_api
