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

#include <binance/margin_trading/export.hpp>

namespace binance::margin_trading::rest_api {

struct QueryCrossIsolatedMarginCapitalFlowResponseInner {
    /// id.
    std::optional<std::int64_t> id;
    /// tran Id.
    std::optional<std::int64_t> tran_id;
    /// timestamp.
    std::optional<std::int64_t> timestamp;
    /// asset.
    std::optional<std::string> asset;
    /// symbol.
    std::optional<std::string> symbol;
    /// type.
    std::optional<std::string> type;
    /// amount.
    std::optional<std::string> amount;
    /// note.
    std::optional<std::string> note;

    bool
    operator==(const QueryCrossIsolatedMarginCapitalFlowResponseInner& /*other*/) const = default;
};

BINANCE_MARGIN_TRADING_EXPORT QueryCrossIsolatedMarginCapitalFlowResponseInner
tag_invoke(boost::json::value_to_tag<QueryCrossIsolatedMarginCapitalFlowResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const QueryCrossIsolatedMarginCapitalFlowResponseInner& v);

} // namespace binance::margin_trading::rest_api
