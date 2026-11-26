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

#include <binance/derivatives_trading_portfolio_margin_pro/export.hpp>

namespace binance::derivatives_trading_portfolio_margin_pro::rest_api {

struct QueryPortfolioMarginAssetIndexPriceResponseInner {
    /// asset.
    std::optional<std::string> asset;
    /// in USD
    std::optional<std::string> asset_index_price;
    /// time.
    std::optional<std::int64_t> time;

    bool
    operator==(const QueryPortfolioMarginAssetIndexPriceResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_PRO_EXPORT
QueryPortfolioMarginAssetIndexPriceResponseInner
tag_invoke(boost::json::value_to_tag<QueryPortfolioMarginAssetIndexPriceResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_PRO_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const QueryPortfolioMarginAssetIndexPriceResponseInner& v);

} // namespace binance::derivatives_trading_portfolio_margin_pro::rest_api
