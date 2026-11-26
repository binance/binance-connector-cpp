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

struct GetCrossMarginTransferHistoryResponseRowsInner {
    /// amount.
    std::optional<std::string> amount;
    /// asset.
    std::optional<std::string> asset;
    /// status.
    std::optional<std::string> status;
    /// timestamp.
    std::optional<std::int64_t> timestamp;
    /// tx Id.
    std::optional<std::int64_t> tx_id;
    /// type.
    std::optional<std::string> type;
    /// SPOT,FUTURES,FIAT,DELIVERY,MINING,ISOLATED_MARGIN,FUNDING,MOTHER_SPOT,OPTION,SUB_SPOT,SUB_MARGIN,CROSS_MARGIN
    std::optional<std::string> trans_from;
    /// SPOT,FUTURES,FIAT,DELIVERY,MINING,ISOLATED_MARGIN,FUNDING,MOTHER_SPOT,OPTION,SUB_SPOT,SUB_MARGIN,CROSS_MARGIN
    std::optional<std::string> trans_to;
    /// from Symbol.
    std::optional<std::string> from_symbol;
    /// to Symbol.
    std::optional<std::string> to_symbol;

    bool
    operator==(const GetCrossMarginTransferHistoryResponseRowsInner& /*other*/) const = default;
};

BINANCE_MARGIN_TRADING_EXPORT GetCrossMarginTransferHistoryResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetCrossMarginTransferHistoryResponseRowsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetCrossMarginTransferHistoryResponseRowsInner& v);

} // namespace binance::margin_trading::rest_api
