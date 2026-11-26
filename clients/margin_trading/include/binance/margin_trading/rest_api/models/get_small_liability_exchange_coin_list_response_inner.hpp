//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <optional>
#include <string>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/common/decimal.hpp>
#include <binance/margin_trading/export.hpp>

namespace binance::margin_trading::rest_api {

struct GetSmallLiabilityExchangeCoinListResponseInner {
    /// asset.
    std::optional<std::string> asset;
    /// interest.
    std::optional<std::string> interest;
    /// principal.
    std::optional<std::string> principal;
    /// liability Asset.
    std::optional<std::string> liability_asset;
    /// liability Qty.
    std::optional<common::Decimal> liability_qty;

    bool
    operator==(const GetSmallLiabilityExchangeCoinListResponseInner& /*other*/) const = default;
};

BINANCE_MARGIN_TRADING_EXPORT GetSmallLiabilityExchangeCoinListResponseInner
tag_invoke(boost::json::value_to_tag<GetSmallLiabilityExchangeCoinListResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetSmallLiabilityExchangeCoinListResponseInner& v);

} // namespace binance::margin_trading::rest_api
