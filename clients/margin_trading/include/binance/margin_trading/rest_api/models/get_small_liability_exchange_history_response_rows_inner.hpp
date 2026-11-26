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

struct GetSmallLiabilityExchangeHistoryResponseRowsInner {
    /// asset.
    std::optional<std::string> asset;
    /// amount.
    std::optional<std::string> amount;
    /// target Asset.
    std::optional<std::string> target_asset;
    /// target Amount.
    std::optional<std::string> target_amount;
    /// biz Type.
    std::optional<std::string> biz_type;
    /// timestamp.
    std::optional<std::int64_t> timestamp;

    bool
    operator==(const GetSmallLiabilityExchangeHistoryResponseRowsInner& /*other*/) const = default;
};

BINANCE_MARGIN_TRADING_EXPORT GetSmallLiabilityExchangeHistoryResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetSmallLiabilityExchangeHistoryResponseRowsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetSmallLiabilityExchangeHistoryResponseRowsInner& v);

} // namespace binance::margin_trading::rest_api
